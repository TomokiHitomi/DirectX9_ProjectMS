//=============================================================================
//
// �J�������� [camera.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "calculate.h"

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
D3DXVECTOR3		Camera::s_vEye[3];
D3DXVECTOR3		Camera::s_vAt[3];
D3DXVECTOR3		Camera::s_vUp[3];
D3DXVECTOR3		Camera::s_vEyeNext[3];
D3DXVECTOR3		Camera::s_vAtNext[3];
D3DXVECTOR3		Camera::s_vUpNext[3];
D3DXMATRIX		Camera::s_mtxView;
D3DXMATRIX		Camera::s_mtxProjection;
D3DXMATRIX		Camera::s_mtxWorld;
float			Camera::s_fEyeIner;
float			Camera::s_fAtIner;
float			Camera::s_fUpIner;
D3DVIEWPORT9	Camera::dvPort[3];
float			Camera::fAspect[3];

//=============================================================================
// ����������
//=============================================================================
void Camera::Init(void)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		s_vEye[i] = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
		s_vAt[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_vUp[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		s_vEyeNext[i] = s_vEye[i];
		s_vAtNext[i] = s_vAt[i];
		s_vUpNext[i] = s_vUp[i];
	}

	s_fEyeIner	= 1.0f;
	s_fAtIner	= 1.0f;
	s_fUpIner	= 1.0f;


	dvPort[0] = D3DVIEWPORT9{ 0, 0, DWORD(SCREEN_WIDTH / 2), DWORD(SCREEN_HEIGHT), 0.0f, DWORD(1.0f) };
	dvPort[1] = D3DVIEWPORT9{ DWORD(SCREEN_WIDTH / 2), 0, DWORD(SCREEN_WIDTH / 2), DWORD(SCREEN_HEIGHT),0.0f,DWORD(1.0f) };
	dvPort[2] = D3DVIEWPORT9{ 0, 0, DWORD(SCREEN_WIDTH), DWORD(SCREEN_HEIGHT), 0.0f, DWORD(1.0f) };

	fAspect[0] = ((float)SCREEN_WIDTH / 2) / ((float)SCREEN_HEIGHT);
	fAspect[1] = ((float)SCREEN_WIDTH / 2) / ((float)SCREEN_HEIGHT);
	fAspect[2] = ((float)SCREEN_WIDTH) / ((float)SCREEN_HEIGHT);

}

//=============================================================================
// �I������
//=============================================================================
void Camera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Camera::Update(void)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		s_vEye[i] = s_vEye[i] + ((s_vEyeNext[i] - s_vEye[i]) * s_fEyeIner);
		s_vAt[i] = s_vAt[i] + ((s_vAtNext[i] - s_vAt[i]) * s_fAtIner);

	}
//#ifdef _DEBUG
//	PrintDebugProc("�y Camera �z\n");
//	PrintDebugProc("Eye [%f,%f,%f]  Iner[%f]\n", s_vEye.x, s_vEye.y, s_vEye.z, s_fEyeIner);
//	PrintDebugProc("At  [%f,%f,%f]  Iner[%f]\n", s_vAt.x, s_vAt.y, s_vAt.z, s_fAtIner);
//	PrintDebugProc("Up  [%f,%f,%f]  Iner[%f]\n", s_vUp.x, s_vUp.y, s_vUp.z, s_fUpIner);
//	PrintDebugProc("\n");
//#endif
}

//=============================================================================
// �J�����̒����_�ݒ菈��
//=============================================================================
void Camera::SetAt(D3DXVECTOR3 vAt, int nNum)
{
	//camera->posCameraAt = vAt;
	s_vAtNext[nNum] = vAt;
}

//=============================================================================
// �J�����̎��_�ݒ菈��
//=============================================================================
void Camera::SetEye(D3DXVECTOR3 vEye, int nNum)
{
	//camera->posCameraEye = vEye;
	s_vEyeNext[nNum] = vEye;
}

//=============================================================================
// �J�����̏㕔�ݒ菈��
//=============================================================================
void Camera::SetUp(D3DXVECTOR3 vUp, int nNum)
{
	s_vUp[nNum] = vUp;
	//camera->vUpNext = vUp;
}

//=============================================================================
// �J�����̒����_�̊����ݒ菈��
//=============================================================================
void Camera::SetAtIner(float fIner)
{
	s_fAtIner = SetLimit(fIner, 1.0f, 0.0f);
}

//=============================================================================
// �J�����̎��_�̊����ݒ菈��
//=============================================================================
void Camera::SetEyeIner(float fIner)
{
	s_fEyeIner = SetLimit(fIner, 1.0f, 0.0f);
}

//=============================================================================
// �J�����̏㕔�̊����ݒ菈��
//=============================================================================
void Camera::SetUpIner(float fIner)
{
	s_fUpIner = SetLimit(fIner, 1.0f, 0.0f);
}

//=============================================================================
// �J�����̒����_�̊�����������
//=============================================================================
void Camera::AddAtIner(float fIner)
{
	s_fAtIner = SetLimit(s_fAtIner + fIner, 1.0f, 0.0f);
}

//=============================================================================
// �J�����̎��_�̊�����������
//=============================================================================
void Camera::AddEyeIner(float fIner)
{
	s_fEyeIner = SetLimit(s_fEyeIner + fIner, 1.0f, 0.0f);
}

//=============================================================================
// �J�����̏㕔�̊�����������
//=============================================================================
void Camera::AddUpIner(float fIner)
{
	s_fUpIner = SetLimit(s_fUpIner + fIner, 1.0f, 0.0f);
}


//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void Camera::Set(int nMulti)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	/******************** �r���[�C���O�ϊ� ********************/
	// �r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&s_mtxView);

	// �r���[�}�g���N�X�̍쐬
	D3DXMatrixLookAtLH(&s_mtxView,
		&s_vEye[nMulti],	// ���_
		&s_vAt[nMulti],		// �����_
		&s_vUp[nMulti]);	// �����

	pDevice->SetViewport(&dvPort[nMulti]);

	// �r���[�}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_mtxView);

	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(g_color[i].r, g_color[i].b, g_color[i].g), 1.0f, 0);
	//pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	/******************** �v���W�F�N�V�����ϊ� ********************/
	// �v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixIdentity(&s_mtxProjection);

	// �v���W�F�N�V�����}�g���N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&s_mtxProjection,
		VIEW_ANGLE,			// �r���[���ʂ̎���p
		//VIEW_ASPECT,		// �r���[���ʂ̃A�X�y�N�g��
		fAspect[nMulti],
		VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l�i�߂��ƕ`�悵�Ȃ��j
		VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l�i�����ƕ`�悵�Ȃ��j

	// �v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_mtxProjection);



	//D3DXMatrixIdentity(&Camera[i]->mtxView);																				//�r���[�}�g���N�X�̏�����
	//D3DXMatrixLookAtLH(&Camera[i]->mtxView, &Camera[i]->posCameraEye, &Camera[i]->posCameraAt, &Camera[i]->vecCameraUp);	//�r���[�}�g���N�X�̍쐬

	//pDevice->SetViewport(&Camera[i]->Port);
	//pDevice->SetTransform(D3DTS_VIEW, &Camera[i]->mtxView);																//�r���[�}�g���N�X�̐ݒ�
	//																													//�`��̈�ɂ�������C�ӂ̐F�ŃN���A
	//pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(g_color[i].r, g_color[i].b, g_color[i].g), 1.0f, 0);
	//D3DXMatrixIdentity(&Camera[i]->mtxProjection);																		//�v���W�F�N�V�����}�g���N�X�̏�����
	//D3DXMatrixPerspectiveFovLH(&Camera[i]->mtxProjection, VIEW_ANGLE, Camera[i]->Aspect, VIEW_NEAR_Z, VIEW_FAR_Z);				//�v���W�F�N�V�����}�g���N�X�̍쐬
	//pDevice->SetTransform(D3DTS_PROJECTION, &Camera[i]->mtxProjection);													//�v���W�F�N�V�����}�g���N�X�̐ݒ�
}

////=============================================================================
//// �J�����Ƒ΂ɂȂ��]�s����擾
////=============================================================================
//D3DXMATRIX Camera::GetInvRotateMat(D3DXVECTOR3 pos)
//{
//	D3DXMATRIX Inv;
//	D3DXMatrixIdentity(&Inv);
//	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &GetLookAtVct(), &camera->vecCameraUp);
//	D3DXMatrixInverse(&Inv, NULL, &Inv);
//
//	return Inv;
//}

////=============================================================================
//// �����_�Ǝ��_�̐��K�����ꂽ�x�N�g�����擾����֐�
////=============================================================================
//D3DXVECTOR3 Camera::GetLookAtVct(void)
//{
//	CAMERA *camera = GetCamera();
//	D3DXVECTOR3	vecLookAtVct;
//	vecLookAtVct = camera->posCameraEye - camera->posCameraAt;
//	return vecLookAtVct;
//}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX Camera::GetMtxView(void)
{
	return s_mtxView;
}

//=============================================================================
// �v���W�F�N�V�����}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX Camera::GetMtxProjection(void)
{
	return s_mtxProjection;
}