/********************************************************************/
/*          MultiSio.h                                              */
/*            �}���`�v���C�ʐM���C�u�����O���錾                    */
/*            �i�^�C�}�[���荞�ݑ��M�j                              */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _MULTI_SIO_H
#define _MULTI_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>


// ���L�̐ݒ�l�̓\�t�g�̎d�l�ɍ��킹�čœK�����ĉ������B

#define MULTI_SIO_BLOCK_SIZE        16      // �ʐM�f�[�^�u���b�N�T�C�Y�i�ő�24Byte�j

#define MULTI_SIO_SYNC_DATA         0xfefe  // �����f�[�^�i0x0000�^0xfffa�`0xffff�͋֎~�j

// CPU�������[�NRAM�ɗ]�T���Ȃ���΃R�����g�A�E�g���ĉ������B
#define MULTI_SIO_DI_FUNC_FAST              // SIO���荞�݋֎~�֐��������t���O�iCPU����RAM���s�j


// �J���r���ł� NDEBUG �𖢒�`�ɂ��ĉ��L�̒l�� 0 �ɂ��A
// �ŏI�`�F�b�N�i�K�ł͒�`���� 600 �ɕύX������Ԃœ���m�F�����ĉ�����
// �i�ݒ�l�𑝂₵�Ă��ʐM�Ԋu�����т邾���ŏ������d���Ȃ邱�Ƃ͂���܂���j�B
//#define NDEBUG                              // Makefile�iMakefileDemo�j�ł̒�`�ł���
#ifdef  NDEBUG
#define MULTI_SIO_INTR_MARGIN       600     // �ʐM���荞�ݔ����덷�ۏؒl
#else
#define MULTI_SIO_INTR_MARGIN       0
#endif

// �ʐM���荞�݂̍ő�x�������L�̒l���傫���Ȃ�ꍇ�͍X�V���ĉ������B
#define MULTI_SIO_INTR_DELAY_MAX    2048    // �ʐM���荞�݋��e�x���N���b�N��

#define MULTI_SIO_INTR_CLOCK_MAX    512     // �ʐM���荞�ݏ����ő�N���b�N��


#define MULTI_SIO_BAUD_RATE         115200          // �{�[���[�g
#define MULTI_SIO_BAUD_RATE_NO      SIO_115200_BPS  // �{�[���[�g�m��


#define MULTI_SIO_TIMER_NO          3       // �^�C�}�[�m��
#define MULTI_SIO_TIMER_INTR_FLAG   (TIMER0_INTR_FLAG << MULTI_SIO_TIMER_NO)
                                            // �^�C�}�[���荞�݃t���O
#define REG_MULTI_SIO_TIMER         (REG_TM0CNT + MULTI_SIO_TIMER_NO * 4)
#define REG_MULTI_SIO_TIMER_L        REG_MULTI_SIO_TIMER
#define REG_MULTI_SIO_TIMER_H       (REG_MULTI_SIO_TIMER + 2)
                                            // �^�C�}�[���W�X�^

// �^�C�}�[�J�E���g�b��l�͒ʐM�f�[�^�u���b�N�T�C�Y����Z�o���܂��B
#define MULTI_SIO_TIMER_COUNT_TMP   (SYSTEM_CLOCK/60/((2 + 4 + MULTI_SIO_BLOCK_SIZE + 14)/(16/8)) \
                                    + MULTI_SIO_INTR_MARGIN)
                                            // �^�C�}�[�J�E���g�b��l
#define MULTI_SIO_TIMER_COUNT_MIN   (SYSTEM_CLOCK/MULTI_SIO_BAUD_RATE*(1+16+1)*4 \
                                    + MULTI_SIO_INTR_DELAY_MAX + MULTI_SIO_INTR_CLOCK_MAX \
                                    + MULTI_SIO_INTR_MARGIN)
                                            // �^�C�}�[�J�E���g�ŏ��l
#define MULTI_SIO_TIMER_COUNT_MAX   0x10000 // �^�C�}�[�J�E���g�ő�l
#define MULTI_SIO_TIMER_COUNT       ((MULTI_SIO_TIMER_COUNT_TMP > MULTI_SIO_TIMER_COUNT_MAX)   \
					                ? MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_MAX    \
					                : ((MULTI_SIO_TIMER_COUNT_TMP < MULTI_SIO_TIMER_COUNT_MIN) \
					                  ? MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_MIN  \
					                  : MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_TMP))
                                            // �^�C�}�[�J�E���g��


// �}���`�v���C�ʐM�p�P�b�g�\����
typedef struct {
    u8  FrameCounter;                       // �t���[���J�E���^
    u8  RecvErrorFlags;                     // ��M�G���[�t���O
    u16 CheckSum;                           // �`�F�b�N�T��
	u16 Data[MULTI_SIO_BLOCK_SIZE/2];       // �ʐM�f�[�^
	u16 OverRunCatch[2];                    // �I�[�o�[�����ی�̈�
} MultiSioPacket;


// �}���`�v���C�ʐM���[�N�G���A�\����
typedef struct {
    u8  Type;                               // �ڑ��֌W�i�e�^�q�j
    u8  State;                              // �ʐM�֐��̏��
    u8  ConnectedFlags;                     // �ڑ������t���O
    u8  RecvSuccessFlags;                   // ��M�����t���O

    u8  SyncRecvFlag[4];                    // �����f�[�^��M�m�F�t���O
    u8  SyncAdjustCounter;                  // ���������J�E���^

	u8  Padding0[1];

	s8  SendBufCounterInit;                 // ���M�o�b�t�@�J�E���^�����l

    u8  SendFrameCounter;                   // ���M�t���[���J�E���^
    u8  RecvFrameCounter[4][2];             // ��M�t���[���J�E���^

    s32 SendBufCounter;                     // ���M�o�b�t�@�J�E���^
    s32 RecvBufCounter[4];                  // ��M�o�b�t�@�J�E���^

    u16 *NextSendBufp;                      // ���M�o�b�t�@�|�C���^
    u16 *CurrentSendBufp;
    u16 *CurrentRecvBufp[4];                // ��M�o�b�t�@�|�C���^
    u16 *LastRecvBufp[4];
    u16 *RecvCheckBufp[4];

    MultiSioPacket  SendBuf[2];             // ���M�o�b�t�@�i�_�u���o�b�t�@�j
    MultiSioPacket  RecvBuf[4][3];          // ��M�o�b�t�@�i�g���v���o�b�t�@�j
} MultiSioArea;


extern u32 RecvFuncBuf[];                   // CPU����RAM���s�p�o�b�t�@
extern u32 IntrFuncBuf[];


/*------------------------------------------------------------------*/
/*                      �}���`�v���C�ʐM������                      */
/*------------------------------------------------------------------*/

extern void MultiSioInit(void);

//�E�V���A���ʐM���[�h���}���`�v���C���[�h�ɂ��܂��B
//�E���W�X�^��o�b�t�@�̏��������s�Ȃ��܂��B

/*------------------------------------------------------------------*/
/*                      �}���`�v���C�ʐM���C��                      */
/*------------------------------------------------------------------*/

extern u32  MultiSioMain(void *Sendp, void *Recvp);

//�E�܂��A�e�@���q�@���𔻕ʂ��A�e�@�ƔF�����ꂽ�ꍇ�͒ʐM���J�n���܂��B
//�EMultiSioSendDataSet()���Ăяo���A���M�f�[�^���Z�b�g���܂��B
//�EMultiSioRecvDataCheck()���Ăяo���A����Ɏ�M�ł������ǂ����𒲂ׁA
//  Recvp�֎�M�f�[�^���R�s�[���܂��B
//
//�E�P�t���[�����̂ł��邾���߂��^�C�~���O�ŌĂяo�����悤�ɂ��ĉ������B
//�E���������ɏ��X���Ԃ��|����ꍇ������܂��B
//�E�����������ɂ̓t���O�f�[�^�iSIO_SYNC_DATA�j�ƈ�v����f�[�^��
//  ���M���Ȃ��������S�ł��B
//�E�P�x�F�����ꂽ�{�̂���̉������Ȃ��Ȃ�Ɠ��������������܂��̂ŁA
//  ��M���s����ɂȂ�܂��B
//
//�E�����F
//    void *Sendp  ���[�U���M�o�b�t�@�|�C���^
//    void *Recvp  ���[�U��M�o�b�t�@�|�C���^

/*------------------------------------------------------------------*/
/*    		 		    �}���`�v���C�ʐM���荞��                    */
/*------------------------------------------------------------------*/

extern void MultiSioIntr(void);

//�E�ʐM���荞�ݎ��Ɋe�{�̂���̎�M�f�[�^���e��M�o�b�t�@�֊i�[���A
//  ���M�o�b�t�@�̃f�[�^�����W�X�^�փZ�b�g���܂��B
//�E�e�@�ł���Α��M���ĊJ���܂��B
//
//�E�q�@�͒ʐM���荞�݂Őe�@�̓^�C�}�[���荞�݂ŌĂ΂��悤��
//  �v���O���~���O���ĉ������B
//�E�K���P�p�P�b�g�iOverRunCatch[]�ȊO�j���P�t���[���œ]���ł���悤��
//  �ݒ�l�𒲐����ĉ������B


/*------------------------------------------------------------------*/
/*                      ���M�f�[�^ �Z�b�g                           */
/*------------------------------------------------------------------*/

extern void MultiSioSendDataSet(void *Sendp);

//�E���[�U���M�o�b�t�@�̃f�[�^�𑗐M�o�b�t�@�փZ�b�g���܂��B
//
//�EMultiSioMain()����Ăяo����܂��B
//�E���ڌĂяo���K�v�͂���܂���B
//
//�E�����F
//    void *Sendp  ���[�U���M�o�b�t�@�|�C���^

/*------------------------------------------------------------------*/
/*                      ��M�f�[�^ �`�F�b�N                         */
/*------------------------------------------------------------------*/

extern u32  MultiSioRecvDataCheck(void *Recvp);

//�E����Ɏ�M�ł������ǂ������`�F�b�N���A����ł���Ύ�M�f�[�^��
//  ���[�U��M�o�b�t�@�փR�s�[���܂��B
//
//�EMultiSioMain()����Ăяo����܂��B
//�E���ڌĂяo���K�v�͂���܂���B
//
//�E�����F
//    void *Recvp  ���[�U��M�o�b�t�@�|�C���^


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _MULTI_SIO_H */
