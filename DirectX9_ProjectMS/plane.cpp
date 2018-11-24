//=============================================================================
//
// �v���[������ [plane.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "calculate.h"
#include "shader.h"
#include "plane.h"

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
Plane::Plane()
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

	fColor = PLANE_COLOR_MAX;
	bColor = false;

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		PLANE_TEXTURE,
		&pTexture)))
	{
		// �G���[
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", PLANE_TEXTURE, MB_OK);
		//return S_FALSE;
	}


	if (pEffect == NULL)
	{
		// �V�F�[�_�̃A�h���X���擾
		pEffect = ShaderManager::GetEffect(ShaderManager::PLANE);
	}

	MakeVertex(pDevice);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Plane::~Plane()
{
	Release();
}

//=============================================================================
// �������
//=============================================================================
void Plane::Release(void)
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
HRESULT Plane::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	/***** ���_�o�b�t�@�ݒ� *****/

	// ���_�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PLANE) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		0,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVtxBuff,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_PLANE *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR4(-PLANE_SIZE_X + PLANE_MARGIN, 0.0f, PLANE_SIZE_Y - PLANE_MARGIN, 1.0f);
		pVtx[1].vtx = D3DXVECTOR4(PLANE_SIZE_X - PLANE_MARGIN, 0.0f, PLANE_SIZE_Y - PLANE_MARGIN, 1.0f);
		pVtx[2].vtx = D3DXVECTOR4(-PLANE_SIZE_X + PLANE_MARGIN, 0.0f, -PLANE_SIZE_Y + PLANE_MARGIN, 1.0f);
		pVtx[3].vtx = D3DXVECTOR4(PLANE_SIZE_X - PLANE_MARGIN, 0.0f, -PLANE_SIZE_Y + PLANE_MARGIN,	1.0f);

		// �e�N�X�`�����W�̐ݒ�
		int x = 0 % PLANE_TEXTURE_PATTERN_DIVIDE_X;
		int y = 0 / PLANE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / PLANE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / PLANE_TEXTURE_PATTERN_DIVIDE_Y;

		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		pVtxBuff->Unlock();
	}


	/***** �C���f�b�N�X�o�b�t�@�ݒ� *****/

	WORD wIndex[6] = { 0, 1, 2, 2, 1, 3 };

	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(wIndex),						// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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
		for (unsigned int i = 0; i < 6; i++, pIdx++)
		{
			*pIdx = wIndex[i];
		}

		// ���_�f�[�^���A�����b�N����
		pIdxBuff->Unlock();
	}


	/***** �C���X�^���V���O�p�̍��W�o�b�t�@�ݒ� *****/

	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(INSTANCE_PLANE) * PLANE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		0,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pInstBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{// �C���X�^���V���O�o�b�t�@�̒��g�𖄂߂�
		INSTANCE_PLANE *pInst;


		// ���W�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pInstBuff->Lock(0, 0, (void**)&pInst, 0);

		// ���W�̐ݒ�
		for (unsigned int i = 0; i < PLANE_Y_MAX; i++)
		{
			for (unsigned int j = 0; j < PLANE_X_MAX; j++)
			{
				pInst->pos = D3DXVECTOR3(
					j * PLANE_SIZE_X * 2 - ((PLANE_X_MAX - 1) * PLANE_SIZE_X),
					0.0f,
					i * PLANE_SIZE_Y * 2 - ((PLANE_Y_MAX - 1) * PLANE_SIZE_Y));
				//pInst->diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pInst->diffuse = SetColorPalletRandomGreen();
				pInst++;
			}
		}

		// ���W�f�[�^���A�����b�N����
		pInstBuff->Unlock();
	}


	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// VTX
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// ���[���h�ʒu
		{ 1, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// ���_�J���[
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);

	return S_OK;
}


//=============================================================================
// �`�揈��
//=============================================================================
void Plane::Update(void)
{
	if (bColor)
	{
		fColor += PLANE_COLOR_SPEED;
		if (fColor > PLANE_COLOR_MAX)
		{
			bColor = false;
		}
	}
	else
	{
		fColor -= PLANE_COLOR_SPEED;
		if (fColor < -PLANE_COLOR_MAX)
		{
			bColor = true;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Plane::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�E�v���W�F�N�V�����s����擾
	D3DXMATRIX mtxWorld, mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	//// ���e�X�g��L����
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, EFFECT_ALPHA);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

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
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | PLANE_MAX);
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

	// �K�v�ȍs������Z�b�g
	pEffect->SetMatrix("proj", &mtxProjection);
	pEffect->SetMatrix("view", &mtxView);
	pEffect->SetMatrix("world", &mtxWorld);

	// �J���[���Z�b�g
	pEffect->SetFloat("color", fColor);

	// ���ʂ��m�肳����
	pEffect->CommitChanges();

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	// �V�F�[�_�[�p�X���I��
	pEffect->EndPass();
	// �V�F�[�_�[���I��
	pEffect->End();

	// �C���X�^���X�錾��W���ɖ߂�
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

	// �Œ�@�\�ɖ߂�
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}