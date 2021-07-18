/********************************************************************/
/*          main.c                                                  */
/*            simple�i��{�T���v���j�̃\�[�X                        */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
//#define CODE32
#include "data.h"


/*-------------------- �O���[�o�� �ϐ�  ----------------------------*/

    u16      Cont, Trg;                  // �L�[����

    u32      IntrMainBuf[0x200];         // ���荞�݃��C�����[�`���p�o�b�t�@

    u16      BgBak[32*32];               // BG  �o�b�N�A�b�v
    OamData  OamBak[128];                // OAM �o�b�N�A�b�v


/*---------------------- �T�u���[�`��  -----------------------------*/

void KeyRead(void);
void ObjSnakeMove(void);


/*------------------------------------------------------------------*/
/*                      ���荞�݃e�[�u��                            */
/*------------------------------------------------------------------*/
#if 0
typedef void (*IntrFuncp)(void);
void IntrDummy(void);
void VBlankIntr(void);

const IntrFuncp IntrTable[14] = {
    VBlankIntr,     // �u�u�����N���荞��
    IntrDummy,      // �g�u�����N���荞��
    IntrDummy,      // �u�J�E���^��v���荞��
    IntrDummy,      // �^�C�}�[�O���荞��
    IntrDummy,      // �^�C�}�[�P���荞��
    IntrDummy,      // �^�C�}�[�Q���荞��
    IntrDummy,      // �^�C�}�[�R���荞��
    IntrDummy,      // �V���A���ʐM���荞��
    IntrDummy,      // �c�l�`�O���荞��
    IntrDummy,      // �c�l�`�P���荞��
    IntrDummy,      // �c�l�`�Q���荞��
    IntrDummy,      // �c�l�`�R���荞��
    IntrDummy,      // �L�[���荞��
    IntrDummy,      // �J�Z�b�g���荞��
};
#endif

/*==================================================================*/
/*                      ���C�����[�`��                              */
/*==================================================================*/
extern void intr_main(void);
extern void initVBlank(void);
extern void waitForVBlank(void);


void AgbMain(void)
{
    s32    i;

    DmaClear(3, 0, EX_WRAM,  EX_WRAM_SIZE,          32);   // CPU�O�����[�NRAM �N���A
    DmaClear(3, 0, CPU_WRAM, CPU_WRAM_SIZE - 0x200, 32);   // CPU�������[�NRAM �N���A
//  DmaClear(3, 0, VRAM,     VRAM_SIZE,             32);   //     VRAM �N���A
//  DmaClear(3, 0, OAM,      OAM_SIZE,              32);   //      OAM �N���A
//  DmaClear(3, 0, PLTT,     PLTT_SIZE,             32);   // �p���b�g �N���A

		initVBlank();

    //DmaCopy(3, intr_main, IntrMainBuf, sizeof(IntrMainBuf), 32);// ���荞�݃��C�����[�`�� �Z�b�g
    //*(vu32 *)INTR_VECTOR_BUF = (vu32 )IntrMainBuf;

    DmaArrayCopy(3, CharData_Sample, BG_VRAM+0x8000, 32);  //  BG�L�����N�^ �Z�b�g
    DmaArrayCopy(3, CharData_Sample, OBJ_MODE0_VRAM, 32);  // OBJ�L�����N�^ �Z�b�g
    DmaArrayCopy(3, PlttData_Sample, BG_PLTT,        32);  //  BG�p���b�g   �Z�b�g
    DmaArrayCopy(3, PlttData_Sample, OBJ_PLTT,       32);  // OBJ�p���b�g   �Z�b�g

    DmaArrayCopy(3, BgScData_Sample, BgBak,          32);  // BG�X�N���[��  �Z�b�g
    DmaArrayCopy(3, BgBak,           BG_VRAM,        32);
    DmaArrayCopy(3, OamData_Sample,  OamBak,         32);  //          OAM  �Z�b�g
    for (i=0; i<94; i++) {                            // OAM ������
        OamBak[i] = *(OamData *)OamData_Sample;
        //OamBak[i].CharNo = '@' + DivRem(i, 64);
        OamBak[i].CharNo = '@' + (i % 64);

        OamBak[i].VPos += i<<2;
        OamBak[i].HPos += i<<2;
    }
    DmaArrayCopy(3, OamBak,          OAM,            32);

    *(vu16 *)REG_BG0CNT =                             // BG�R���g���[�� �Z�b�g
            BG_COLOR_16 | BG_SCREEN_SIZE_0 | BG_PRIORITY_0
            | 0 << BG_SCREEN_BASE_SHIFT | 2 << BG_CHAR_BASE_SHIFT ;

    *(vu16 *)REG_IME   = 1;                           // IME �Z�b�g
    *(vu16 *)REG_IE    = V_BLANK_INTR_FLAG;           // V�u�����N��������
    *(vu16 *)REG_STAT  = STAT_V_BLANK_IF_ENABLE;

    *(vu16 *)REG_DISPCNT = DISP_MODE_0 | DISP_OBJ_ON | DISP_BG0_ON; // LCDC ON

    while(1) {
        KeyRead();                                  // �L�[����
        if (Trg & A_BUTTON)                         // �L�����N�^ �ύX
            for (i=0; i<128; i++)    OamBak[i].CharNo++;
        if (Trg & B_BUTTON)
            for (i=0; i<128; i++)    OamBak[i].CharNo--;
        if (Cont & PLUS_KEY_MASK)                   // OBJ �ړ�
            ObjSnakeMove();

        //VBlankIntrWait();                           // V�u�����N�����I���҂�
				waitForVBlank();

    }
}


/*==================================================================*/
/*                      ���荞�݃��[�`��                            */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      �u�u�����N����                              */
/*------------------------------------------------------------------*/

void VBlankIntr(void)
{
    DmaArrayCopy(3, BgBak,  BG_VRAM, 32);           // BG�X�N���[�� �Z�b�g
    DmaArrayCopy(3, OamBak, OAM,     32);           // OAM �Z�b�g

    *(u16 *)INTR_CHECK_BUF = V_BLANK_INTR_FLAG;     // V�u�����N�����`�F�b�N�̃Z�b�g
}

/*------------------------------------------------------------------*/
/*                      ���荞�� �_�~�[���[�`��                     */
/*------------------------------------------------------------------*/

void IntrDummy(void)
{
}

/*==================================================================*/
/*                      �T�u���[�`��                                */
/*==================================================================*/

/*------------------------------------------------------------------*/
/*                      �L�[�ǂݍ���                                */
/*------------------------------------------------------------------*/

void KeyRead(void)
{
    u16 ReadData = (*(vu16 *)REG_KEYINPUT ^ 0xffff);
    Trg  = ReadData & (ReadData ^ Cont);            // �g���K ����
    Cont = ReadData;                                //   �x�^ ����
}

/*------------------------------------------------------------------*/
/*                      �n�a�i�ړ� ���[�`��                         */
/*------------------------------------------------------------------*/

void ObjSnakeMove(void)
{
    u8   i;
    for (i=127; i>0; i--) {
        OamBak[i].VPos = OamBak[i-1].VPos;
        OamBak[i].HPos = OamBak[i-1].HPos;
    }
    if (Cont & U_KEY)    OamBak[0].VPos -= 4;
    if (Cont & D_KEY)    OamBak[0].VPos += 4;
    if (Cont & L_KEY)    OamBak[0].HPos -= 4;
    if (Cont & R_KEY)    OamBak[0].HPos += 4;
}

