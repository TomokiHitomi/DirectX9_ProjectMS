//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "title.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* タイトルで必要なインクルード */
#include "object.h"
#include "light.h"
#include "player.h"
#include "skydome.h"
#include "cube.h"
#include "stage.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 更新処理
//=============================================================================
void TitleScene::Update(void)
{
	ObjectManager::UpdateAll();
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleScene::Draw(void)
{
	Camera::Set(2);
	ObjectManager::DrawAll();
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
TitleScene::TitleScene(void)
{
	new Skydome;
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
TitleScene::~TitleScene(void)
{
	ObjectManager::ReleaseAll();
}

//=============================================================================
// タイトルデモのリスタートメソッド
//=============================================================================
void TitleScene::DemoRestart(void)
{

}