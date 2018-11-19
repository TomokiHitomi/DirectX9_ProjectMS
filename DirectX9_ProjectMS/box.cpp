//=============================================================================
//
// �{�b�N�X���� [box.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "calculate.h"
#include "shader.h"
#include "box.h"
#include "particle.h"

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
Box::Box()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�|�C���^�̏�����
	pTexture = NULL;	// �e�N�X�`��
	pVtxBuff = NULL;	// ���_�o�b�t�@
	pInstBuff = NULL;	// �C���X�^���V���O�o�b�t�@
	pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@
	pDecl = NULL;		// ���_�錾

	// �V�F�[�_�֘A�̏�����
	pEffect = NULL;		// �V�F�[�_

	fRot = 0.0f;
	fColor = BOX_COLOR_MAX;
	bColor = false;

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		BOX_TEXTURE,
		&pTexture)))
	{
		// �G���[
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", BOX_TEXTURE, MB_OK);
		//return S_FALSE;
	}


	if (pEffect == NULL)
	{
		// �V�F�[�_�̃A�h���X���擾
		pEffect = ShaderManager::GetEffect(ShaderManager::BOX);
	}

	MakeVertex(pDevice);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Box::~Box()
{
	Release();
}

//=============================================================================
// �������
//=============================================================================
void Box::Release(void)
{
	// �������
	SAFE_RELEASE(pTexture);		// �e�N�X�`��
	SAFE_RELEASE(pVtxBuff);		// ���_�o�b�t�@
	SAFE_RELEASE(pInstBuff);	// �C���X�^���V���O�o�b�t�@
	SAFE_RELEASE(pIdxBuff);		// �C���f�b�N�X�o�b�t�@
	SAFE_RELEASE(pDecl);		// ���_�錾
	//SAFE_RELEASE(pErrorBuff);	// �V�F�[�_�p�R���p�C���G���[
	//SAFE_RELEASE(pEffect);		// �V�F�[�_
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Box::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
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
	D3DXVECTOR2 CubeUV[] = {	D3DXVECTOR2(0.0f, 0.0f),
								D3DXVECTOR2(1.0f, 0.0f),
								D3DXVECTOR2(0.0f, 1.0f),
								D3DXVECTOR2(1.0f, 1.0f),
	};


	/***** ���_�o�b�t�@�ݒ� *****/

	// ���_�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PLANE) * NUM_VERTEX * 6,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,										// ���_�o�b�t�@�̎g�p�@�@
		0,										// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVtxBuff,								// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_PLANE *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		WORD k = 0;
		for (DWORD i = 0; i < 6; i++)
		{
			for (DWORD j = 0; j < NUM_VERTEX; j++)
			{
				// ���_���W�̐ݒ�
				pVtx->vtx = CubePosition[CubeVertList[k++]];
				// �e�N�X�`�����W�̐ݒ�
				pVtx->tex = CubeUV[j];
				pVtx++;
			}
		}

		// ���_�f�[�^���A�����b�N����
		pVtxBuff->Unlock();
	}


	/***** �C���f�b�N�X�o�b�t�@�ݒ� *****/


	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36 ,						// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pIdxBuff,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{// ���W�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
		pIdxBuff->Unlock();
	}


	/***** �C���X�^���V���O�p�̍��W�o�b�t�@�ݒ� *****/

	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(INSTANCE_PLANE) * BOX_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		0,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pInstBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	int count1 = BOX_MAX;
	int count2 = 0;

	{// �C���X�^���V���O�o�b�t�@�̒��g�𖄂߂�
		INSTANCE_PLANE *pInst;


		// ���W�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pInstBuff->Lock(0, 0, (void**)&pInst, 0);

		// ���W�̐ݒ�
		//for (unsigned int i = 0; i < PLANE_Y_MAX + 1; i++)
		//{
		//	for (unsigned int j = 0; j < PLANE_X_MAX + 1; j++)
		//	{
		//		if ((i == 0 || i == PLANE_Y_MAX) || (j == 0 || j == PLANE_X_MAX))
		//		{
		//			for (unsigned int k = 0; k < BOX_Y_MAX; k++)
		//			{
		//				pInst->pos = D3DXVECTOR3(
		//					j * PLANE_SIZE_X * 2 - ((PLANE_X_MAX+1) * PLANE_SIZE_X),
		//					k * BOX_SIZE_X*2 + (BOX_SIZE_X*2),
		//					i * PLANE_SIZE_Y * 2 - ((PLANE_Y_MAX+1) * PLANE_SIZE_Y));
		//				//pInst->diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//				pInst->diffuse = SetColorPalletRandomGreen();
		//				pInst->angle = float(rand() % 614) * 0.01f;
		//				pInst++;
		//				count2++;
		//			}
		//		}
		//	}
		//}

		D3DXVECTOR3 posTmp;
		for (unsigned int i = 0; i < BOX_Z_MAX; i++)
		{
			for (unsigned int j = 0; j < BOX_X_MAX; j++)
			{
				for (unsigned int k = 0; k < BOX_Y_MAX; k++)
				{
					posTmp = D3DXVECTOR3(
						j * (PLANE_X_MAX * PLANE_SIZE_X * 2 + BOX_MARGIN) / (BOX_X_MAX - 1)
						- (PLANE_X_MAX * PLANE_SIZE_X * 2 + BOX_MARGIN) / 2,
						k * (PLANE_X_MAX * PLANE_SIZE_X * 2 + BOX_MARGIN) / (BOX_X_MAX - 1)
						+ BOX_HEIGHT,
						i * (PLANE_Y_MAX * PLANE_SIZE_Y * 2 + BOX_MARGIN) / (BOX_Z_MAX - 1)
						- (PLANE_Y_MAX * PLANE_SIZE_Y * 2 + BOX_MARGIN) / 2);
					ParticleManager::Set(100, posTmp);
					if (k == BOX_Y_MAX - 1 || (i == 0 || i == BOX_Z_MAX - 1) || (j == 0 || j == BOX_X_MAX - 1))
					{
						pInst->pos = posTmp;
						//pInst->diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pInst->diffuse = SetColorPalletRandomGreen();
						pInst->angle = float(rand() % 614) * 0.01f;
						pInst++;
						count2++;
					}
				}
			}
		}

		// ���W�f�[�^���A�����b�N����
		pInstBuff->Unlock();
	}


	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// VTX
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// ���[���h�ʒu
		{ 1, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		// �����p�x
		{ 1, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// ���_�J���[
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);

	return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void Box::Update(void)
{
	fRot += BOX_ROT_SPEED;
	//fRot = PiCalculate360(fRot + BOX_ROT_SPEED);

	if (bColor)
	{
		fColor += BOX_COLOR_SPEED;
		if (fColor > BOX_COLOR_MAX)
		{
			bColor = false;
		}
	}
	else
	{
		fColor -= BOX_COLOR_SPEED;
		if (fColor < -BOX_COLOR_MAX)
		{
			bColor = true;
		}
	}


}
//=============================================================================
// �`�揈��
//=============================================================================
void Box::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�E�v���W�F�N�V�����s����擾
	D3DXMATRIX mtxWorld, mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//����

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, BOX_ALPHA);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//// ���Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//////pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

	//// ���C���e�B���O�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �C���X�^���X�錾
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | BOX_MAX);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// ���_�ƃC���f�b�N�X��ݒ�
	pDevice->SetVertexDeclaration(pDecl);
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_PLANE));		// ���_�o�b�t�@
	pDevice->SetStreamSource(1, pInstBuff, 0, sizeof(INSTANCE_PLANE));	// �C���X�^���X�o�b�t�@
	pDevice->SetIndices(pIdxBuff);										// �C���f�b�N�X�o�b�t�@

	// �g�p����e�N�j�b�N���`
	if (FAILED(pEffect->SetTechnique("Tec01")))
	{
		// �G���[
		MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "Tec01", MB_OK);
		//return S_FALSE;
	}

	// �V�F�[�_�[�̊J�n�AnumPass�ɂ͎w�肵�Ă���e�N�j�b�N�ɒ�`���Ă���pass�̐����ς���
	UINT numPass = 0;
	pEffect->Begin(&numPass, 0);

	// �p�X���w�肵�ĊJ�n
	pEffect->BeginPass(0);

	// �e�N�X�`�����Z�b�g
	pEffect->SetTexture("tex", pTexture);

	// ��]�ʂ��Z�b�g
	pEffect->SetFloat("rot", fRot);
	// �J���[���Z�b�g
	pEffect->SetFloat("color", fColor);

	//// �ڂ����l���Z�b�g
	//float fBlur = 0.05f;
	//pEffect->SetFloat("AddU", fBlur);
	//pEffect->SetFloat("AddV", fBlur);


	// �K�v�ȍs������Z�b�g
	pEffect->SetMatrix("proj", &mtxProjection);
	pEffect->SetMatrix("view", &mtxView);
	pEffect->SetMatrix("world", &mtxWorld);

	// ���ʂ��m�肳����
	pEffect->CommitChanges();

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * 6, 0, 2 * 6);

	// �V�F�[�_�[�p�X���I��
	pEffect->EndPass();
	// �V�F�[�_�[���I��
	pEffect->End();

	// �C���X�^���X�錾��W���ɖ߂�
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

	//// �ʏ�u�����h�ɖ߂�
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//// ���C���e�B���O��L���ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�Ж�
}