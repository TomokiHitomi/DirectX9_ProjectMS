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
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual ~BaseScene() {};
};

class SceneManager
{
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

	// ���݂̃V�[���擾
	static SCENE		GetScene(void)				{ return m_eScene; }

	// �}���`��ʐݒ�
	static void			SetMulti(int nflag) { m_nMulti = nflag; }
	// �}���`��ʎ擾
	static int			GetMulti(void) { return m_nMulti; }


	// SE�̏I���֐�
	static void			EndSeS(void);

	static int			m_nTotalBurnBonus;
	static int			m_nTotalWetBonus;
	static int			m_nTotalBurnChain;

private:
	static BaseScene		*m_pScene;			// ���݂̃V�[��
	static SCENE			m_eScene;			// ���݂̃V�[���ԍ�
	static int				m_nMulti;			// �Q��ʃt���O
	static CharacterManager *CharMgr;
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