//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "character.h"
#include "camera.h"
#include "shader.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCENE_UIOBJECT_MAX		(10)
#define SCENE_GAME_WIN			(50.0f)		// 勝利割合

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BaseScene
{
public:
	static bool bSceneChange;
	static bool bPause;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual ~BaseScene() {};
	BaseScene() { bSceneChange = false; bPause = false;}

};

class SceneManager
{
private:
	static int m_nSelectChar[2];
	static int m_nWinPlayer;
public:
	// シーンリスト
	enum SCENE 	{TITLE, SELECT, GAME, RESULT, MAX	};
	// コンストラクタ
	SceneManager(void);
	// デストラクタ
	~SceneManager(void);
	// シーンを引数によって変える関数
	static void			ChangeScene(SCENE scene);
	// シーンの初期化関数
	static void			Init(HINSTANCE hInst, HWND hWnd);
	// シーンの終了関数
	static void			Uninit(void);
	// シーンの更新関数
	static void			Update(void);
	// シーンの描画関数
	static void			Draw(void);
	static void			Load(SCENE scene);


	// 現在のシーン取得
	static SCENE		GetScene(void)				{ return m_eScene; }

	// マルチ画面設定
	static void			SetMulti(int nflag) { m_nMulti = nflag; }
	// マルチ画面取得
	static int			GetMulti(void) { return m_nMulti; }

	// 選択キャラクターの設定・取得
	static void SetSelectChar(int nPlayer,int nSelect) { m_nSelectChar[nPlayer] = nSelect; }
	static int GetSelectChar(int nPlayer) { return m_nSelectChar[nPlayer]; }

	// 勝利プレイヤーの設定・取得
	static void SetWinPlayer(int nPlayer) { m_nWinPlayer = nPlayer; }
	static int GetWinPlayer(void) { return m_nWinPlayer; }

	// SEの終了関数
	static void			EndSeS(void);


private:
	static BaseScene		*m_pScene;			// 現在のシーン
	static SCENE			m_eScene;			// 現在のシーン番号
	static int				m_nMulti;			// ２画面フラグ
	static CharacterManager *CharMgr;
	static CameraManager	*CameraMgr;
	static ShaderManager	*ShaderMgr;
public:
	static CharacterManager *GetCharMgr(void) { return CharMgr; }

#ifdef _DEBUG
	// デバッグ用シーン遷移
	static void DebugScene(void);
#endif
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif