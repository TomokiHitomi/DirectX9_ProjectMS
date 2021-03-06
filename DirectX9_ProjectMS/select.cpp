//=============================================================================
//
// ゲーム処理 [select.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "select.h"

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
#include "selectface.h"
#include "particle.h"
#include "selectcharacter.h"

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
void SelectScene::Update(void)
{
	ObjectManager::UpdateAll();

	if (bSceneChange)
	{
		m_nSceneCount++;
	}

	if(m_nSceneCount == SELECT_CHANGE_COUNT)
		// シーン遷移開始
		SetFadeScene(SceneManager::GAME);
}

//=============================================================================
// 描画処理
//=============================================================================
void SelectScene::Draw(void)
{
	////for (unsigned int i = 0; i < 2; i++)
	////{
	//CameraManager::Set(CameraManager::SINGLE);
	//ObjectManager::DrawAll();
	////}

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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
SelectScene::SelectScene(void)
{
	m_nSceneCount = 0;
	ObjectManager::CreateObject<ParticleManager>();
	ObjectManager::CreateObject<StageManager>();
	ObjectManager::CreateObject<Selectface>();
	ObjectManager::CreateObject<SelectCharacterManager>();
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
SelectScene::~SelectScene(void)
{
	ObjectManager::ReleaseAll();
}