//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "game.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "sound.h"

/* ゲームで必要なインクルード */
#include "fade.h"
#include "skydome.h"
#include "stage.h"
#include "player.h"
#include "effect.h"
#include "particle.h"
#include "gage.h"
/* デバッグ */
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
extern SceneManager		g_cScene;				// Sceneマネージャ

//=============================================================================
// 更新処理
//=============================================================================
void GameScene::Update(void)
{
	ObjectManager::UpdateAll();
}

//=============================================================================
// 描画処理
//=============================================================================
void GameScene::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		CameraManager::Set(CameraManager::CameraType(i));
		ObjectManager::DrawAll();
		//pDevice->Present(NULL, NULL, NULL, NULL);
	}
	CameraManager::Set(CameraManager::SINGLE);
}

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
GameScene::GameScene(void)
{
	//new Copyright;
	//new AirWaterFream;
	//ObjectManager::CreateObject<Skydome>();
	//ObjectManager::CreateObject<Cube>();
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<PlayerManager>();
	ObjectManager::CreateObject<EffectManager>();
	ObjectManager::CreateObject<Gage>();
	//new Player;
	//new Skydome;
	//new Cube;
	//new Stencil;

	//// 指定オブジェクト取得テスト
	//Object *pTest1 = Object::GetObjectPointer(Object::PLAYER);
	//Object *pTest2 = Object::GetObjectPointer(Object::COPYRIGHT);
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
GameScene::~GameScene(void)
{
	ObjectManager::ReleaseAll();
}

//=============================================================================
// ゲーム停止メソッド
//=============================================================================
bool GameScene::GameStop(void)
{
	return 0;
}