//=============================================================================
//
// ゲーム処理 [game.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_COUNT_MAX		(100)		// ゲーム遷移カウント
#define GAME_ROUND_MAX		(3)

// 各種カウント
//#define GAME_ROUND_RESET	(90)
//#define GAME_ROUND_RESET	(180)
#define GAME_ROUND_START		(200)
#define GAME_ROUND_START_FAST	(100)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class GameScene :public BaseScene
{   // :public  BaseScene
public:
	GameScene(void);
	~GameScene(void);
	void Update(void);
	void Draw(void);

	enum GamePlayer
	{
		GP1,
		GP2,
		GPMAX
	};

	static bool	m_bGame;			// ゲーム操作フラグ
	static int	m_nGameRound;
	static int	m_nRoundWin;
	static bool GetGameFlag(void) { return m_bGame; }
	static void SetRoundWin(int num);

private:
	bool	GameStop(void);			// ゲーム停止メソッド
	int		m_nGameCount;			// ゲーム停止カウント

	void Pause(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif