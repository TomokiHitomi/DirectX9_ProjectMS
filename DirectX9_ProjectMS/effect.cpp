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
const WCHAR* EffectManager::c_filename[] = {
	// �G�t�F�N�g�t�@�C��
	L"TrinityField.efk",
	L"high_sword",
	L"test2.efk",
	L"test3.efk",
	L"test4.efk"
};

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
EffectManager::EffectManager(void)
{

	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::EFFECT, Priority::Low, Priority::Low);

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	m_manager = NULL;
	m_renderer = NULL;
	m_sound = NULL;
	m_handle = -1;
	m_position;
	m_rotation;

	for (unsigned int i = 0; i < EFFECT_MAX; i++)
	{
		m_effect[i] = NULL;
	}

	//// XAudio2�̏��������s��
	//XAudio2Create(&g_xa2);

	//g_xa2->CreateMasteringVoice(&g_xa2_master);


	// �`��p�C���X�^���X�̐���
	m_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 2048);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	m_manager = ::Effekseer::Manager::Create(2048);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());

	// ������W�n�ɐݒ�
	m_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);


	//// ���Đ��p�C���X�^���X�̐���
	//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);

	//// ���Đ��p�C���X�^���X����Đ��@�\���w��
	//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

	//// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
	//// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());


	// ���_�ʒu���m��	
	m_position = ::Effekseer::Vector3D(0.0f, 5.0f, 0.0f);
	m_rotation = ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f);


	// �G�t�F�N�g�̓Ǎ�
	for (unsigned int i = 0; i < EFFECT_MAX; i++)
	{
		m_effect[i] = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)c_filename[i]);
	}
	//m_effect[EFFECT1] = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)L"TrinityField.efk");
	//m_effect[EFFECT2] = Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)L"test2.efk");

	//g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"test.efk");

	// �G�t�F�N�g�̍Đ�
	//m_handle = m_manager->Play(m_effect[EFFECT1], 0, 0, 0);
	//m_manager->Play(m_effect[EFFECT2], 0, 5.0f, 0);

	m_manager->SetLocation(m_handle, m_position);
	m_manager->SetScale(m_handle, 5.0f, 5.0f, 5.0f);

}

//=============================================================================
// �f�X�g���N�^�i�I�������j
//=============================================================================
EffectManager::~EffectManager(void)
{
	// �S�G�t�F�N�g�̒�~
	m_manager->StopAllEffects();

	for (unsigned int i = 0; i < EFFECT_MAX; i++)
	{
		// �G�t�F�N�g�̔j��
		ES_SAFE_RELEASE(m_effect[i]);
	}

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	m_manager->Destroy();

	//// ���ɉ��Đ��p�C���X�^���X��j��
	//g_sound->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	m_renderer->Destroy();

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
void EffectManager::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �G�t�F�N�g�̈ړ��������s��
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));
	if (GetKeyboardTrigger(DIK_K))
	{
		m_handle = m_manager->Play(m_effect[EFFECT2], 0, 5.0f, 0);
		m_manager->SetScale(m_handle, 5.0f, 5.0f, 5.0f);
	}
	if (GetKeyboardTrigger(DIK_J))
	{
		m_handle = m_manager->Play(m_effect[EFFECT3], 30.0f, 5.0f, 0);
		m_manager->SetScale(m_handle, 5.0f, 5.0f, 5.0f);
	}
	if (GetKeyboardTrigger(DIK_L))
	{
		m_handle = m_manager->Play(m_effect[EFFECT4], 0, 5.0f, 30.0f);
		m_manager->SetScale(m_handle, 5.0f, 5.0f, 5.0f);
	}
	if (GetKeyboardTrigger(DIK_M))
	{
		m_manager->StopEffect(m_handle);
	}

	// �G�t�F�N�g�̍X�V�������s��
	m_manager->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void EffectManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxView, mtxPro;

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxPro);

	// �J�����s���ݒ�
	m_renderer->SetCameraMatrix(ConvertMtx44(mtxView));

	// ���e�s���ݒ�
	m_renderer->SetProjectionMatrix(ConvertMtx44(mtxPro));


	// ���ʕ`�悷��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// �G�t�F�N�g�̕`��J�n�������s���B
	m_renderer->BeginRendering();

	//g_position = ::Effekseer::Vector3D(100.0f, 20.0f, 0.0f);
	//g_manager->SetLocation(g_handle, g_position);

	// �G�t�F�N�g�̕`����s���B
	m_manager->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	m_renderer->EndRendering();

	// ���ʂ��J�����O�ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

//=============================================================================
// Effekseer�p�s��ϊ�����
//=============================================================================
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