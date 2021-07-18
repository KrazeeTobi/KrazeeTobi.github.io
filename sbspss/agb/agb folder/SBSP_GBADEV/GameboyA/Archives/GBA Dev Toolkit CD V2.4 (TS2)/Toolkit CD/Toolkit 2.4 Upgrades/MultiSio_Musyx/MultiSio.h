/********************************************************************/
/*          MultiSio.h                                              */
/*            マルチプレイ通信ライブラリ外部宣言                    */
/*            （タイマー割り込み送信）                              */
/*                                                                  */
/*          Copyright (C) 1999-2000 NINTENDO Co.,Ltd.               */
/********************************************************************/
#ifndef _MULTI_SIO_H
#define _MULTI_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Agb.h>


// 下記の設定値はソフトの仕様に合わせて最適化して下さい。

#define MULTI_SIO_BLOCK_SIZE        16      // 通信データブロックサイズ（最大24Byte）

#define MULTI_SIO_SYNC_DATA         0xfefe  // 同期データ（0x0000／0xfffa～0xffffは禁止）

// CPU内部ワークRAMに余裕がなければコメントアウトして下さい。
#define MULTI_SIO_DI_FUNC_FAST              // SIO割り込み禁止関数高速化フラグ（CPU内部RAM実行）


// 開発途中では NDEBUG を未定義にして下記の値を 0 にし、
// 最終チェック段階では定義して 600 に変更した状態で動作確認をして下さい
// （設定値を増やしても通信間隔が延びるだけで処理が重くなることはありません）。
//#define NDEBUG                              // Makefile（MakefileDemo）での定義でも可
#ifdef  NDEBUG
#define MULTI_SIO_INTR_MARGIN       600     // 通信割り込み発生誤差保証値
#else
#define MULTI_SIO_INTR_MARGIN       0
#endif

// 通信割り込みの最大遅延が下記の値より大きくなる場合は更新して下さい。
#define MULTI_SIO_INTR_DELAY_MAX    2048    // 通信割り込み許容遅延クロック数

#define MULTI_SIO_INTR_CLOCK_MAX    512     // 通信割り込み処理最大クロック数


#define MULTI_SIO_BAUD_RATE         115200          // ボーレート
#define MULTI_SIO_BAUD_RATE_NO      SIO_115200_BPS  // ボーレートＮｏ


#define MULTI_SIO_TIMER_NO          3       // タイマーＮｏ
#define MULTI_SIO_TIMER_INTR_FLAG   (TIMER0_INTR_FLAG << MULTI_SIO_TIMER_NO)
                                            // タイマー割り込みフラグ
#define REG_MULTI_SIO_TIMER         (REG_TM0CNT + MULTI_SIO_TIMER_NO * 4)
#define REG_MULTI_SIO_TIMER_L        REG_MULTI_SIO_TIMER
#define REG_MULTI_SIO_TIMER_H       (REG_MULTI_SIO_TIMER + 2)
                                            // タイマーレジスタ

// タイマーカウント暫定値は通信データブロックサイズから算出します。
#define MULTI_SIO_TIMER_COUNT_TMP   (SYSTEM_CLOCK/60/((2 + 4 + MULTI_SIO_BLOCK_SIZE + 14)/(16/8)) \
                                    + MULTI_SIO_INTR_MARGIN)
                                            // タイマーカウント暫定値
#define MULTI_SIO_TIMER_COUNT_MIN   (SYSTEM_CLOCK/MULTI_SIO_BAUD_RATE*(1+16+1)*4 \
                                    + MULTI_SIO_INTR_DELAY_MAX + MULTI_SIO_INTR_CLOCK_MAX \
                                    + MULTI_SIO_INTR_MARGIN)
                                            // タイマーカウント最小値
#define MULTI_SIO_TIMER_COUNT_MAX   0x10000 // タイマーカウント最大値
#define MULTI_SIO_TIMER_COUNT       ((MULTI_SIO_TIMER_COUNT_TMP > MULTI_SIO_TIMER_COUNT_MAX)   \
					                ? MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_MAX    \
					                : ((MULTI_SIO_TIMER_COUNT_TMP < MULTI_SIO_TIMER_COUNT_MIN) \
					                  ? MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_MIN  \
					                  : MULTI_SIO_TIMER_COUNT_MAX - MULTI_SIO_TIMER_COUNT_TMP))
                                            // タイマーカウント数


// マルチプレイ通信パケット構造体
typedef struct {
    u8  FrameCounter;                       // フレームカウンタ
    u8  RecvErrorFlags;                     // 受信エラーフラグ
    u16 CheckSum;                           // チェックサム
	u16 Data[MULTI_SIO_BLOCK_SIZE/2];       // 通信データ
	u16 OverRunCatch[2];                    // オーバーラン保護領域
} MultiSioPacket;


// マルチプレイ通信ワークエリア構造体
typedef struct {
    u8  Type;                               // 接続関係（親／子）
    u8  State;                              // 通信関数の状態
    u8  ConnectedFlags;                     // 接続履歴フラグ
    u8  RecvSuccessFlags;                   // 受信成功フラグ

    u8  SyncRecvFlag[4];                    // 同期データ受信確認フラグ
    u8  SyncAdjustCounter;                  // 同期調整カウンタ

	u8  Padding0[1];

	s8  SendBufCounterInit;                 // 送信バッファカウンタ初期値

    u8  SendFrameCounter;                   // 送信フレームカウンタ
    u8  RecvFrameCounter[4][2];             // 受信フレームカウンタ

    s32 SendBufCounter;                     // 送信バッファカウンタ
    s32 RecvBufCounter[4];                  // 受信バッファカウンタ

    u16 *NextSendBufp;                      // 送信バッファポインタ
    u16 *CurrentSendBufp;
    u16 *CurrentRecvBufp[4];                // 受信バッファポインタ
    u16 *LastRecvBufp[4];
    u16 *RecvCheckBufp[4];

    MultiSioPacket  SendBuf[2];             // 送信バッファ（ダブルバッファ）
    MultiSioPacket  RecvBuf[4][3];          // 受信バッファ（トリプルバッファ）
} MultiSioArea;


extern u32 RecvFuncBuf[];                   // CPU内部RAM実行用バッファ
extern u32 IntrFuncBuf[];


/*------------------------------------------------------------------*/
/*                      マルチプレイ通信初期化                      */
/*------------------------------------------------------------------*/

extern void MultiSioInit(void);

//・シリアル通信モードをマルチプレイモードにします。
//・レジスタやバッファの初期化を行ないます。

/*------------------------------------------------------------------*/
/*                      マルチプレイ通信メイン                      */
/*------------------------------------------------------------------*/

extern u32  MultiSioMain(void *Sendp, void *Recvp);

//・まず、親機か子機かを判別し、親機と認識された場合は通信を開始します。
//・MultiSioSendDataSet()を呼び出し、送信データをセットします。
//・MultiSioRecvDataCheck()を呼び出し、正常に受信できたかどうかを調べ、
//  Recvpへ受信データをコピーします。
//
//・１フレーム中のできるだけ近いタイミングで呼び出されるようにして下さい。
//・同期調整に少々時間が掛かる場合があります。
//・同期調整中にはフラグデータ（SIO_SYNC_DATA）と一致するデータは
//  送信しない方が安全です。
//・１度認識された本体からの応答がなくなると同期調整し続けますので、
//  受信が不安定になります。
//
//・引数：
//    void *Sendp  ユーザ送信バッファポインタ
//    void *Recvp  ユーザ受信バッファポインタ

/*------------------------------------------------------------------*/
/*    		 		    マルチプレイ通信割り込み                    */
/*------------------------------------------------------------------*/

extern void MultiSioIntr(void);

//・通信割り込み時に各本体からの受信データを各受信バッファへ格納し、
//  送信バッファのデータをレジスタへセットします。
//・親機であれば送信を再開します。
//
//・子機は通信割り込みで親機はタイマー割り込みで呼ばれるように
//  プログラミングして下さい。
//・必ず１パケット（OverRunCatch[]以外）が１フレームで転送できるように
//  設定値を調整して下さい。


/*------------------------------------------------------------------*/
/*                      送信データ セット                           */
/*------------------------------------------------------------------*/

extern void MultiSioSendDataSet(void *Sendp);

//・ユーザ送信バッファのデータを送信バッファへセットします。
//
//・MultiSioMain()から呼び出されます。
//・直接呼び出す必要はありません。
//
//・引数：
//    void *Sendp  ユーザ送信バッファポインタ

/*------------------------------------------------------------------*/
/*                      受信データ チェック                         */
/*------------------------------------------------------------------*/

extern u32  MultiSioRecvDataCheck(void *Recvp);

//・正常に受信できたかどうかをチェックし、正常であれば受信データを
//  ユーザ受信バッファへコピーします。
//
//・MultiSioMain()から呼び出されます。
//・直接呼び出す必要はありません。
//
//・引数：
//    void *Recvp  ユーザ受信バッファポインタ


#ifdef __cplusplus
}      /* extern "C" */
#endif

#endif /* _MULTI_SIO_H */
