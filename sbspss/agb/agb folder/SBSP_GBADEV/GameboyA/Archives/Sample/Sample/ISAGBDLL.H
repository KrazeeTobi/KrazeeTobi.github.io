#ifndef __ISAGBDLL_H__
#define __ISAGBDLL_H__


/////////////////////////////////////////////////////////////////////////
/// Copyright (C) 1999 INTELLIGENT SYSTEMS Co., Ltd.
/// All rights reserved.
///
/// IS-AGB-EMULATOR [ISAGB.DLL]
///

#ifdef __cplusplus
extern "C" {
#endif

// dll internal name
#define	AGB_FUNC_FINDFIRST	"AGBFindFirst"
#define AGB_FUNC_FINDNEXT	"AGBFindNext"
#define AGB_FUNC_FINDCLOSE	"AGBFindClose"
#define	AGB_FUNC_OPEN		"AGBOpen"
#define	AGB_FUNC_CLOSE		"AGBClose"
#define	AGB_FUNC_READ		"AGBRead"
#define	AGB_FUNC_WRITE		"AGBWrite"
#define	AGB_FUNC_GO		"AGBGo"
#define	AGB_FUNC_RESET		"AGBReset"

// find struct
typedef struct {
  INT m_nHost;	// SCSI-HOST
  INT m_nId;	// SCSI-ID
} AGBFindData;

// export function
typedef HANDLE	(_cdecl *AGBFINDFIRST)(AGBFindData* pFindData);
typedef BOOL	(_cdecl *AGBFINDNEXT)(HANDLE hFind, AGBFindData* pFindData);
typedef void	(_cdecl *AGBFINDCLOSE)(HANDLE hFind);
typedef HANDLE	(_cdecl *AGBOPEN)(INT nHost, INT nID);
typedef VOID	(_cdecl *AGBCLOSE)(HANDLE hAGB);
typedef INT	(_cdecl *AGBWRITE)(HANDLE hAGB, BYTE* pBuf, ULONG adrs, ULONG len);
typedef INT	(_cdecl *AGBREAD)(HANDLE hAGB, BYTE* pBuf, ULONG adrs, ULONG len);
typedef BOOL	(_cdecl *AGBGO)(HANDLE hAGB);
typedef	BOOL	(_cdecl *AGBRESET)(HANDLE hAGB, BOOL bOnOff);

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////////
///

#endif
