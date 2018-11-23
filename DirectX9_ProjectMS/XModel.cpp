//=============================================================================
//
// ���f������ [XModel.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "XModel.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//=============================================================================
// �R���X�g���N�^�i�����������j
//=============================================================================
CXModel::CXModel(void)
{
	// ���f���֌W�̏�����
	pTexture = NULL;
	pMesh = NULL;
	pBuffMat = NULL;
	dwNumMat = 0;
	bLight = true;

	pEffect = NULL;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CXModel::Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pMeshPass, LPSTR pTexPass)
{
	// ���f���f�[�^�ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
		pMeshPass,				// ���f���f�[�^
		D3DXMESH_SYSTEMMEM,		// �g�p���郁�����̃I�v�V����
		pDevice,				// �f�o�C�X
		NULL,					// ���g�p
		&pBuffMat,				// �}�e���A���f�[�^
		NULL,					// ���g�p
		&dwNumMat,				// D3DXMATERIAL�\���̂̐�
		&pMesh)))				// ���b�V���f�[�^�ւ̃|�C���^
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", pMeshPass, MB_OK);
		return E_FAIL;
	}
	if (pTexPass)
	{
		// �e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,				// �f�o�C�X
			pTexPass,				// �t�@�C����
			&pTexture)))			// �ǂݍ��ރ������i�����Ȃ�z��Ɂj
		{
			MessageBox(NULL, "X�t�@�C���̃e�N�X�`���ǂݍ��݂Ɏ��s���܂���", pTexPass, MB_OK);
			return E_FAIL;
		}
	}
}

//=============================================================================
// �������
//=============================================================================
void CXModel::Release(void)
{
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pBuffMat);
}

//=============================================================================
// �X�V����
//=============================================================================
void CXModel::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CXModel::Draw(D3DXMATRIX mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 pMatDef;
	HRESULT hr;

	// �r���[�E�v���W�F�N�V�����s����擾
	D3DXMATRIX mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	if (pEffect == NULL)
	{
		// �V�F�[�_�̃A�h���X���擾
		pEffect = ShaderManager::GetEffect(ShaderManager::XMODEL);
	}

	// �}�e���A�����ɑ΂���|�C���^�̎擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();


	// �g�p����e�N�j�b�N���`
	if (bLight)
	{	// ���C�gON
		if (pTexture)
		{
			hr = pEffect->SetTechnique("LIGHT_ON_TEX");
		}
		else
		{
			hr = pEffect->SetTechnique("LIGHT_ON");
		}
	}
	else
	{	// ���C�gOFF
		if (pTexture)
		{
			hr = pEffect->SetTechnique("LIGHT_OFF_TEX");
		}
		else
		{
			hr = pEffect->SetTechnique("LIGHT_OFF");
		}
	}

	if (FAILED(hr))
	{
		// �G���[
		MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂����B", "XMODEL", MB_OK);
	}

	// �V�F�[�_�[�̊J�n�AnumPass�ɂ͎w�肵�Ă���e�N�j�b�N�ɒ�`���Ă���pass�̐����ς���
	UINT numPass = 0;
	pEffect->Begin(&numPass, 0);

	// �p�X���w�肵�ĊJ�n
	pEffect->BeginPass(0);

	// �K�v�ȍs������Z�b�g
	pEffect->SetMatrix("proj", &mtxProjection);
	pEffect->SetMatrix("view", &mtxView);
	pEffect->SetMatrix("world", &mtxWorld);

	if (bLight)
	{	// ���C�gON
		Camera* pCamera = CameraManager::GetCameraNow();
		D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
		if (FAILED(pEffect->SetVector("eye",&eyeTmp)))
		{
			// �G���[
			MessageBox(NULL, "�J����Eye���̃Z�b�g�Ɏ��s���܂����B", "eye", MB_OK);
		}
		// ���C�g�����擾
		Light* pLight = LightManager::GetLightAdr(LightManager::Main);
		// ���C�g�����Z�b�g
		if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
		{
			// �G���[
			MessageBox(NULL, "���C�g���̃Z�b�g�Ɏ��s���܂����B", "lt", MB_OK);
		}
		//SetShaderLight(pEffect, GetLight(0));
	}

	//���b�V���̕`��
	D3DXVECTOR4  temp;
	for (int i = 0; i < (int)dwNumMat; i++)
	{
		// �}�e���A�����Z�b�g
		pEffect->SetValue("mat", &pMat[i].MatD3D, sizeof(D3DMATERIAL9));

		// �e�N�X�`�����Z�b�g
		pEffect->SetTexture("tex", pTexture);

		// ���ʂ��m�肳����
		pEffect->CommitChanges();

		// �`��
		pMesh->DrawSubset(i);
	}

	// �V�F�[�_�[�p�X���I��
	pEffect->EndPass();
	// �V�F�[�_�[���I��
	pEffect->End();
}