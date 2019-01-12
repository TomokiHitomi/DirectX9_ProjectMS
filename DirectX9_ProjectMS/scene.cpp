//=============================================================================
//
// �V�[������ [scene.cpp]
// Author : GP12A295 25 �l���F��
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

/* �f�o�b�O */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//�n�߂̓V�[������ɂ��Ă���
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
// �V�[���Ǘ�����
//=============================================================================
void SceneManager::ChangeScene(SCENE scene)
{
	if (m_pScene != NULL)
	{
		delete m_pScene;
		CameraManager::Init();	// �J����
	}

	// SE�̒�~����
	EndSeS();

	// �I�����ꂽ�V�[����ۊ�
	m_eScene = scene;

	switch (scene)
	{	//�����̃V�[��
	case SCENE::TITLE:
		SetSoundBgm(SOUND_BGM_TITLE);
		m_pScene = new TitleScene();	// �^�C�g���V�[�������݂̃V�[���ɂ���
		break;
	case SCENE::SELECT:
		SetSoundBgm(SOUND_BGM_SELECT);
		m_pScene = new SelectScene();	// �Z���N�g�V�[�������݂̃V�[���ɂ���
		break;
	case SCENE::GAME:
		SetSoundBgm(SOUND_BGM_GAME);
		m_pScene = new GameScene();		// �Q�[���V�[�������݂̃V�[���ɂ���
		break;
	case SCENE::RESULT:
		SetSoundBgm(SOUND_BGM_RESULT);
		m_pScene = new ResultScene();	// ���U���g�V�[�������݂̃V�[���ɂ���
		break;
	default:
		break;
	}
}

//=============================================================================
// ����������
//=============================================================================
void SceneManager::Init(HINSTANCE hInst, HWND hWnd)
{
	// �J�����}�l�[�W���[�����̉�
	CameraMgr = new CameraManager;

	// �V�F�[�_�}�l�[�W�������̉�
	ShaderMgr = new ShaderManager;

	// �L�����N�^�[�}�l�[�W���[�����̉�
	CharMgr = new CharacterManager;

	LightManager::Init();	// ���C�g�i�V�F�[�_�p�j
	InitLight();			// ���C�g
	InitInput(hInst, hWnd);	// ����
	InitSound(hWnd);		// �T�E���h
	InitFade();				// �t�F�[�h

	// �����̃V�[����TITLE�ɐݒ�
	m_eScene = TITLE;
	//m_eScene = GAME;

	ChangeScene(m_eScene);	// �����V�[���ݒ�

#ifdef _DEBUG
	InitDebugProc();		// �f�o�b�O
#endif
}

//=============================================================================
// �I������
//=============================================================================
void SceneManager::Uninit(void)
{

	UninitInput();			// ����
	UninitSound();			// �T�E���h
	UninitFade();			// �t�F�[�h

#ifdef _DEBUG
	UninitDebugProc();		// �f�o�b�O
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
// �X�V����
//=============================================================================
void SceneManager::Update(void)
{
	UpdateInput();				// ����
	UpdateFade();				// �t�F�[�h

#ifdef _DEBUG
	DebugScene();				// �f�o�b�O�p
#endif

	m_pScene->Update();			// ���݂̃V�[���̍X�V�֐�

	CameraManager::Update();	// �J����
	UpdateSound();				// �T�E���h
}

//=============================================================================
// �`�揈��
//=============================================================================
void SceneManager::Draw(void)
{
	m_pScene->Draw();		// ���݂̃V�[���̕`��֐�

	DrawFade();				// �t�F�[�h

#ifdef _DEBUG
	DrawDebugProc();
#endif
}

//=============================================================================
// �R���X�g���N�^����
//=============================================================================
SceneManager::SceneManager(void)
{
	// �����̃V�[����TITLE�ɐݒ�
	//m_eScene = TITLE;
	//m_eScene = GAME;

	// �e�ϐ���������
}

//=============================================================================
// �f�X�g���N�^����
//=============================================================================
SceneManager::~SceneManager(void)
{

}

//=============================================================================
// �V�[���Ǘ�����
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
// �f�o�b�O����
//=============================================================================
void SceneManager::DebugScene(void)
{
	// �f�o�b�O�̍X�V����
	UpdateDebugProc();

	// �V�[������\��
	PrintDebugProc("�y SCENE �z\n");

	// ���݂̃V�[����\��
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

	// �I���E�����L����
	PrintDebugProc("Select 1P[%d] 2P[%d]  Win[%d]",
		m_nSelectChar[0], m_nSelectChar[1], m_nWinPlayer);

	// �V�[�������ύX
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

	// SE�e�X�g�isound.h��include���Ċ֐����Ăԁj
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