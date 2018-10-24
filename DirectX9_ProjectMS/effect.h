//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "object.h"
#include <tchar.h>

#include <Effekseer\Effekseer.h>
#include <Effekseer\EffekseerRendererDX9.h>
#include <Effekseer\EffekseerSoundXAudio2.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EffectManager : public ObjectManager
{
private:
	static const WCHAR* c_filename[];
	//= {
	//	// BGM
	//	_T("data/SOUND/BGM/WhiteLily_WithoutV.wav"),
	//	_T("data/SOUND/BGM/WhiteLily_Violin.wav")
	//};

public:
	//struct Prop
	//{
	//	CXModel			*CXModel;			// ���f���i�[�p
	//	D3DXVECTOR3		vPos;				// ���W���
	//	D3DXVECTOR3		vRot;				// ��]���
	//	D3DXVECTOR3		vScl;				// �g�k���
	//	D3DXMATRIX		mtxWorld;			// ���[���h�}�g���N�X
	//	bool			bUse;
	//}*prop;

	enum EFFECT
	{	// �v���C���[�Ǘ�
		EFFECT1,
		EFFECT2,
		EFFECT3,
		EFFECT4,
		EFFECT_MAX
	};
	//static const TCHAR* c_filename[EFFECT_MAX];

	::Effekseer::Manager*				m_manager;
	::EffekseerRendererDX9::Renderer*	m_renderer;
	::EffekseerSound::Sound*			m_sound;
	::Effekseer::Effect*				m_effect[EFFECT_MAX];
	::Effekseer::Handle					m_handle;
	::Effekseer::Vector3D				m_position;
	::Effekseer::Vector3D				m_rotation;
	::Effekseer::Matrix44				mtx44View, mtx44Pro;

	// �T�E���h
	//IXAudio2*						g_xa2 = NULL;
	//IXAudio2MasteringVoice*			g_xa2_master = NULL;

	// �R���X�g���N�^�i�����������j
	EffectManager(void);
	//�f�X�g���N�^�i�I�������j
	~EffectManager(void);

	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif