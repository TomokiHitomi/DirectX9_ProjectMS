//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "effect.h"

/* �S�̂ŕK�v�ȃC���N���[�h */
#include "input.h"
#include "camera.h"
#include "calculate.h"


#include <Effekseer\Effekseer.h>
#include <Effekseer\EffekseerRendererDX9.h>
#include <Effekseer\EffekseerSoundXAudio2.h>

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
::Effekseer::Matrix44 ConvertMtx44(D3DXMATRIX mtx);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ::Effekseer::Manager*				g_manager = NULL;
static ::EffekseerRendererDX9::Renderer*	g_renderer = NULL;
static ::EffekseerSound::Sound*				g_sound = NULL;
static ::Effekseer::Effect*					g_effect = NULL;
static ::Effekseer::Handle					g_handle = -1;
static ::Effekseer::Vector3D				g_position;
static ::Effekseer::Vector3D				g_rotation;
static ::Effekseer::Matrix44 mtx44View, mtx44Pro, mtx44World;

// �T�E���h
//static IXAudio2*						g_xa2 = NULL;
//static IXAudio2MasteringVoice*			g_xa2_master = NULL;

//=============================================================================
// �R���X�g���N�^�����i�������j
//=============================================================================
Effect::Effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// XAudio2�̏��������s��
	//XAudio2Create(&g_xa2);

	//g_xa2->CreateMasteringVoice(&g_xa2_master);


	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 2000);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create(2000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// ������W�n�ɐݒ�
	g_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);


	//// ���Đ��p�C���X�^���X�̐���
	//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);

	//// ���Đ��p�C���X�^���X����Đ��@�\���w��
	//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

	//// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
	//// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());


	// ���_�ʒu���m��	
	g_position = ::Effekseer::Vector3D(0.0f, 5.0f, 0.0f);
	g_rotation = ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f);


	// �G�t�F�N�g�̓Ǎ�
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"TrinityField.efk");
	//g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"test.efk");

	// �G�t�F�N�g�̍Đ�
	g_handle = g_manager->Play(g_effect, 0, 0, 0);

	g_manager->SetLocation(g_handle, g_position);
	g_manager->SetScale(g_handle, 5.0f, 5.0f, 5.0f);
}

//=============================================================================
// �f�X�g���N�^�����i�I���j
//=============================================================================
Effect::~Effect(void)
{
	// �G�t�F�N�g�̒�~
	g_manager->StopEffect(g_handle);

	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE(g_effect);

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	//// ���ɉ��Đ��p�C���X�^���X��j��
	//g_sound->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();

	//// XAudio2�̉��
	//if (g_xa2_master != NULL)
	//{
	//	g_xa2_master->DestroyVoice();
	//	g_xa2_master = NULL;
	//}
	//ES_SAFE_RELEASE(g_xa2);
}

//=============================================================================
// �X�V����
//=============================================================================
void Effect::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �G�t�F�N�g�̈ړ��������s��
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// �G�t�F�N�g�̍X�V�������s��
	g_manager->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Effect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxView, mtxPro, mtxWorld;

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxPro);

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(ConvertMtx44(mtxView));

	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(ConvertMtx44(mtxPro));


	// ���ʕ`�悷��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


		// �G�t�F�N�g�̕`��J�n�������s���B
		g_renderer->BeginRendering();

		//g_position = ::Effekseer::Vector3D(100.0f, 20.0f, 0.0f);
		//g_manager->SetLocation(g_handle, g_position);

		// �G�t�F�N�g�̕`����s���B
		g_manager->Draw();

		// �G�t�F�N�g�̕`��I���������s���B
		g_renderer->EndRendering();
	

	// ���ʂ��J�����O�ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

::Effekseer::Matrix44 ConvertMtx44(D3DXMATRIX mtx)
{
	::Effekseer::Matrix44 mtx44;
	mtx44.Values[0][0] = mtx._11;
	mtx44.Values[0][1] = mtx._12;
	mtx44.Values[0][2] = mtx._13;
	mtx44.Values[0][3] = mtx._14;
	mtx44.Values[1][0] = mtx._21;
	mtx44.Values[1][1] = mtx._22;
	mtx44.Values[1][2] = mtx._23;
	mtx44.Values[1][3] = mtx._24;
	mtx44.Values[2][0] = mtx._31;
	mtx44.Values[2][1] = mtx._32;
	mtx44.Values[2][2] = mtx._33;
	mtx44.Values[2][3] = mtx._34;
	mtx44.Values[3][0] = mtx._41;
	mtx44.Values[3][1] = mtx._42;
	mtx44.Values[3][2] = mtx._43;
	mtx44.Values[3][3] = mtx._44;
	return mtx44;
}