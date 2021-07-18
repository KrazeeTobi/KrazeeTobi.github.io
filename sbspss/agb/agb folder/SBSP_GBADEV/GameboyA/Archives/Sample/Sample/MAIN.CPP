///////////////////////////////////////////////////////////
/// IS-AGB-EMULATOR
/// Copyright 1999 INTELLIGENT SYSTEMS Co.,Ltd.
/// 
/// ISAGB.DLL smaple program
///
/// Win32 console application sample.exe
///
/// このサンプルは、IS-AGB-EMULATORを使用し、
/// 単純なバイナリファイルをダウンロードするものです。
///
/// Last Modified:1999/12/16

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "isagbdll.h"

/////////////////////////////////////////////////////////////
/// CAGB
///
/// サンプルの説明を簡素化する為の、サンプルクラスです。
/// 必要に合わせて、変更・修正を行って下さい。
///

#define ISAGBDLL_NAME "isagb.dll"

class CAGB {
protected:
  HINSTANCE m_hDLL;
	HANDLE	m_hAGB;
  AGBFINDFIRST  m_lpfnFindFirst;
  AGBFINDNEXT   m_lpfnFindNext;
  AGBFINDCLOSE  m_lpfnFindClose;
  AGBOPEN       m_lpfnOpen;
  AGBCLOSE      m_lpfnClose;
  AGBWRITE      m_lpfnWrite;
  AGBREAD       m_lpfnRead;
  AGBGO         m_lpfnGo;
	AGBRESET			m_lpfnReset;
	
public:
  CAGB();
  virtual ~CAGB();
  enum { 
    ERR_SUCCESS, 
    ERR_CANNOT_FOUND_DLL, 
    ERR_CANNOT_OPEN,
  };
protected:
  HANDLE	AGBOpen(INT nHost, INT nID)                           { return (m_lpfnOpen) ? (*m_lpfnOpen)(nHost, nID) : NULL;			}
public:
  HANDLE  FindFirst(AGBFindData* pFindData)                     { return (m_lpfnFindFirst) ? (*m_lpfnFindFirst)(pFindData) : NULL;		}
  BOOL    FindNext(HANDLE hFind, AGBFindData* pFindData)        { return (m_lpfnFindNext) ? (*m_lpfnFindNext)(hFind, pFindData) : FALSE;	}
  void    FindClose(HANDLE hFind)                               { if (m_lpfnFindClose) (*m_lpfnFindClose)(hFind);	}
public:
  INT     Open(INT nHost = -1, INT nID = -1);
  VOID		Close()                                               { if (m_lpfnClose) (*m_lpfnClose)(m_hAGB); m_hAGB = NULL;	}
  UINT    Write(BYTE* pBuf, ULONG adrs, ULONG len)              { return (m_lpfnWrite) ? (*m_lpfnWrite)(m_hAGB, pBuf, adrs, len) : 0; }
  UINT    Read(BYTE* pBuf, ULONG adrs, ULONG len)               { return (m_lpfnRead) ? (*m_lpfnRead)(m_hAGB, pBuf, adrs, len) : 0;  }
  BOOL		Go()                                                  { return (m_lpfnGo) ? (*m_lpfnGo)(m_hAGB) : FALSE;  }
	BOOL		Reset(BOOL bOnOff)																		{ return (m_lpfnReset) ? (*m_lpfnReset)(m_hAGB, bOnOff) : FALSE; }
};

CAGB::CAGB() : 
  m_hDLL(NULL), m_hAGB(NULL), 
  m_lpfnFindFirst(NULL), m_lpfnFindNext(NULL), m_lpfnFindClose(NULL),
  m_lpfnOpen(NULL), m_lpfnClose(NULL), m_lpfnWrite(NULL),
  m_lpfnRead(NULL), m_lpfnGo(NULL), m_lpfnReset(NULL)
{
	// ISAGB.DLLをロードします。
	// ISAGB.DLLが存在した場合には、EXPORT関数を得ます。
  m_hDLL = ::LoadLibrary(ISAGBDLL_NAME);
  if (m_hDLL) {
    m_lpfnFindFirst = (AGBFINDFIRST)GetProcAddress(m_hDLL, AGB_FUNC_FINDFIRST);
    m_lpfnFindNext  = (AGBFINDNEXT)GetProcAddress(m_hDLL, AGB_FUNC_FINDNEXT);
    m_lpfnFindClose = (AGBFINDCLOSE)GetProcAddress(m_hDLL, AGB_FUNC_FINDCLOSE);
    m_lpfnOpen      = (AGBOPEN)GetProcAddress(m_hDLL, AGB_FUNC_OPEN);
    m_lpfnClose     = (AGBCLOSE)GetProcAddress(m_hDLL, AGB_FUNC_CLOSE);
    m_lpfnWrite     = (AGBWRITE)GetProcAddress(m_hDLL, AGB_FUNC_WRITE);
    m_lpfnRead      = (AGBREAD)GetProcAddress(m_hDLL, AGB_FUNC_READ);
    m_lpfnGo        = (AGBGO)GetProcAddress(m_hDLL, AGB_FUNC_GO);
		m_lpfnReset			= (AGBRESET)GetProcAddress(m_hDLL, AGB_FUNC_RESET);
  }
}


CAGB::~CAGB()
{
	// DLLを破棄します。
  if (m_hAGB) Close();
  if (m_hDLL) {
    BOOL b = ::FreeLibrary(m_hDLL);
  }
}


INT CAGB::Open(INT nHost, INT nID)
{
  UINT nErrCode = ERR_SUCCESS;
  if (m_hAGB) Close();
  try {
    if (!m_hDLL) throw((INT)ERR_CANNOT_FOUND_DLL);		// DLL が見つからない。(ISAGB.DLL / WNASPI32.DLL)

		// AGBOpen()の最も簡単に使用方法は、引数 nHost, nIDに
		// -1, -1 を指定することです。こうすることで、AGBOpen()
		// 関数は、接続されているIS-AGB-EMULATORの中から、他の
		// アプリケーションで使用されていないIS-AGB-EMULATORを
		// 自動検索します。
    m_hAGB = AGBOpen(nHost, nID);
    if (!m_hAGB) throw((INT)ERR_CANNOT_OPEN);          // AGBを使用することが出来ない。
  }
  catch(INT nErr) {
    nErrCode = nErr;
  }
  return nErrCode;
}

//////////////////////////////////////////////////////////////////////////////////////////

static VOID Error(LPCTSTR lpszError)
{
  printf("\n%s\n", lpszError);
}

static VOID Title()
{
  printf("\n");
  printf("IS-AGB-EMULATOR iscgb.dll sample program\n");
  printf("Copyright 1999 INTELLIGENT SYSTEMS Co.,Ltd.\n");
  printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////
///

VOID main(INT argc, char* argv[])
{
  Title();
  if (argc <= 1) {  
		// ダウンロードするバイナリファイルを引数に指定してください。
    Error("sample exe-file1");
    exit(EXIT_FAILURE);
  }

  FILE* pFile = fopen(argv[1], "rb");
  if (pFile == NULL) {
		// 指定したファイルは、オープン出来ませんでした。
    Error("can not open file");
    exit(EXIT_FAILURE);
  }

  CAGB agb;			// agbオブジェクトの作成

	const INT nMax = 16;
	AGBFindData FindData[nMax];
	// Find*系の動作確認
	// 接続されているIS-AGB-EMULATORの台数を調べる為のテストです。
	// サンプルを簡単にする為に FindData は固定サイズ16としています。
	// 台数は、nCntに格納されます。
	int nCnt = 0;
	HANDLE hFind;
	if(hFind = agb.FindFirst(&FindData[nCnt])) {
		nCnt++;
		while(agb.FindNext(hFind, &FindData[nCnt]) && (nCnt < nMax)) {
			nCnt++;
		}
		agb.FindClose(hFind);
	}

	// IS-AGB-EMULATORとの接続を確立します。
	// Open()の引数に何も渡していないので、自動検索して最初に見つけた
	// IS-AGB-EMULATORを使用します。複数台の中の、特定のIS-AGB-EMULATOR
  // を使用したい場合には、上の Find*で検索したデータ[FindData]を使用して、
  // Open()の引数とすることも出来ます。
  if (agb.Open()) {
    printf("Can't found wnaspi32.dll / isagb.dll ");
    printf("or Can't open IS-AGB-EMULATOR device.");
    exit(EXIT_FAILURE);
  }

	// IS-AGB-EMULATORに、正しくデータを転送する為には、AGB側リセット状態
	// にしておく必要があります。ゲームを実行したままでデータのロード・セ
	// ーブを行うことは出来ません。

	agb.Reset(TRUE);		// リセットボタンを押します。
	::Sleep(2000);			// リセット後ハードウェアを安定させる為2秒間待ちます。(この処理は次回バージョンでISAGB.DLLにより吸収する予定です。）

  ULONG nLen = 0;
  ULONG nAdrs = 0x08000000;			// AGBのROM先頭アドレス
  const ULONG bufsiz = 0x10000;	// 一度に転送するサイズ
  static BYTE  writeBuf[bufsiz];

	// ホストに存在するファイルを、AGB側に転送します。
  while(nLen = fread(writeBuf, 1, bufsiz, pFile)) {
    if (nLen != agb.Write(writeBuf, nAdrs, nLen)) {
      printf("write error");
      break;
    }
    printf("\n%08x-%08x", nAdrs, (nAdrs + nLen - 1));
    nAdrs += nLen;
	}
  printf("\n");
	agb.Reset(FALSE);		// リセットボタンを放します。(リセット解除してゲーム実行)

	fclose(pFile);
  agb.Close();    // 接続を解除します。
}

