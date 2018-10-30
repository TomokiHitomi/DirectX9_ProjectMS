//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "camera.h"
#include "particle.h"
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
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void InitStatusEffect(LPDIRECT3DDEVICE9 pDevice, int nEffect);
void SetInstEffect(int nWk, D3DXVECTOR3 pos, D3DXCOLOR color);
//void SetVtxEffect(int nWk, float fSizeX, float fSizeY);
//void SetDiffuseEffect(int nWk, D3DXCOLOR col);
//void SetTexEffect(int nWk, int nTex);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9				g_pD3DTextureEffect = NULL;	// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9			g_pD3DVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pD3DInstBuffEffect = NULL;// �C���X�^���V���O�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9			g_pD3DIdxBuffEffect = NULL;

LPDIRECT3DVERTEXDECLARATION9	g_pD3DDeclEffect = NULL;

EFFECT					effectWk[PARTICLE_MAX];
//VERTEX_PLANE			vtxPlane[NUM_VERTEX];

D3DXMATRIX				g_mtxWorldEffect;

// �V�F�[�_�[�֘A
LPD3DXBUFFER errorEffect = NULL;
LPD3DXEFFECT effectshader = NULL;
UINT numPassEffect;
HRESULT hrEffect;

int g_nEffectColor = 0;
int g_nEffectCount = 0;
float g_fEffectMove = 0.0f;

//=============================================================================
// �R���X�g���N�^�i�������j
//=============================================================================
Particle::Particle()
{

}


//=============================================================================
// �f�X�g���N�^�i�I���j
//=============================================================================
Particle::~Particle()
{

}


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(int nType)
{
	EFFECT *effect = &effectWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* path = PARTICLE_SHADER_FILE;
	// �t�@�C��( const char* path )����V�F�[�_�[�t�@�C����ǂݍ��ݓǂݍ���
	hrEffect = D3DXCreateEffectFromFile(pDevice, path, 0, 0, 0, 0, &effectshader, &errorEffect);
	if (FAILED(hrEffect))
	{
		// �G���[
		return S_FALSE;
	}
	// �g�p����e�N�j�b�N���`
	hrEffect = effectshader->SetTechnique("Tec01");
	if (FAILED(hrEffect)) {

		// �G���[
		return S_FALSE;
	}


	if (nType == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			PARTICLE_TEXTURE,
			&g_pD3DTextureEffect);
	}

	for (int i = 0; i < PARTICLE_MAX; i++, effect++)
	{
		// �ʒu�E��]�E�X�P�[���̐ݒ�
		effect->posEffect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->rotEffect = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect->sclEffect = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		InitStatusEffect(pDevice, i);

	}

	// ���_���̍쐬�i���[�J�����W�̐ݒ�j
	MakeVertexEffect(pDevice);
	return S_OK;
}

//=============================================================================
// �ė��p����
//=============================================================================
void InitStatusEffect(LPDIRECT3DDEVICE9 pDevice, int nEffect)
{
	EFFECT *effect = &effectWk[nEffect];

	effect->bUse = false;
	effect->vec2Size = D3DXVECTOR2(PARTICLE_SIZE_X, PARTICLE_SIZE_Y);
	effect->colorEffect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	effect->nTex = 0;
	effect->fSizeChange = 0.0f;
	effect->fAlphaChange = 0.0f;
	effect->fSize = 1.0f;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	// �V�F�[�_�[�����
	effectshader->Release();

	if (g_pD3DTextureEffect != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEffect->Release();
		g_pD3DTextureEffect = NULL;
	}

	if (g_pD3DVtxBuffEffect != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEffect->Release();
		g_pD3DVtxBuffEffect = NULL;
	}

	if (g_pD3DInstBuffEffect != NULL)
	{// �C���X�^���V���O�o�b�t�@�̊J��
		g_pD3DInstBuffEffect->Release();
		g_pD3DInstBuffEffect = NULL;
	}

	if (g_pD3DIdxBuffEffect != NULL)
	{// �C���f�b�N�X�o�b�t�@�̊J��
		g_pD3DIdxBuffEffect->Release();
		g_pD3DIdxBuffEffect = NULL;
	}

	if (g_pD3DDeclEffect != NULL)
	{// ���_�錾�̊J��
		g_pD3DDeclEffect->Release();
		g_pD3DDeclEffect = NULL;
	}

	if (errorEffect != NULL)
	{// �V�F�[�_�f�[�^�o�b�t�@�̊J��
		errorEffect->Release();
		errorEffect = NULL;
	}

	if (effectshader != NULL)
	{// �V�F�[�_�̊J��
		effectshader->Release();
		effectshader = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
#ifdef _DEBUG
	PrintDebugProc("�y EFFECT �z\n");
	int nEffectCount = 0;
	DWORD  start = GetTickCount();
	static double s_dClockTime;
#endif
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT *effect = &effectWk[0];

	g_fEffectMove += PARTICLE_MOVE_SPEED;

	long ModUseZ = GetMobUseZ();
	if (ModUseZ != 0)
	{
		if (ModUseZ > 0)
		{
			g_nEffectColor++;
			if (g_nEffectColor >= COLOR_PALLET_MAX)
			{
				g_nEffectColor = 0;
			}
		}
		else
		{
			g_nEffectColor--;
			if (g_nEffectColor < 0)
			{
				g_nEffectColor = COLOR_PALLET_MAX - 1;
			}
		}
	}	



	// �G�t�F�N�g�ݒu
	if (IsMobUseLeftPressed())
	{
		for (unsigned int i = 0; i < PARTICLE_SET; i++)
		{
			SetEffect(0,
				D3DXVECTOR2(10, 10), SetColorPallet(g_nEffectColor),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				0.0001f, 0.0001f);
		}
	}

	for (int i = 0; i < PARTICLE_MAX; i++, effect++)
	{
		if (effect->bUse)
		{
#ifdef _DEBUG
			// �g�p�G�t�F�N�g�����J�E���g
			nEffectCount++;
#endif
			//effect->fSize += 0.5f;
			//if (effect->fSize > 100.0f)
			//{
			//	InitStatusEffect(pDevice, i);
			//}
			//effect->vec2Size.x -= effect->fSizeChange;
			//effect->vec2Size.y -= effect->fSizeChange;
			//effect->colorEffect.a -= effect->fAlphaChange;

			//SetVtxEffect(i, effect->vec2Size.x, effect->vec2Size.y);
			//SetDiffuseEffect(i, effect->colorEffect);
			//SetTexEffect(i, effect->nTex);

			//if (effect->vec2Size.x < 0 || effect->colorEffect.a < 0)
			//{
			//	InitStatusEffect(pDevice, i);
			//}
		}
	}

#ifdef _DEBUG
	PrintDebugProc("EffectMax:%d\n", nEffectCount);
	DWORD end = GetTickCount();
	double dClockTemp = (double)(end - start) / 1000;

	if (dClockTemp > s_dClockTime)
	{
		s_dClockTime = dClockTemp;
	}
	PrintDebugProc("clockTime[%f]\n", s_dClockTime);
	PrintDebugProc("\n");

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
#ifdef _DEBUG
	PrintDebugProc("�y EFFECT DRAW �z\n");
	DWORD  start = GetTickCount();
	static double s_dClockTime;
#endif
	if (g_nEffectCount > 0)
	{

		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[��, ��], ���s�ړ�

		EFFECT *effect = &effectWk[0];
		D3DXMATRIX mtxView, mtxProjection;
			
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

		//// ���e�X�g��L����
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		//pDevice->SetRenderState(D3DRS_ALPHAREF, EFFECT_ALPHA);
		//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// ���Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//////pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

		//// ���C���e�B���O�𖳌��ɂ���
		//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldEffect);

		// �r���{�[�h��
		g_mtxWorldEffect._11 = mtxView._11;
		g_mtxWorldEffect._12 = mtxView._21;
		g_mtxWorldEffect._13 = mtxView._31;
		g_mtxWorldEffect._21 = mtxView._12;
		g_mtxWorldEffect._22 = mtxView._22;
		g_mtxWorldEffect._23 = mtxView._32;
		g_mtxWorldEffect._31 = mtxView._13;
		g_mtxWorldEffect._32 = mtxView._23;
		g_mtxWorldEffect._33 = mtxView._33;

		// �C���X�^���X�錾
		pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | g_nEffectCount);
		pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		// ���_�ƃC���f�b�N�X��ݒ�
		pDevice->SetVertexDeclaration(g_pD3DDeclEffect);
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEffect, 0, sizeof(VERTEX_PLANE));	// ���_�o�b�t�@
		pDevice->SetStreamSource(1, g_pD3DInstBuffEffect, 0, sizeof(INSTANCING_PLANE));	// ���W�o�b�t�@
		pDevice->SetIndices(g_pD3DIdxBuffEffect);									// �C���f�b�N�X�o�b�t�@

		// �e�N�j�b�N��ݒ�
		effectshader->SetTechnique("Tec01");

		// �V�F�[�_�[�̊J�n�ApassNum�ɂ͎w�肵�Ă���e�N�j�b�N�ɒ�`���Ă���pass�̐����ς���
		UINT passNum = 0;
		effectshader->Begin(&passNum, 0);

		// �p�X���w�肵�ĊJ�n
		effectshader->BeginPass(0);

		// �e�N�X�`�����Z�b�g
		effectshader->SetTexture("tex", g_pD3DTextureEffect);

		// �K�v�ȍs������Z�b�g
		effectshader->SetMatrix("proj", &mtxProjection);
		effectshader->SetMatrix("view", &mtxView);
		effectshader->SetMatrix("world", &g_mtxWorldEffect);

		// ���ԃJ�E���^�[���Z�b�g
		effectshader->SetFloat("moveTime", g_fEffectMove);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

		// �V�F�[�_�[�p�X�̏I��
		effectshader->EndPass();
		// �V�F�[�_�[�I��
		effectshader->End();

		// �C���X�^���X�錾��W���ɖ߂�
		pDevice->SetStreamSourceFreq(0, 1);
		pDevice->SetStreamSourceFreq(1, 1);

		// �ʏ�u�����h�ɖ߂�
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		////// ���e�X�g�𖳌���
		////pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


		//// ���C���e�B���O��L���ɂ���
		//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
#ifdef _DEBUG
	DWORD end = GetTickCount();
	double dClockTemp = (double)(end - start) / 1000;
	
	if (dClockTemp > s_dClockTime)
	{
		s_dClockTime = dClockTemp;
	}
	PrintDebugProc("clockTime[%f]\n", s_dClockTime);
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	/***** ���_�o�b�t�@�ݒ� *****/

	// ���_�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PLANE) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		0,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffEffect,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_PLANE *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[1].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[2].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[3].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		int x = 0 % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		int y = 0 / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
		float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;

		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffect->Unlock();
	}


	/***** �C���X�^���V���O�p�̍��W�o�b�t�@�ݒ� *****/

	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(INSTANCING_PLANE) * PARTICLE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		0,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DInstBuffEffect,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{// �C���X�^���V���O�o�b�t�@�̒��g�𖄂߂�
		INSTANCING_PLANE *pInst;
		

		// ���W�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DInstBuffEffect->Lock(0, 0, (void**)&pInst, 0);

		// ���W�̐ݒ�
		for (unsigned int i = 0; i < PARTICLE_MAX; i++, pInst++)
		{
			pInst->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pInst->diffuse = SetColorPallet(COLOR_PALLET_WHITE);
			pInst->vec = RandVector();
			pInst->move = 0.0f;
		}

		// ���W�f�[�^���A�����b�N����
		g_pD3DInstBuffEffect->Unlock();
	}

	/***** �C���f�b�N�X�o�b�t�@�ݒ� *****/

	WORD wIndex[6] = { 0, 1, 2, 2, 1, 3 };

	// ���W�o�b�t�@����
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(wIndex),						// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,									// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DIdxBuffEffect,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{// ���W�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DIdxBuffEffect->Lock(0, 0, (void**)&pIdx, 0);

		// ���_���W�̐ݒ�
		for (unsigned int i = 0; i < 6; i++, pIdx++)
		{
			*pIdx = wIndex[i];
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DIdxBuffEffect->Unlock();
	}

	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// VTX
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// ���[���h�ʒu
		{ 1, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// ���_�J���[
		{ 1, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		// �ړ��x�N�g��
		{ 1, 28, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	// �J�E���^�[
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &g_pD3DDeclEffect);

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetInstEffect(int nWk, D3DXVECTOR3 pos, D3DXCOLOR color)
{
	{// ���W�o�b�t�@�̒��g�𖄂߂�
		INSTANCING_PLANE *pInst;

		// ���W�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DInstBuffEffect->Lock(0, 0, (void**)&pInst, 0);

		pInst += nWk;

		// ���W�̐ݒ�
		pInst->pos = pos;
		pInst->diffuse = color;
		//pInst->diffuse = SetColorPalletRandom();
		//pInst->vec = RandVector();
		pInst->move = g_fEffectMove;

		// ���W�f�[�^���A�����b�N����
		g_pD3DInstBuffEffect->Unlock();
	}
}

////=============================================================================
//// ���_���W�̐ݒ�֐�
////=============================================================================
//void SetVtxEffect(int nWk, float fSizeX, float fSizeY)
//{
//	{// ���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_NOLIGHT *pVtx;
//
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//		pVtx += (nWk * 4);
//
//		// ���_���W�̐ݒ�
//		pVtx[0].vtx = D3DXVECTOR3(-fSizeX, -fSizeY, 0.0f);
//		pVtx[1].vtx = D3DXVECTOR3(-fSizeX, fSizeY, 0.0f);
//		pVtx[2].vtx = D3DXVECTOR3(fSizeX, -fSizeY, 0.0f);
//		pVtx[3].vtx = D3DXVECTOR3(fSizeX, fSizeY, 0.0f);
//
//		// ���_�f�[�^���A�����b�N����
//		g_pD3DVtxBuffEffect->Unlock();
//	}
//}
//
////=============================================================================
//// ���ˌ��̐ݒ�֐�
////=============================================================================
//void SetDiffuseEffect(int nWk, D3DXCOLOR col)
//{
//	{// ���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_NOLIGHT *pVtx;
//
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//		pVtx += (nWk * 4);
//
//		// ���_���W�̐ݒ�
//		pVtx[0].diffuse =
//			pVtx[1].diffuse =
//			pVtx[2].diffuse =
//			pVtx[3].diffuse = col;
//
//		// ���_�f�[�^���A�����b�N����
//		g_pD3DVtxBuffEffect->Unlock();
//	}
//}
//
////=============================================================================
//// �e�N�X�`�����W�̐ݒ�֐�
////=============================================================================
//void SetTexEffect(int nWk, int nTex)
//{
//	{// ���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_NOLIGHT *pVtx;
//
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		g_pD3DVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
//
//		pVtx += (nWk * 4);
//
//		// �e�N�X�`�����W�̐ݒ�
//		int x = nTex % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//		int y = nTex / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//		float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//		float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;
//		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//
//		// ���_�f�[�^���A�����b�N����
//		g_pD3DVtxBuffEffect->Unlock();
//	}
//}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
//void SetTextureEffect(int no, int cntPattern)
//{
//	EFFECT *effect = &effectWk[no];
//
//	// �e�N�X�`�����W�̐ݒ�
//	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT;
//	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT;
//	effect->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
//	effect->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
//	effect->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
//	effect->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
//}

//=============================================================================
// �Ώۂɐݒu
//=============================================================================
void SetEffect(int nTex, D3DXVECTOR2 vec2Size, D3DXCOLOR color, D3DXVECTOR3 vecPos, float fSizeChange, float fAlphaChange)
{
	EFFECT *effect = &effectWk[0];

	// ���g�p��T��
	for (int i = 0; i < PARTICLE_MAX; i++, effect++)
	{
		if (!effect->bUse)
		{
			effect->bUse = true;
			//effect->posEffect = vecPos;
			//effect->colorEffect = color;
			//effect->colorEffect.a = 1.0f;
			//effect->vec2Size = vec2Size;
			//effect->fSizeChange = fSizeChange;
			//effect->fAlphaChange = fAlphaChange;
			//effect->nTex = nTex;
			g_nEffectCount++;

			SetInstEffect(i, vecPos, color);

			//SetVtxEffect(i, effect->vec2Size.x, effect->vec2Size.y);
			//SetDiffuseEffect(i, effect->colorEffect);
			//SetTexEffect(i, effect->nTex);
			return;
		}
	}
}