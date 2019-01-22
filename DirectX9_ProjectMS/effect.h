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
		EFFECT_GUARD,
		EFFECT_JUMPEND,
		//EFFECT_PASTRY,
		//EFFECT_IDOL,
		EFFECT_MAGIC,
		//EFFECT2,
		//EFFECT3,
		//EFFECT4,
		//EFFECT5,
		EFFECT_MAX
	};
	//static const TCHAR* c_filename[EFFECT_MAX];

	::Effekseer::Manager*				m_manager;
	::EffekseerRendererDX9::Renderer*	m_renderer;
	::Effekseer::Effect*				m_effect[EFFECT_MAX];
	::Effekseer::Handle					m_handle;
	::Effekseer::Vector3D				m_position;
	::Effekseer::Vector3D				m_rotation;
	::Effekseer::Matrix44				mtx44View, mtx44Pro;

	//// �T�E���h
	//::EffekseerSound::Sound*			m_sound;
	//IXAudio2*						m_xa2 = NULL;
	//IXAudio2MasteringVoice*			m_xa2_master = NULL;

	// �R���X�g���N�^�i�����������j
	EffectManager(void);
	//�f�X�g���N�^�i�I�������j
	~EffectManager(void);

	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);

public:
	::Effekseer::Handle Play(EFFECT eEffect, D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	void Pause(bool bUse);
	void SetColor(::Effekseer::Handle handle, D3DXCOLOR xColor);
	void SetMatrix(::Effekseer::Handle handle, D3DXMATRIX mtx);
	void SetPos(::Effekseer::Handle handle, D3DXVECTOR3 vPos);
	void SetScale(::Effekseer::Handle handle, D3DXVECTOR3 vScl);
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
::Effekseer::Matrix44 ConvertMtx44(D3DXMATRIX mtx);
::Effekseer::Matrix43 ConvertMtx43(D3DXMATRIX mtx);

#endif