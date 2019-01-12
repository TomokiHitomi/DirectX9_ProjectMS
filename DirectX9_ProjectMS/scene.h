//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "character.h"
#include "camera.h"
#include "shader.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCENE_UIOBJECT_MAX		(10)
#define SCENE_GAME_WIN			(50.0f)		// ��������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
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
	// �V�[�����X�g
	enum SCENE 	{TITLE, SELECT, GAME, RESULT, MAX	};
	// �R���X�g���N�^
	SceneManager(void);
	// �f�X�g���N�^
	~SceneManager(void);
	// �V�[���������ɂ���ĕς���֐�
	static void			ChangeScene(SCENE scene);
	// �V�[���̏������֐�
	static void			Init(HINSTANCE hInst, HWND hWnd);
	// �V�[���̏I���֐�
	static void			Uninit(void);
	// �V�[���̍X�V�֐�
	static void			Update(void);
	// �V�[���̕`��֐�
	static void			Draw(void);
	static void			Load(SCENE scene);


	// ���݂̃V�[���擾
	static SCENE		GetScene(void)				{ return m_eScene; }

	// �}���`��ʐݒ�
	static void			SetMulti(int nflag) { m_nMulti = nflag; }
	// �}���`��ʎ擾
	static int			GetMulti(void) { return m_nMulti; }

	// �I���L�����N�^�[�̐ݒ�E�擾
	static void SetSelectChar(int nPlayer,int nSelect) { m_nSelectChar[nPlayer] = nSelect; }
	static int GetSelectChar(int nPlayer) { return m_nSelectChar[nPlayer]; }

	// �����v���C���[�̐ݒ�E�擾
	static void SetWinPlayer(int nPlayer) { m_nWinPlayer = nPlayer; }
	static int GetWinPlayer(void) { return m_nWinPlayer; }

	// SE�̏I���֐�
	static void			EndSeS(void);


private:
	static BaseScene		*m_pScene;			// ���݂̃V�[��
	static SCENE			m_eScene;			// ���݂̃V�[���ԍ�
	static int				m_nMulti;			// �Q��ʃt���O
	static CharacterManager *CharMgr;
	static CameraManager	*CameraMgr;
	static ShaderManager	*ShaderMgr;
public:
	static CharacterManager *GetCharMgr(void) { return CharMgr; }

#ifdef _DEBUG
	// �f�o�b�O�p�V�[���J��
	static void DebugScene(void);
#endif
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif