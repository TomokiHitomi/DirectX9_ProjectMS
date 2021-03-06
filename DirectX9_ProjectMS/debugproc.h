//=============================================================================
//
// デバッグ表示処理 [debugproc.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEBUG_SCROLL_SPEED		(5)
#define DEBUG_MSECOND			(1000)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Debugtimer
{
private:
	LARGE_INTEGER 	 m_liStart, m_liFreq;
public:
	void			Restart(void);
	double			End(void);
	Debugtimer(void) { Restart(); }
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);
void DebugHowTo(void);

void PrintDebugProc(char *fmt,...);

// デバッグ用メッセージボックス
// 引数：ハンドル, テキスト, ウィンドウタイトル, 変更したいフラグ, 「はい」を選択時に設定する値
void DebugMB(HWND hWnd, LPSTR lpText, LPSTR lpTitle, bool *pFlag, bool bValue);
#endif