//=============================================================================
//
// �v���C���[���� [ko.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "ko.h"
#include "character.h"
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
Ko::Ko()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::KO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Ko::~Ko()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Ko::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_KO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_KO_000, &KoObj[i].pD3DTexture);
			}
			KoObj[i].Pos = D3DXVECTOR3(TEXTURE_KO_POSITION000_X, TEXTURE_KO_POSITION000_Y, 0.0f);
			KoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_KO_SIZE000_X, TEXTURE_KO_SIZE000_Y);
			KoObj[i].Count = 0;
			KoObj[i].Alfa = 255;
			KoObj[i].Color = 255;
			KoObj[i].Use = false;
			KoObj[i].Nowselect = false;
			KoObj[i].Texture = KoObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			KoObj[i].Pos = D3DXVECTOR3(TEXTURE_KO_POSITION001_X, TEXTURE_KO_POSITION001_Y, 0.0f);
			KoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_KO_SIZE001_X, TEXTURE_KO_SIZE001_Y);
			KoObj[i].Count = 0;
			KoObj[i].Alfa = 255;
			KoObj[i].Color = 255;
			KoObj[i].Use = false;
			KoObj[i].Nowselect = false;
			KoObj[i].Texture = KoObj[0].pD3DTexture;
		}
		KoObj[i].Scale = D3DXVECTOR2(TEXTURE_KO_SCALE_X, TEXTURE_KO_SCALE_Y);
		KoObj[i].Angle = TEXTURE_KO_ANGLE_X;
		MakeVertexKo(i);
	}
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void Ko::Uninit(void)
{
	for (int i = 0; i < NUM_KO; i++)
	{
		if (i == 0 || i == 1)
		{
			if (KoObj[0].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				KoObj[0].pD3DTexture->Release();
				KoObj[0].pD3DTexture = NULL;
			}
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void Ko::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("KoObj[2].Alfa:%d\n", KoObj[2].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("KoObj[1].Alfa:%d\n", KoObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_KO; i++)
	{
		if (GetKeyboardTrigger(DIK_T))
		{
			KoObj[0].Use = true;
			KoObj[0].Nowselect = true;
			KoObj[0].Color = 255;
			KoObj[1].Use = true;
			KoObj[1].Nowselect = true;
			KoObj[1].Color = 0;
		}
		if (GetKeyboardTrigger(DIK_Y))
		{
			KoObj[0].Use = true;
			KoObj[0].Nowselect = true;
			KoObj[0].Color = 0;
			KoObj[1].Use = true;
			KoObj[1].Nowselect = true;
			KoObj[1].Color = 255;
		}
		//	���_�J���[�̐ݒ�
		SetVertexKo(i);
		// �e�N�X�`�����W��ݒ�
		SetTextureKo(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Ko::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_KO; i++)
	{
		if (KoObj[i].Use == true)
		{
			if (i == 0 || i == 1)
			{
				pDevice->SetTexture(0, KoObj[0].pD3DTexture);
			}

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, KoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set�֐�
//=============================================================================
void Ko::SetVertexKo(int CreateCount)
{
	if (CreateCount < NUM_KO)
	{
		KoObj[CreateCount].vertexWk[0].vtx.x = KoObj[CreateCount].Pos.x - KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[0].vtx.y = KoObj[CreateCount].Pos.y - KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[1].vtx.x = KoObj[CreateCount].Pos.x + KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[1].vtx.y = KoObj[CreateCount].Pos.y - KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[2].vtx.x = KoObj[CreateCount].Pos.x - KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[2].vtx.y = KoObj[CreateCount].Pos.y + KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[3].vtx.x = KoObj[CreateCount].Pos.x + KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[3].vtx.y = KoObj[CreateCount].Pos.y + KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ� (*34)
//=============================================================================
void Ko::SetTextureKo(int i)
{

	KoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);

}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Ko::MakeVertexKo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	SetVertexKo(i);


	// rhw�̐ݒ�
	KoObj[i].vertexWk[0].rhw = 1.0f;
	KoObj[i].vertexWk[1].rhw = 1.0f;
	KoObj[i].vertexWk[2].rhw = 1.0f;
	KoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureKo(i);

	KoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	KoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	KoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	KoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}