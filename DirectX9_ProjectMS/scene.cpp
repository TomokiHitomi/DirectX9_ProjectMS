//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "scene.h"

/* Scene */
#include "title.h"
#include "select.h"
#include "game.h"
#include "result.h"

/* System */
#include "camera.h"
#include "light.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

/* Ui */

/* Object */

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
//始めはシーンを空にしておく
BaseScene			*SceneManager::m_pScene = NULL;
bool				BaseScene::bSceneChange = false;
bool				BaseScene::bPause = false;
SceneManager::SCENE	SceneManager::m_eScene;

int					SceneManager::m_nSelectChar[2];
int					SceneManager::m_nWinPlayer = 0;
int					SceneManager::m_nMulti;
CharacterManager	*SceneManager::CharMgr = NULL;
CameraManager		*SceneManager::CameraMgr = NULL;
ShaderManager		*SceneManager::ShaderMgr = NULL;

//=============================================================================
// シーン管理処理
//=============================================================================
void SceneManager::ChangeScene(SCENE scene)
{
	if (m_pScene != NULL)
	{
		delete m_pScene;
		CameraManager::Init();	// カメラ
	}

	// SEの停止処理
	EndSeS();

	// 選択されたシーンを保管
	m_eScene = scene;

	switch (scene)
	{	//引数のシーン
	case SCENE::TITLE:
		SetSoundBgm(SOUND_BGM_TITLE);
		m_pScene = new TitleScene();	// タイトルシーンを現在のシーンにする
		break;
	case SCENE::SELECT:
		SetSoundBgm(SOUND_BGM_SELECT);
		m_pScene = new SelectScene();	// セレクトシーンを現在のシーンにする
		break;
	case SCENE::GAME:
		SetSoundBgm(SOUND_BGM_GAME);
		m_pScene = new GameScene();		// ゲームシーンを現在のシーンにする
		break;
	case SCENE::RESULT:
		SetSoundBgm(SOUND_BGM_RESULT);
		m_pScene = new ResultScene();	// リザルトシーンを現在のシーンにする
		break;
	default:
		break;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
void SceneManager::Init(HINSTANCE hInst, HWND hWnd)
{
	// カメラマネージャーを実体化
	CameraMgr = new CameraManager;

	// シェーダマネージャを実体化
	ShaderMgr = new ShaderManager;

	// キャラクターマネージャーを実体化
	CharMgr = new CharacterManager;

	LightManager::Init();	// ライト（シェーダ用）
	InitLight();			// ライト
	InitInput(hInst, hWnd);	// 入力
	InitSound(hWnd);		// サウンド
	InitFade();				// フェード

	// 初期のシーンをTITLEに設定
	m_eScene = TITLE;
	//m_eScene = GAME;

	ChangeScene(m_eScene);	// 初期シーン設定

#ifdef _DEBUG
	InitDebugProc();		// デバッグ
#endif
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneManager::Uninit(void)
{

	UninitInput();			// 入力
	UninitSound();			// サウンド
	UninitFade();			// フェード

#ifdef _DEBUG
	UninitDebugProc();		// デバッグ
#endif

	if (m_pScene != NULL)
	{
		delete m_pScene;
	}
	if (CharMgr != NULL)
	{
		delete CharMgr;
	}
	if (CameraMgr != NULL)
	{
		delete CameraMgr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneManager::Update(void)
{
	UpdateInput();				// 入力
	UpdateFade();				// フェード

#ifdef _DEBUG
	DebugScene();				// デバッグ用
#endif

	m_pScene->Update();			// 現在のシーンの更新関数

	CameraManager::Update();	// カメラ
	UpdateSound();				// サウンド
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneManager::Draw(void)
{
	m_pScene->Draw();		// 現在のシーンの描画関数

	DrawFade();				// フェード

#ifdef _DEBUG
	DrawDebugProc();
#endif
}

//=============================================================================
// コンストラクタ処理
//=============================================================================
SceneManager::SceneManager(void)
{
	// 初期のシーンをTITLEに設定
	//m_eScene = TITLE;
	//m_eScene = GAME;

	// 各変数を初期化
}

//=============================================================================
// デストラクタ処理
//=============================================================================
SceneManager::~SceneManager(void)
{

}

//=============================================================================
// シーン管理処理
//=============================================================================
void SceneManager::EndSeS(void)
{
	EndSe(SE_FIRE1);
	EndSe(SE_WATER_SUCK);
	EndSe(SE_WATER1);
	EndSe(SE_WATER2);
	EndSe(SE_WIND_SUCK);
	EndSe(SE_WIND1);
}

#ifdef _DEBUG
//=============================================================================
// デバッグ処理
//=============================================================================
void SceneManager::DebugScene(void)
{
	// デバッグの更新処理
	UpdateDebugProc();

	// シーン情報を表示
	PrintDebugProc("【 SCENE 】\n");

	// 現在のシーンを表示
	switch (m_eScene)
	{
	case SCENE::TITLE:
		PrintDebugProc("Scene[TITLE ]  ");
		break;
	case SCENE::GAME:
		PrintDebugProc("Scene[ GAME ]  ");
		break;
	case SCENE::RESULT:
		PrintDebugProc("Scene[RESULT]  ");
		break;
	}

	// 選択・勝利キャラ
	PrintDebugProc("Select 1P[%d] 2P[%d]  Win[%d]",
		m_nSelectChar[0], m_nSelectChar[1], m_nWinPlayer);

	// シーン強制変更
	if (GetKeyboardTrigger(DIK_F2))
	{
		SetFadeScene(TITLE);
	}
	if (GetKeyboardTrigger(DIK_F3))
	{
		SetFadeScene(SELECT);
	}
	if (GetKeyboardTrigger(DIK_F4))
	{
		SetFadeScene(GAME);
	}
	if (GetKeyboardTrigger(DIK_F5))
	{
		SetFadeScene(RESULT);
	}

	// SEテスト（sound.hをincludeして関数を呼ぶ）
	if (GetKeyboardTrigger(DIK_1))
	{	// 
		SetSe(SE_KETTEI, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_2))
	{	// 
		SetSe(SE_SELECT, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_3))
	{	// 
		SetSe(SE_CANCEL, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_4))
	{	//		
		SetSe(SE_SENNI, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_5))
	{	// 
		SetSe(SE_JAN, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_6))
	{	// 
		SetSe(SE_ROLLOFDRAM, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_7))
	{	// 
		SetSe(SE_COLLIDE, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_8))
	{	// 
		SetSe(SE_SP_MAX, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_9))
	{	// 
		SetSe(SE_IDOL_CD, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}
	if (GetKeyboardTrigger(DIK_0))
	{	// 
		SetSe(SE_PATISSIER_SP, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
	}

	PrintDebugProc("\n");
}
#endif