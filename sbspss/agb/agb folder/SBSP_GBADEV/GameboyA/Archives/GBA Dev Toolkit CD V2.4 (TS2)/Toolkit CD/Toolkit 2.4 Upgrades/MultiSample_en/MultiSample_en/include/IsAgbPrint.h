
#ifndef	__ISAGBPRN_H__
#define	__ISAGBPRN_H__

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////
/// Copyright 1999 INTELLIGENT SYSTEMS Co.,Ltd.
/// IS-AGB-EMULATOR
/// PRINT DEBUG LIBRARY [libagbprn.a]
/////////////////////////////////////////////////////////////////////////
/// Function Description
/// 
/// [Initialize Print Debug]
/// void AGBPrintInit(void);
///		This initializes the buffer to be used in print debugging. 
///		Currently 0x08fd0000 - 0x08fdffff is used. In the future, it will
///		be possible for the user to change this address to any address 
///		using the host application. 
///
/// [Output 1 Character]
///	 void AGBPutc(unsigned char cChar);
///		 cChar: Store the one character to be output in the output buffer. 
///			If the buffer is full, '\n' will be output to call 
///			AGBPrintFlush(). 
///
/// [Output Character String]
/// void AGBPrint(unsigned char* pBuf);
///		 pBuf: Store the character string in the output buffer.  
///			AGBPutc() is called until '\0' appears.
///
/// [Flush Character String]
/// void AGBPrintFlush(void);
///		 Data are actually output to the host-side by flushing the 
///		 character string that was output. 
///
/// [Macro to Check Program Normalcy]
/// AGB_ASSERT(evaluation equation);
///		 The evaluation equation is an evaluation equation written in C.  
///		 If the value of the evaluation equation is true (not ZERO), the 
///		 next program is executed.  If it is false (ZERO), the source 
///		 filename defined by AGB_ASSERT(), the line number therein, and 
///		 the evaluation equation are displayed, and the program is 
///		 suspended.
///		 
/// [Macro to Check Program Normalcy]
/// AGB_WARNING( expression );
///		 This is used in the same way as AGB_ASSERT().  It differs from 
///		 AGB_ASSERT() in that ASSERT does not perform any processing 
///		 after the program has been suspended (hang status), while 
///		 ABG_WARNING continues to run the program. 
///		 
/////////////////////////////////////////////////////////////////////////
/// Precautions
/// 
///  - This library is for use with gcc. 
///  - Even though a character string is output, it doesn't mean that it is 
///	output directly to the host. It is output to the host when the buffer
///	becomes full, or when a line feed '\n' is output. 
///  - The user must not change the area specified by the print debug. 
///  - Due to the IS-AGB-EMULATOR hardware, [Temporary] interruptions are 
///	prohibited and the memory wait is changed while data are being sent to
///	the host (while AGBFlash() is being called).  Because of this, this is
///	not necessarily incorporated into the main loop, etc. of the program. 
///	Special techniques, such as pressing a button, are necessary to output 
///	in special cases.  
///  - Be sure to specify the -mthumb-interwork option for the gcc compiler. 
///  - When the ROM is created at the time of shipping, all of the print debug
///	functions can be deleted by defining NDEBUG. 
///

/////////////////////////////////////////////////////////////////////////
/// Example of Makefile Link Line
/// -L. -l isagbprn

/////////////////////////////////////////////////////////////////////////
/// Sample Application
/// 
/// AGBPrintInit();
///
/// while(1) {
///		AGBPrint("TEST PROGRAM \n");
///			pSelf->X++;
///			AGB_ASSERT((pSelf != NULL) && (pSelf->X > 0));
/// }
///
///

/////////////////////////////////////////////////////////////////////////
///

#ifdef NDEBUG
	#define AGBPrintInit()				((void*)0)
	#define AGBPutc(cChar)				((void*)0)
	#define AGBPrint(pBuf)				((void*)0)
	#define AGBPrintFlush()				((void*)0)
	#define AGBAssert(file,line,info)		((void*)0)
#else
	void AGBPrintInit(void);
	void AGBPutc(unsigned char pBuf);
	void AGBPrint(unsigned char* pBuf);
	void AGBPrintFlush(void);
	void AGBAssert(char* pFile, int nLine, char* pExpression, int nStopProgram);
#endif

/////////////////////////////////////////////////////////////////////////
///

#undef AGB_ASSERT
#ifdef NDEBUG
#define	AGB_ASSERT(exp)	(0)
#else
#define	AGB_ASSERT(exp)	(exp) ? (0) : AGBAssert(__FILE__, __LINE__, #exp, 1);
#endif

#undef AGB_WARNING
#ifdef NDEBUG
#define	AGB_WARNING(exp)	 (0)
#else
#define	AGB_WARNING(exp)	 (exp) ? (0) : AGBAssert(__FILE__, __LINE__, #exp, 0);
#endif

/////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}	 // extern "C"
#endif

#endif

