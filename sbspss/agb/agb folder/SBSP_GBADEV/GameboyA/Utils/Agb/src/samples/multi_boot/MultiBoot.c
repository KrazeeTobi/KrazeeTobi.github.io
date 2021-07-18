/********************************************************************/
/*          MultiBoot.c                                             */
/*            AGB Multi-play Boot Library                           */
/*               (Server Support Library of Multi-play Boot)        */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/

#include "MultiBoot.h"


static u8 MultiBoot_headerbuf[MULTIBOOT_HEADER_SIZE * MULTIBOOT_NCHILD];
static u16 MultiBoot_required_data[MULTIBOOT_NCHILD];


/*------------------------------------------------------------------*/
/*                   Initialize Multi-play Boot                       */
/*------------------------------------------------------------------*/

void MultiBootInit(MultiBootParam *mp)
{
  int i;

  for (i = 0; i < MULTIBOOT_NCHILD; i++) {
    mp -> headerp[i] = &MultiBoot_headerbuf[MULTIBOOT_HEADER_SIZE * i];
  }
  mp -> probe_count = 0;
  mp -> response_bit = 0;
  mp -> client_bit = 0;
  mp -> slave_bit = 0;

  mp -> check_wait = MULTIBOOT_CONNECTION_CHECK_WAIT;
  mp -> sendflag = 0;

  *(vu16 *)REG_RCNT = 0;
  /* No interrupts,115k */
  *(vu16 *)REG_SIOCNT = SIO_MULTI_MODE | SIO_115200_BPS;
  *(vu16 *)REG_SIODATA8 = 0;
}


/*------------------------------------------------------------------*/
/*                   Multi-play Boot Main                      */
/*------------------------------------------------------------------*/
static int MultiBootSend(MultiBootParam *mp, u16 data);

int MultiBootMain(MultiBootParam *mp)
{
  extern void MultiBootStartProbe(MultiBootParam *mp);
  int i;
  int j;
  int k;
  int nchild;

  if (MultiBootCheckComplete(mp)) {
    /* No other process as transfer has been completed */
    return 0;
  }
  
  if (mp -> check_wait > MULTIBOOT_CONNECTION_CHECK_WAIT) {
    /* After system call error generates, do not send anything and wait for time out error on client.*/
    mp -> check_wait--;
    return 0;
  }

  if (mp -> sendflag) {
    mp -> sendflag = 0;
    /* SC7 should not be on at this point.
     * If it is on, communication must have timed out due to abnormal cable connection (connected to JOY, etc.)
     * When error does not generate.
     * It is considered to be errors when connect ID is not 00 or the status of SD and SI terminals is abnormal.
     */
    i = *(vu16 *)REG_SIOCNT & (SIO_MULTI_BUSY | SIO_ID_NO_MASK | SIO_MULTI_SD | SIO_MULTI_SI);
    if (i != SIO_MULTI_SD) {
      MultiBootInit(mp);
      return i ^ SIO_MULTI_SD;
    }
  }

  nchild = MULTIBOOT_NCHILD;
  
  switch (mp -> probe_count) {
  case 0:
    /* Not in the middle of recognizing client and slave.
     * SLAVE_CLIENT_INFO sss 0 ccc 0 should have received by now.
     * Check to see if there are any reactions (other than 0xffff) on machine.*/
    k = 0x0e;
    for (i = nchild; i != 0; i--) {
      if (*(vu16 *)(REG_SIOMULTI0 + i * 2) != 0xffff) {
        break;
      }
      k >>= 1;
    }

    k &= 0x0e; /* 4P-2P: d3-d1 is 1 */
    mp -> response_bit = k;

    /* The machines that are recognized as client or slave
     * must be SLAVE_CLIENT_INFO sss 0 ccc 0.
     */
    for (i = nchild; i != 0; i--) {
      j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
      if (mp -> client_bit & (1 << i)) {
        if (j != ((MULTIBOOT_SLAVE_CLIENT_INFO << 8)
                  | (1 << i))) {
          /* Needs to conduct recognition process again */
          k = 0;
          break;
        }
      }
      if (mp -> slave_bit & (0x10 << i)) {
        if (j != ((MULTIBOOT_SLAVE_CLIENT_INFO << 8)
                  | (0x10 << i))) {
          /* Needs to conduct re-recognition process */
          k = 0;
          break;
        }
      }
    }

    mp -> client_bit &= k;
    mp -> slave_bit &= k;

    if (k == 0) {
      /* Keep the length of time until re-recognition process constant 
        * until at least one of client or slave returns a value other than 0xffff*/
      mp -> check_wait = MULTIBOOT_CONNECTION_CHECK_WAIT;
    }
    
    if (mp -> check_wait) {
      mp -> check_wait--;
    } else {
      /* If the machine responded and the status of client and slave do not match,
       * conduct re-recognition process.*/
      if (mp -> response_bit !=
          ((mp -> slave_bit << 4)
           | (mp -> client_bit))) {
        MultiBootStartProbe(mp);
        goto case_1;
      }
    }
    
output_master_info:
    /* Output MASTER_INFO sss 0 ccc 0.     */
    return MultiBootSend(mp,
                        (MULTIBOOT_MASTER_INFO << 8)
                        |(mp -> slave_bit << 4)
                        | mp -> client_bit);
case_1:
  case 1:
    /* Start recognition
     * Those with in data being SLAVE_CLIENT_INFO sss 0 ccc 0 are recognized.
     */
    mp -> probe_target_bit = 0;
    for (i = nchild; i != 0; i--) {
      j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
      if ((j >> 8) == MULTIBOOT_SLAVE_CLIENT_INFO) {
        /* Check the correctness of sss 0 ccc 0 within the possible range.
         * if 4P, it is 0x80 or 0x08
         * If 3P, it is 0x40 or 0x04
         * If 2P, it is 0x20 or 0x02
         * It is invalid if other than above.
         */
        MultiBoot_required_data[i - 1] = j; /* The same value must be used for the next process. */
        j &= 0xff;
        if (j == (0x10 << i) || j == (0x01 << i)) {
          mp -> probe_target_bit |= j;
        }
      }
    }

    /* Send MASTER_START_PROBE sss 0 ccc 0.
     * sss and ccc here are the bits that are recognized.
     * When it is not possibly either sss or ccc, master does not recognize.
     */
    
    mp -> probe_count = 2;
    return MultiBootSend(mp,
                         (MULTIBOOT_MASTER_START_PROBE << 8)
                        | mp -> probe_target_bit);

  case 2:
    /* Has to be SLAVE_CLIENT_INFO sss 0 ccc 0.
     * Output Header  +0,+1 bytes.
     */
    for (i = nchild; i != 0; i--) {
      if (mp -> probe_target_bit & (1 << i)) {
        j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
        if (j != MultiBoot_required_data[i - 1]) {
          /* Abnormality generates when client recognized */
          mp -> probe_target_bit ^= 1 << i;
        }
      }
    }
    goto output_header;

  case 0xfe:
    /* Sent MASTER_START_DL
     * It should be SLAVE_CLIENT_DLREADY
     * What are you going to do with lower order?
     */
    for (i = nchild; i != 0; i--) {
      j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
      if (mp -> probe_target_bit & (0x11 << i)) {
        if ((j >> 8) != MULTIBOOT_SLAVE_CLIENT_DLREADY) {
          MultiBootInit(mp);
          return MULTIBOOT_ERROR_NO_DLREADY; /* It did not response that it is ready for download. */
        }
      }
    }

    i = MultiBoot(mp);

    if (i == 0) {
      /* complete
       * Set mp -> probe_count as 0xf0 (Transfer succeeded).
       */
      mp -> probe_count = 0xf0;
      return 0;
    }
    MultiBootInit(mp);
    /* If system call fails, it is possible that client is still in the data receiving status.
     * For this reason, do not send out anything, including MASTER_INFO, during the time
     * in which "client becomes time out error" until retrying.
     */
    mp -> check_wait = MULTIBOOT_CONNECTION_CHECK_WAIT * 2;
    return MULTIBOOT_ERROR_BOOT_FAILURE; /* Transfer failed */

  case 0xff:
    /* Master server start request is out.
     * If SLAVE_CLIENT_INFO sss 0 ccc 0, client and slave are not ready to download.
     * If all slaves and clients are SLAVE_CLIENT_DLREADY, call for system call and 
     * transfer boot program.
     */
    k = 1; /* Is it okay to start download ? */
    for (i = MULTIBOOT_NCHILD; i != 0; i--) {
      j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
      /* Data for handshake from clients and slaves.
       * Regardless whether recognized or notm save data on all the machines.
       */
      mp -> client_data[i - 1] = j;
      if (mp -> probe_target_bit & (0x11 << i)) {
        if ((j >> 8) != MULTIBOOT_SLAVE_CLIENT_INFO
            && (j >> 8) != MULTIBOOT_SLAVE_CLIENT_DLREADY) {
          MultiBootInit(mp);
          return MULTIBOOT_ERROR_NO_DLREADY; /* It did not respond that it is ready for download. */
        }
        if (j == MultiBoot_required_data[i - 1]) {
          /* It is SLAVE_CLIENT_INFO sss 0 ccc 0.
           * If even one machine is not ready to download, do not start downloading. */
          k = 0;
        }
      }
    }

    if (k == 0) {
      /* Do not start downloading. */
      goto output_request_dl;
    }
    /* All the machines are ready for download. */
    mp -> probe_count = 0xfe;

    k = 0x11;
    for (i = MULTIBOOT_NCHILD; i != 0; i--) {
      /* Handshake data */
      k += mp -> client_data[i - 1];
    }
    mp -> handshake_data = k;
    return MultiBootSend(mp,
                         (MULTIBOOT_MASTER_START_DL << 8) | (k & 0xff));

output_request_dl:
    /* Send download preparation request */
    return MultiBootSend(mp,
                         (MULTIBOOT_MASTER_REQUEST_DLREADY << 8)
                         | mp -> palette_data);

  /* probe_count 0xf0 is used as a value that indicates that transfer has ended.*/
  default:
    /* 4-...: middle of the recognition process
     * 4 -> +0th, 1st byte
     * 6 -> +2,3
     * 8 -> +4,5
     *  :
     * 0xc2 -> +0xbe-th, 0xbf-th byte
     * Reads from slave and outputs from master.
     */

    /* When client is recognized,
     * MASTER_START_PROBE - 1, ..-2, ..., 0 comes.
     * 0x61 - 1,               0x5f
     * Lower order is 000 0 ccc 0 
     */
    for (i = 3; i != 0; i--) {
      if (mp -> probe_target_bit & (1 << i)) {
        j = *(vu16 *)(REG_SIOMULTI0 + i * 2);
        if ((j >> 8) != (MULTIBOOT_MASTER_START_PROBE + 1 - (mp -> probe_count >> 1))
            || ((j & 0xff) != (1 << i))) {
          /* Abnormality generates when client recognized */
          mp -> probe_target_bit ^= 1 << i;
        }
      }
    }

    if (mp -> probe_count == 0xc4) {
      /* Among those recognized, qualify the ones that lasted until end as slave and client      
       * However, determine clearly whether or not they can be recognized as slaves for sure with other functions.
       * The content of the header is not determined here.
       */
      mp -> client_bit = mp -> probe_target_bit & 0x0e;
      mp -> slave_bit  = mp -> probe_target_bit >> 4;
      mp -> probe_count = 0;
      goto output_master_info;
    }

output_header:
    /* When there is nothing more to recognize, end as error even in the middle. */
    if (mp -> probe_target_bit == 0) {
      MultiBootInit(mp);
      return MULTIBOOT_ERROR_NO_PROBE_TARGET; /* There is nothing to be recognized. */
    }
    
    mp -> probe_count += 2;
    if (mp -> probe_count == 0xc4) {
      /* Send MASTER_SLAVE_INFO sss 0 ccc 0 to obtain the last data.       
      * Otherwise the timing is not right.
       */
      goto output_master_info;
    }
    return MultiBootSend(mp,
                         (mp -> masterp[mp -> probe_count - 4 + 1] << 8)
                        | mp -> masterp[mp -> probe_count - 4]);
  }
  /* never comes here */
}


/*------------------------------------------------------------------*/
/*                       Send Data                                 */
/*------------------------------------------------------------------*/

/*
 * If connect status is abnormal, non-0
 */
static int MultiBootSend(MultiBootParam *mp, u16 data)
{
  int i;

  /* If SC7 is on at this point, something is wrong.
   * Cable connection (with JOY, etc.) may be abnormal which caused time out on communication.
   * When it does not become error.
   * Since it may be the first communication (since cable is reconnected),
   * do not check connect ID.
   */
  i = *(vu16 *)REG_SIOCNT & (SIO_MULTI_BUSY | SIO_MULTI_SD | SIO_MULTI_SI);
  if (i != SIO_MULTI_SD) {
    MultiBootInit(mp);
    return i ^ SIO_MULTI_SD;
  }
  *(vu16 *)REG_SIODATA8 = data;
  *(vu16 *)REG_SIOCNT = SIO_MULTI_MODE | SIO_START | SIO_115200_BPS;
  

  mp -> sendflag = 1;
  return 0;
}


/*------------------------------------------------------------------*/
/*               Start Recognizing Slave Server and Client             */
/*------------------------------------------------------------------*/

void MultiBootStartProbe(MultiBootParam *mp)
{
  if (mp -> probe_count != 0) {
    MultiBootInit(mp);
    return;
  }
  mp -> check_wait = 0;
  mp -> probe_count = 1;
}


/*------------------------------------------------------------------*/
/*                   Start Transferring from Master Server                       */
/*------------------------------------------------------------------*/

void MultiBootStartMaster(MultiBootParam *mp, u8 *srcp, int length, u8 palette_color, s8 palette_speed)
{
  int i;
  if (mp -> probe_count != 0
      || mp -> client_bit == 0
      || mp -> check_wait != 0
      ) {
    /* It is either processing the recognition process or cannot process.*/
    MultiBootInit(mp);
    return;
  }
  mp -> boot_srcp = srcp;
  length = (length + 15) & ~15; /* 16-byte unit */
  if (length <= MULTIBOOT_SEND_SIZE_MIN || length > MULTIBOOT_SEND_SIZE_MAX) {
    /* Abnormal number of transfer byte */
    MultiBootInit(mp);
    return;
  }
  mp -> boot_endp = srcp + length;
  switch (palette_speed) {
  case -4:
  case -3:
  case -2:
  case -1:
    i = (palette_color << 3) | (3 - palette_speed);
    break;
  case 0:
    i = 0x38 | palette_color;
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    i = (palette_color << 3) | (palette_speed - 1);
    break;
  }
  mp -> palette_data = ((i & 0x3f) << 1) | 0x81;
  mp -> probe_count = 0xff;
}


/*------------------------------------------------------------------*/
/*                       Check If Transfer has Ended                           */
/*------------------------------------------------------------------*/

int MultiBootCheckComplete(MultiBootParam *mp)
{
  if (mp -> probe_count == 0xf0) {
    /* Transfer has ended */
    return 1;
  }
  /* Either recognizing, transfer not being started or failing transfer */
  return 0;
}


/* End of AgbMultiBoot.c */
