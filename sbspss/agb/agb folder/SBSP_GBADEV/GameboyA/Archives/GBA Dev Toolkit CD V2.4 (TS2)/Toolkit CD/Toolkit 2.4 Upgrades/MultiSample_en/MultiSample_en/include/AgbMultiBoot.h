/********************************************************************/
/*          AgbMultiBoot.h                                          */
/*            AGB Multi-play Boot Library Declaration               */
/*                                                                  */
/*          Copyright (C) 2000 NINTENDO Co.,Ltd.                    */
/********************************************************************/
#ifndef _AGB_MULTIBOOT_H
#define _AGB_MULTIBOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <AgbTypes.h>


#define MULTIBOOT_NCHILD 3             
#define MULTIBOOT_HEADER_SIZE 0xc0    
#define MULTIBOOT_SEND_SIZE_MIN 0x100   
#define MULTIBOOT_SEND_SIZE_MAX 0x40000 

// Multi-play boot parameter structure
typedef struct {
  u32 system_work[5];   
  u8 handshake_data;
  u8 padding[3];
  u8 probe_count;       
  u8 client_data[MULTIBOOT_NCHILD];
  u8 palette_data;      
  u8 response_bit;     
  u8 client_bit;        
  u8 slave_bit;        
  u8 *boot_srcp;     
  u8 *boot_endp;    
  u8 *masterp;      
  u8 *headerp[MULTIBOOT_NCHILD]; 
  u32 system_work2[4];  
  u8 sendflag;         
  u8 probe_target_bit; 
  u8 check_wait;     
  u8 server_type;    
} MultiBootParam;

#define MULTIBOOT_ERROR_04              0x04
#define MULTIBOOT_ERROR_08              0x08
#define MULTIBOOT_ERROR_0c              0x0c
#define MULTIBOOT_ERROR_80              0x80
#define MULTIBOOT_ERROR_84              0x84
#define MULTIBOOT_ERROR_88              0x88
#define MULTIBOOT_ERROR_8c              0x8c
#define MULTIBOOT_ERROR_NO_PROBE_TARGET 0x40
#define MULTIBOOT_ERROR_NO_DLREADY      0x50
#define MULTIBOOT_ERROR_BOOT_FAILURE    0x60


/* Chattering avoidance wait (frame) until connection check is re-tried after an 
   error or when a value other than 0xffff returns.  Since there are 11 frames 
   in the time out of the client, be sure to set the value longer than that.  
   Normally, MASTER_INFO is sent during this period, but do not send anything 
   during this period if there is an error with system call. Then, send 
   MASTER_INFO for the period of 15 frames.
*/
#define MULTIBOOT_CONNECTION_CHECK_WAIT 15


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif    /* _AGB_MULTIBOOT_H */
/* End of AgbMultiBoot.h */
