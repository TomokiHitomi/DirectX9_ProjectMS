//=============================================================================
//
// �Q�[������ [game.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_COUNT_MAX		(100)		// �Q�[���J�ڃJ�E���g
#define GAME_ROUND_MAX		(3)

// �e��J�E���g
#define GAME_ROUND_RESET	(90)
#define GAME_ROUND_START	(100)

//*****************************************************************************
// �N���X��`
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

	static bool	m_bGame;			// �Q�[������t���O
	static int	m_nGameRound;
	static int	m_nRoundWin;
	static bool GetGameFlag(void) { return m_bGame; }
	static void SetRoundWin(int num);

private:
	bool	GameStop(void);			// �Q�[����~���\�b�h
	int		m_nGameCount;			// �Q�[����~�J�E���g

	


	void Pause(void);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif