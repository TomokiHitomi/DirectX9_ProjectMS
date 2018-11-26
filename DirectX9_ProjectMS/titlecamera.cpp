//=============================================================================
//
// �v���C���[���� [ko.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titlecamera.h"
#include "camera.h"
#include "character.h"
#include "calculate.h"
#include <math.h>
// �f�o�b�O�p
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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Titlecamera::Titlecamera()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::TITLECAMERA, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Titlecamera::~Titlecamera()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Titlecamera::Init()
{
	TitlecameraObj[0].Pos = D3DXVECTOR3(0.0, 30.0, 90.0);
	TitlecameraObj[0].Angle = 0.0f;

	// �J������At�����f���ɐݒ�
	CameraManager::pCamera[CameraManager::SINGLE]->SetAt(ZERO_D3DXVECTOR3);

	// �J����Eye�����f������ɃZ�b�g
	CameraManager::pCamera[CameraManager::SINGLE]->SetEye(ZERO_D3DXVECTOR3 + TitlecameraObj[0].Pos);

	TitlecameraObj[0].Use = true;
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void Titlecamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Titlecamera::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG

#endif
	TitlecameraObj[0].Angle += TITLECAMERA_ROT_SPEED;
	TitlecameraObj[0].Pos.x = sinf(TitlecameraObj[0].Angle)*TITLECAMERA_LENGTH;
	TitlecameraObj[0].Pos.z = cosf(TitlecameraObj[0].Angle)*TITLECAMERA_LENGTH;
	// �J������At�����f���ɐݒ�
	CameraManager::pCamera[CameraManager::SINGLE]->SetAt(ZERO_D3DXVECTOR3);
	//Camera::SetAt(m_vTag, m_nNum);

	// �J����Eye�����f������ɃZ�b�g
	CameraManager::pCamera[CameraManager::SINGLE]->SetEye(ZERO_D3DXVECTOR3 + TitlecameraObj[0].Pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void Titlecamera::Draw(void)
{

}
