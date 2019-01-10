#include "SkinPmx.h"
#include "shader.h"

#include "camera.h"
#include "box.h"

CSkinPmx::CSkinPmx(void)
{
	// �e�|�C���^�̏�����
	pTexture = NULL;	// �e�N�X�`��
	pVtxBuff = NULL;	// ���_�o�b�t�@
	pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@
	pDecl = NULL;		// ���_�錾

	// �V�F�[�_�֘A�̏�����
	pEffect = NULL;		// �V�F�[�_

	pVtxCount = NULL;
	pFaceCount = NULL;

	nMeshCount = 0;
}

CSkinPmx::~CSkinPmx(void)
{
	Release();
}

HRESULT CSkinPmx::Init(void)
{
	// ���_�f�[�^
	D3DXVECTOR4 CubePosition[] = {
							D3DXVECTOR4(-BOX_SIZE, BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE,  BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE,  -BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 0.0f),

							D3DXVECTOR4(BOX_SIZE, BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE,  BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE, -BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE, -BOX_SIZE,  BOX_SIZE, 0.0f),
	};
	// �C���f�b�N�X�f�[�^
	//	�O(z=-1)  ��(x=-1)  ��(z=+1)  �E(x=+1)  ��(y=+1)  ��(y=-1)
	WORD CubeVertList[] = { 0,1,2,3,  5,0,7,2,  4,5,6,7,  1,4,3,6,  5,4,0,1,  6,7,3,2 };

	// UV�f�[�^
	D3DXVECTOR2 CubeUV[] = { D3DXVECTOR2(0.0f, 0.0f),
								D3DXVECTOR2(1.0f, 0.0f),
								D3DXVECTOR2(0.0f, 1.0f),
								D3DXVECTOR2(1.0f, 1.0f),
	};


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �V�F�[�_�̃A�h���X���擾
	pEffect = ShaderManager::GetEffect(ShaderManager::SKINPMX);

	nMeshCount = 1;
	// �e�o�b�t�@���m��
	pTexture = new LPDIRECT3DTEXTURE9[nMeshCount];
	pVtxBuff = new LPDIRECT3DVERTEXBUFFER9[nMeshCount];
	pIdxBuff = new LPDIRECT3DINDEXBUFFER9[nMeshCount];
	pVtxCount = new unsigned int[nMeshCount];
	pFaceCount = new unsigned int[nMeshCount];

	// �m�ۂ����o�b�t�@��NULL�A�J�E���^�� 0 �ŏ�����
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		pTexture[i] = NULL;
		pVtxBuff[i] = NULL;
		pIdxBuff[i] = NULL;
		pVtxCount[i] = 0;
		pFaceCount[i] = 0;
	}

	// ���_�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PMX) * NUM_VERTEX * 6,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,										// ���_�o�b�t�@�̎g�p�@�@
		0,										// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVtxBuff[0],								// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	pVtxCount[0] = NUM_VERTEX * 6;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_PMX *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pVtxBuff[0]->Lock(0, 0, (void**)&pVtx, 0);

		WORD k = 0;
		for (DWORD i = 0; i < 6; i++)
		{
			for (DWORD j = 0; j < NUM_VERTEX; j++)
			{
				D3DXVECTOR3 temp4 = CubePosition[CubeVertList[k++]];
				D3DXVECTOR3 temp3 = D3DXVECTOR3(temp4.x, temp4.y, temp4.z);
				// ���_���W�̐ݒ�
				pVtx->pos = temp3;
				//pVtx->normal = D3DXVECTOR3
				// �e�N�X�`�����W�̐ݒ�
				pVtx->uv = CubeUV[j];
				pVtx++;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pVtxBuff[0]->Unlock();
	}


	/***** �C���f�b�N�X�o�b�t�@�ݒ� *****/


	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36,						// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pIdxBuff[0],							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	pFaceCount[0] = 36;


	{// ���W�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pIdxBuff[0]->Lock(0, 0, (void**)&pIdx, 0);

		// ���_���W�̐ݒ�
		for (WORD m = 0; m < 6; m++)
		{
			*pIdx++ = 0 + 4 * m;
			*pIdx++ = 1 + 4 * m;
			*pIdx++ = 2 + 4 * m;
			*pIdx++ = 2 + 4 * m;
			*pIdx++ = 1 + 4 * m;
			*pIdx++ = 3 + 4 * m;
		}

		// ���_�f�[�^���A�����b�N����
		pIdxBuff[0]->Unlock();
	}


	// ���_���̐錾
	D3DVERTEXELEMENT9 declElems[] = {
	{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// pos
	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },		// normal
	{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// uv
	//{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// boneId
	//{ 0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		// boneWeight
	D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);
}

void CSkinPmx::Update(void)
{

}

void CSkinPmx::Draw(D3DXMATRIX mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 pMatDef;

	// �r���[�E�v���W�F�N�V�����s����擾
	D3DXMATRIX mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	//// �}�e���A�����ɑ΂���|�C���^�̎擾
	//pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();


	//// ���ʕ`�悷��
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (unsigned int i = 0; i < nMeshCount; i++)
	{

		//// �C���X�^���X�錾
		//pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | 1);

		// ���_�錾
		pDevice->SetVertexDeclaration(pDecl);

		// ���_�ƃC���f�b�N�X��ݒ�
		pDevice->SetStreamSource(0, pVtxBuff[i], 0, sizeof(VERTEX_PMX));		// ���_�o�b�t�@
		pDevice->SetIndices(pIdxBuff[i]);										// �C���f�b�N�X�o�b�t�@

	// �g�p����e�N�j�b�N���`
		if (0)
		{	// ���C�gON
			if (FAILED(pEffect->SetTechnique("LIGHT_ON")))
			{
				// �G���[
				MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "LIGHT_ON", MB_OK);
				//return S_FALSE;
			}
		}
		else
		{	// ���C�gOFF
			if (FAILED(pEffect->SetTechnique("LIGHT_OFF")))
			{
				// �G���[
				MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "LIGHT_OFF", MB_OK);
				//return S_FALSE;
			}
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

		//if (bLight)
		//{	// ���C�gON
		//	Camera* pCamera = CameraManager::GetCameraNow();
		//	D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
		//	if (FAILED(pEffect->SetVector("eye", &eyeTmp)))
		//	{
		//		// �G���[
		//		MessageBox(NULL, "�J����Eye���̃Z�b�g�Ɏ��s���܂����B", "eye", MB_OK);
		//	}
		//	// ���C�g�����擾
		//	Light* pLight = LightManager::GetLightAdr(LightManager::Main);
		//	// ���C�g�����Z�b�g
		//	if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
		//	{
		//		// �G���[
		//		MessageBox(NULL, "���C�g���̃Z�b�g�Ɏ��s���܂����B", "lt", MB_OK);
		//	}
		//	//SetShaderLight(pEffect, GetLight(0));
		//}

		//���b�V���̕`��
		//for (int i = 0; i < (int)dwNumMat; i++)
		//{
			//if (bLight)
			//{	// ���C�gON
			//	// �}�e���A�����Z�b�g
			//	pEffect->SetValue("mat", &pMat[i].MatD3D, sizeof(D3DMATERIAL9));
			//	//SetShaderMat(pEffect, pMat[i].MatD3D);
			//}

		// �e�N�X�`�����Z�b�g
		pEffect->SetTexture("tex", pTexture[i]);

		// ���ʂ��m�肳����
		pEffect->CommitChanges();

		//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pFaceCount[i]);

		// �|���S���̕`��
		if (FAILED(pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxCount[i], 0, pFaceCount[i])))
		{
			// �G���[
			MessageBox(NULL, "�`��Ɏ��s", "Draw", MB_OK);
		}
		//}

		// �V�F�[�_�[�p�X���I��
		pEffect->EndPass();
		// �V�F�[�_�[���I��
		pEffect->End();
	}

	//// �C���X�^���X�錾��W���ɖ߂�
	//pDevice->SetStreamSourceFreq(0, 1);

	//// ���ʂ��J�����O�ɖ߂�
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �Œ�@�\�ɖ߂�
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}


void CSkinPmx::Release(void)
{
	// �������
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		SAFE_RELEASE(pTexture[i]);		// �e�N�X�`��
		SAFE_RELEASE(pVtxBuff[i]);		// ���_�o�b�t�@
		SAFE_RELEASE(pIdxBuff[i]);		// �C���f�b�N�X�o�b�t�@
	}

	SAFE_DELETE_ARRAY(pTexture);
	SAFE_DELETE_ARRAY(pVtxBuff);
	SAFE_DELETE_ARRAY(pIdxBuff);
	SAFE_DELETE_ARRAY(pVtxCount);
	SAFE_DELETE_ARRAY(pFaceCount);

	SAFE_RELEASE(pDecl);		// ���_�錾
}