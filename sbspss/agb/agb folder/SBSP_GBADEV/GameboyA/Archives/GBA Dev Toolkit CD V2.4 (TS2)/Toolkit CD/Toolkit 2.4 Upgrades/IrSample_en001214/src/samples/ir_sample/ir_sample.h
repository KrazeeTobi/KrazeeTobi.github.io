/********************************************************************/
/*					main.h											*/
/*      			AGB IR通信 サンプルプログラム宣言		    	*/
/*					ver1.0											*/
/*					Copyright (C) 2000 NINTENDO CO.,Ltd.			*/
/********************************************************************/

#ifndef	_AGB_SAMPLE_H
#define	_AGB_SAMPLE_H

#include <AgbTypes.h>
#include <AgbIr.h>



u8		IR_SEND_CGB	( void);
u8		IR_RECV_CGB	( void);

void	PrintMenu     ( void)     ;
void	PrintParameter( irResult*);

/*-------------------------- データ  -------------------------------*/

extern u32 CharData_Sample[8*0xe0];

extern u16 PlttData_Sample[16][16];



#endif	/* _AGB_SAMPLE_H */
