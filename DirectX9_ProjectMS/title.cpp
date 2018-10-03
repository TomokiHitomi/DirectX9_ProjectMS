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
#include "SkinMeshX.h"
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
	pEffect->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void TitleScene::Draw(void)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		Camera::Set(i);			// カメラ
		ObjectManager::DrawAll();
		pEffect->Draw();
	}
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
TitleScene::TitleScene(void)
{
	//new Copyright;
	//new AirWaterFream;
	//ObjectManager::CreateObject<Player>();
	ObjectManager::CreateObject<Skydome>();
	//ObjectManager::CreateObject<Cube>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<PlayerManager>();
	//new Player;
	//new Skydome;
	//new Cube;
	//new Stencil;

	pEffect = new Effect;
	//// 指定オブジェクト取得テスト
	//Object *pTest1 = Object::GetObjectPointer(Object::PLAYER);
	//Object *pTest2 = Object::GetObjectPointer(Object::COPYRIGHT);
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
TitleScene::~TitleScene(void)
{
	ObjectManager::ReleaseAll();
	if (pEffect != NULL)
	{
		delete pEffect;
	}

}

//=============================================================================
// タイトルデモのリスタートメソッド
//=============================================================================
void TitleScene::DemoRestart(void)
{

}