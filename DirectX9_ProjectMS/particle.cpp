//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "main.h"
#include "particle.h"
#include "input.h"
#include "calculate.h"
#include "camera.h"

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
ParticleManager::ParticleManager()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::PARTICLE, Priority::Middle, Priority::Middle);

	// �p�[�e�B�N���̏�����
	pParticle = NULL;

	// ����������
	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
ParticleManager::~ParticleManager()
{
	// �������
	Release();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT ParticleManager::Init(void)
{
	pParticle = new Particle;
	return S_OK;
}

//=============================================================================
// �������
//=============================================================================
void ParticleManager::Release(void)
{
	// �������
	SAFE_DELETE(pParticle);
}

//=============================================================================
// �X�V����
//=============================================================================
void ParticleManager::Update(void)
{
	SAFE_UPDATE(pParticle);
}

//=============================================================================
// �`�揈��
//=============================================================================
void ParticleManager::Draw(void)
{
	SAFE_DRAW(pParticle);
}



//=============================================================================
// �R���X�g���N�^
//=============================================================================
Particle::Particle()
{
	// �e�|�C���^�̏�����
	pTexture = NULL;	// �e�N�X�`��
	pVtxBuff = NULL;	// ���_�o�b�t�@
	pInstBuff = NULL;	// �C���X�^���V���O�o�b�t�@
	pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@
	pDecl = NULL;		// ���_�錾

	// �V�F�[�_�֘A�̏�����
	pErrorBuff = NULL;	// �V�F�[�_�p�R���p�C���G���[
	pEffect = NULL;		// �V�F�[�_
	numPass = 0;

	// �J�E���^�̏�����
	nCount = 0;

	// �J���[�w��̏�����
	nColor = 0;

	// �ړ��ʂ̏�����
	fMove = 0.0f;

	// ����������
	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Particle::~Particle()
{
	// �������
	Release();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Particle::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* path = PARTICLE_SHADER_FILE;
	// �t�@�C��( const char* path )����V�F�[�_�[�t�@�C����ǂݍ��ݓǂݍ���
	if (FAILED(D3DXCreateEffectFromFile(
		pDevice, path, 0, 0, 0, 0, &pEffect, &pErrorBuff)))
	{
		// �G���[
		MessageBox(NULL, "�V�F�[�_�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", path, MB_OK);
		return S_FALSE;
	}

	// �g�p����e�N�j�b�N���`
	if (FAILED(pEffect->SetTechnique("Tec01")))
	{
		// �G���[
		MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "Tec01", MB_OK);
		return S_FALSE;
	}

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		PARTICLE_TEXTURE,
		&pTexture)))
	{
		// �G���[
		MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", PARTICLE_TEXTURE, MB_OK);
		return S_FALSE;
	}

	// ���_���̍쐬�i���[�J�����W�̐ݒ�j
	MakeVertex(pDevice);
	return S_OK;
}

//=============================================================================
// �������
//=============================================================================
void Particle::Release(void)
{
	// �������
	SAFE_RELEASE(pTexture);		// �e�N�X�`��
	SAFE_RELEASE(pVtxBuff);		// ���_�o�b�t�@
	SAFE_RELEASE(pInstBuff);	// �C���X�^���V���O�o�b�t�@
	SAFE_RELEASE(pIdxBuff);		// �C���f�b�N�X�o�b�t�@
	SAFE_RELEASE(pDecl);		// ���_�錾
	SAFE_RELEASE(pErrorBuff);	// �V�F�[�_�p�R���p�C���G���[
	SAFE_RELEASE(pEffect);		// �V�F�[�_
}

//=============================================================================
// �X�V����
//=============================================================================
void Particle::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("�y PARTICLE �z\n");
#endif
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ړ��ʂ����Z
	fMove += PARTICLE_MOVE_SPEED;

	// �}�E�X�z�C�[���Ńp�[�e�B�N���J���[��ύX
	long ModUseZ = GetMobUseZ();
	if (ModUseZ != 0)
	{
		if (ModUseZ > 0)
		{
			nColor++;
			if (nColor >= COLOR_PALLET_MAX)
			{
				nColor = 0;
			}
		}
		else
		{
			nColor--;
			if (nColor < 0)
			{
				nColor = COLOR_PALLET_MAX - 1;
			}
		}
	}

	// ���N���b�N�ŃG�t�F�N�g�ݒu
	if (IsMobUseLeftPressed())
	{
		Set(PARTICLE_SET,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			SetColorPallet(nColor));
	}

#ifdef _DEBUG
	PrintDebugProc("ParticleMax:%d\n", nCount);
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void Particle::Draw(void)
{
	if (nCount >= 0)
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

		// ���Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//////pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

		//// ���C���e�B���O�𖳌��ɂ���
		//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �r���[�s��̋t�s����i�[�i�r���{�[�h���j
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;

		// �C���X�^���X�錾
		pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | nCount);
		pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		// ���_�ƃC���f�b�N�X��ݒ�
		pDevice->SetVertexDeclaration(pDecl);
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_PLANE));		// ���_�o�b�t�@
		pDevice->SetStreamSource(1, pInstBuff, 0, sizeof(INSTANCE_PLANE));	// �C���X�^���X�o�b�t�@
		pDevice->SetIndices(pIdxBuff);										// �C���f�b�N�X�o�b�t�@

		// �e�N�j�b�N��ݒ�
		pEffect->SetTechnique("Tec01");

		// �V�F�[�_�[�̊J�n�ApassNum�ɂ͎w�肵�Ă���e�N�j�b�N�ɒ�`���Ă���pass�̐����ς���
		pEffect->Begin(&numPass, 0);

		// �p�X���w�肵�ĊJ�n
		pEffect->BeginPass(0);

		// �e�N�X�`�����Z�b�g
		pEffect->SetTexture("tex", pTexture);

		// �K�v�ȍs������Z�b�g
		pEffect->SetMatrix("proj", &mtxProjection);
		pEffect->SetMatrix("view", &mtxView);
		pEffect->SetMatrix("world", &mtxWorld);

		// �ړ��ʂ��Z�b�g
		pEffect->SetFloat("moveTime", fMove);

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

		// �ʏ�u�����h�ɖ߂�
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//// ���e�X�g�𖳌���
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//// ���C���e�B���O��L���ɂ���
		//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Particle::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
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
		pVtx[0].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[1].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[2].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[3].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		int x = 0 % PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		int y = 0 / PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / PARTICLE_TEXTURE_PATTERN_DIVIDE_Y;

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
		sizeof(INSTANCE_PLANE) * PARTICLE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
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
		for (unsigned int i = 0; i < PARTICLE_MAX; i++, pInst++)
		{
			pInst->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pInst->diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pInst->vec = RandVector();
			pInst->move = 0.0f;
		}

		// ���W�f�[�^���A�����b�N����
		pInstBuff->Unlock();
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

	pDevice->CreateVertexDeclaration(declElems, &pDecl);

	return S_OK;
}

//=============================================================================
// �ݒu����
//=============================================================================
void Particle::Set(int value, D3DXVECTOR3 pos, D3DXCOLOR color)
{
	if (nCount + value > PARTICLE_MAX)
	{
		value = PARTICLE_MAX - nCount;
	}

	{// ���W�o�b�t�@�̒��g�𖄂߂�
		INSTANCE_PLANE *pInst;

		// ���W�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pInstBuff->Lock(0, 0, (void**)&pInst, 0);

		pInst += nCount;

		for (unsigned int i = 0; i < value; i++, pInst++)
		{
			// ���W�̐ݒ�
			pInst->pos = pos;
			//pInst->diffuse = color;
			pInst->diffuse = SetColorPalletRandom();
			//pInst->vec = RandVector();
			pInst->move = fMove;
		}
		// ���W�f�[�^���A�����b�N����
		pInstBuff->Unlock();

		nCount += value;
	}
}