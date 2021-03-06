//=============================================================================
//
// メイン処理 [main.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include <time.h>
#include <stdio.h>

#ifdef _DEBUG

/* imgui */
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_internal.h"

// メモリリーク検出
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#include <stdlib.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAFE_UPDATE(p) { if(p) { (p)->Update(); } }
#define SAFE_DRAW(p) { if(p) { (p)->Draw(); } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

#define CLASS_NAME			("AppClass")		// ウインドウのクラス名
#define WINDOW_NAME			("MS")		// ウインドウのキャプション名

// 起動時のコメント
#define START_UP_COMMENT	("ウインドウモードで起動しますか？")

//#define SCREEN_SCALE	(2.0f)
#define SCREEN_SCALE	(1.5f)
#define SCREEN_WIDTH	(1280 * SCREEN_SCALE)		// ウインドウの幅
#define SCREEN_HEIGHT	(720 * SCREEN_SCALE)		// ウインドウの高さ
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)			// ウインドウ中央X
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)			// ウインドウ中央Y

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

#define DEBUG_RECT		(50)	// デバッグ

#define MOUSE_MARGIN	(10)

#define FRAME			(60)

// ３Ｄポリゴン頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{	// 3Dポリゴン頂点構造体
	D3DXVECTOR3	vtx;		// 頂点座標
	D3DXVECTOR3	nor;		// 法線ベクトル
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2	tex;		// テクスチャ座標
} VERTEX_3D;

typedef struct
{	// 2Dポリゴン頂点構造体
	D3DXVECTOR3 vtx;		// 頂点座標
	float		rhw;		// テクスチャのパースペクティブコレクト用
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void EndGame(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#ifdef _DEBUG
int GetFps(void);
#endif

#endif