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
#include "time.h"
#include "rightleft.h"
#include "ko.h"
#include "roundlogo.h"
#include "timeuplogo.h"
#include "gage.h"
#include "gage3d.h"
#include "gray.h"
#include "grayko.h"
#include "weaponMgr.h"
#include "collision.h"
#include "resultselect.h"
#include "joycon.h"

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
#ifdef _DEBUG
	Debugtimer timer;
#endif
	// リザルトセレクトのポインタを取得
	Resultselect* pResultselect = ObjectManager::GetObjectPointer<Resultselect>(ObjectManager::RESULTSELECT);

	// グレーのポインタを取得
	Gray* pGray = ObjectManager::GetObjectPointer<Gray>(ObjectManager::GRAY);

	// ポーズフラグが false ならば
	if (!bPause)
	{
		// 全てUpdateする
		ObjectManager::UpdateAll();
	}
	else
	{
		// リザルトセレクトだけUpdateする
		pResultselect->Update();
	}

	// ポーズ情報を取得
	Pause();

	// リザルトセレクトの使用フラグをポーズフラグと同期
	for (int i = 0; i < NUM_RESULTSELECT; i++)
	{
		pGray->GrayObj[0].Use = bPause;
		pResultselect->ResultselectObj[i].Use = bPause;
	}

#ifdef _DEBUG
	PrintDebugProc("【 UpdateALL 】\n");
	PrintDebugProc("TIME:%f\n", timer.End());
#endif

#ifdef _DEBUG
	Debugtimer timer2;
#endif
	ChackHit();
#ifdef _DEBUG
	PrintDebugProc("【 COLLISION 】\n");
	PrintDebugProc("TIME:%f\n", timer2.End());
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void GameScene::Draw(void)
{
	// デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	//{
	//	CameraManager::Set(CameraManager::CameraType(i));
	//	ObjectManager::DrawAll();
	//	//pDevice->Present(NULL, NULL, NULL, NULL);
	//}
	//CameraManager::Set(CameraManager::SINGLE);

	for (unsigned int i = 0; i < CameraManager::MULTI_MAX; i++)
	{
		CameraManager::Set(CameraManager::CameraType(i));
		ObjectManager::DrawNormalAll();
		//pDevice->Present(NULL, NULL, NULL, NULL);
	}
	CameraManager::Set(CameraManager::SINGLE);
	ObjectManager::DrawUiAll();
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
	ObjectManager::CreateObject<WeaponManager>();
	ObjectManager::CreateObject<PlayerManager>();
	ObjectManager::CreateObject<EffectManager>();
	ObjectManager::CreateObject<Roundlogo>();
	ObjectManager::CreateObject<Rightleft>();
	ObjectManager::CreateObject<Gage>();
	ObjectManager::CreateObject<Gage3d>();
	ObjectManager::CreateObject<Gray>();
	ObjectManager::CreateObject<Grayko>();
	ObjectManager::CreateObject<Timeuplogo>();
	ObjectManager::CreateObject<Ko>();
	ObjectManager::CreateObject<Time>();
	ObjectManager::CreateObject<Resultselect>();
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

//=============================================================================
// の確認
//=============================================================================
void GameScene::Pause(void)
{
	// 決定になりえるボタンが押されている場合、遷移フラグを true
	if (GetKeyboardTrigger(DIK_ESCAPE))
		bPause = bPause ? false : true;
	else
	{
		// Joyconの数だけ回す
		for (unsigned int i = 0; i < GetJoyconSize(); i++)
		{
			// 決定になりえるボタンが押されている場合、遷移フラグを true
			if (JcTriggered(i, JC_L_BUTTON_MINUS | JC_R_BUTTON_PLUS)
				|| GetKeyboardTrigger(DIK_ESCAPE))
				bPause = bPause ? false : true;;
		}
	}
}

//=============================================================================
// シーンチェンジの確認
//=============================================================================
//void GameScene::SceneChange(void)
//{
//	if (BaseScene::bSceneChange)
//	{
//		// Joyconの数だけ回す
//		for (unsigned int i = 0; i < GetJoyconSize(); i++)
//		{
//			// 決定になりえるボタンが押されている場合、遷移フラグを true
//			if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
//				| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
//				|| GetKeyboardTrigger(DIK_RETURN))
//				bSceneChange = true;
//		}
//
//		// 遷移フラグが true なら遷移開始
//		if (bSceneChange) SetFadeScene(SceneManager::SELECT);
//	}
//}