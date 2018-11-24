//=============================================================================
//
// �v���C���[���� [gray.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "gray.h"
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
Gray::Gray()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::GRAY, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Gray::~Gray()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Gray::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_GRAY; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GRAY_000, &GrayObj[i].pD3DTexture);
			}
			GrayObj[i].Pos = D3DXVECTOR3(TEXTURE_GRAY_POSITION000_X, TEXTURE_GRAY_POSITION000_Y, 0.0f);
			GrayObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GRAY_SIZE000_X, TEXTURE_GRAY_SIZE000_Y);
			GrayObj[i].Count = 0;
			GrayObj[i].Alfa = 255;
			GrayObj[i].Use = false;
			GrayObj[i].Nowselect = true;
			GrayObj[i].Texture = GrayObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GRAY_000, &GrayObj[i].pD3DTexture);
			}
			GrayObj[i].Pos = D3DXVECTOR3(TEXTURE_GRAY_POSITION001_X, TEXTURE_GRAY_POSITION001_Y, 0.0f);
			GrayObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GRAY_SIZE001_X, TEXTURE_GRAY_SIZE001_Y);
			GrayObj[i].Count = 0;
			GrayObj[i].Alfa = 255;
			GrayObj[i].Use = false;
			GrayObj[i].Nowselect = true;
			GrayObj[i].Texture = GrayObj[i].pD3DTexture;
		}
		if (i == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GRAY_000, &GrayObj[i].pD3DTexture);
			}
			GrayObj[i].Pos = D3DXVECTOR3(TEXTURE_GRAY_POSITION002_X, TEXTURE_GRAY_POSITION002_Y, 0.0f);
			GrayObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GRAY_SIZE002_X, TEXTURE_GRAY_SIZE002_Y);
			GrayObj[i].Count = 0;
			GrayObj[i].Alfa = 255;
			GrayObj[i].Use = false;
			GrayObj[i].Nowselect = true;
			GrayObj[i].Texture = GrayObj[i].pD3DTexture;
		}

		GrayObj[i].Scale = D3DXVECTOR2(TEXTURE_GRAY_SCALE_X, TEXTURE_GRAY_SCALE_Y);
		GrayObj[i].Angle = TEXTURE_GRAY_ANGLE_X;
		MakeVertexGray(i);
	}
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void Gray::Uninit(void)
{
	for (int i = 0; i < NUM_GRAY; i++)
	{
		if (GrayObj[i].pD3DTexture != NULL)	// (*31)
		{	// �e�N�X�`���̊J��
			GrayObj[i].pD3DTexture->Release();
			GrayObj[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Gray::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("GrayObj[0].Alfa:%d\n", GrayObj[0].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("GrayObj[1].Alfa:%d\n", GrayObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_GRAY; i++)
	{
		if (GetKeyboardTrigger(DIK_U))
		{
			GrayObj[0].Use = true;
			GrayObj[1].Use = false;
			GrayObj[2].Use = false;
		}
		if (GetKeyboardTrigger(DIK_Y))
		{
			GrayObj[1].Use = true;
			GrayObj[1].Pos = D3DXVECTOR3(TEXTURE_GRAY_POSITION001_X, TEXTURE_GRAY_POSITION001_Y, 0.0f);
			GrayObj[2].Use = false;
		}
		if (GetKeyboardTrigger(DIK_T))
		{
			GrayObj[1].Use = false;
			GrayObj[2].Use = true;
			GrayObj[2].Pos = D3DXVECTOR3(TEXTURE_GRAY_POSITION002_X, TEXTURE_GRAY_POSITION002_Y, 0.0f);
		}
		//	���_�J���[�̐ݒ�
		SetVertexGray(i);
		// �e�N�X�`�����W��ݒ�
		SetTextureGray(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Gray::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_GRAY; i++)
	{
		if (GrayObj[i].Use == true)
		{
			pDevice->SetTexture(0, GrayObj[i].pD3DTexture);


			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, GrayObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set�֐�
//=============================================================================
void Gray::SetVertexGray(int CreateCount)
{
	if (CreateCount < NUM_GRAY)
	{
		GrayObj[CreateCount].vertexWk[0].vtx.x = GrayObj[CreateCount].Pos.x - GrayObj[CreateCount].TextureSize.x;
		GrayObj[CreateCount].vertexWk[0].vtx.y = GrayObj[CreateCount].Pos.y - GrayObj[CreateCount].TextureSize.y;
		GrayObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		GrayObj[CreateCount].vertexWk[1].vtx.x = GrayObj[CreateCount].Pos.x + GrayObj[CreateCount].TextureSize.x;
		GrayObj[CreateCount].vertexWk[1].vtx.y = GrayObj[CreateCount].Pos.y - GrayObj[CreateCount].TextureSize.y;
		GrayObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		GrayObj[CreateCount].vertexWk[2].vtx.x = GrayObj[CreateCount].Pos.x - GrayObj[CreateCount].TextureSize.x;
		GrayObj[CreateCount].vertexWk[2].vtx.y = GrayObj[CreateCount].Pos.y + GrayObj[CreateCount].TextureSize.y;
		GrayObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		GrayObj[CreateCount].vertexWk[3].vtx.x = GrayObj[CreateCount].Pos.x + GrayObj[CreateCount].TextureSize.x;
		GrayObj[CreateCount].vertexWk[3].vtx.y = GrayObj[CreateCount].Pos.y + GrayObj[CreateCount].TextureSize.y;
		GrayObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ� (*34)
//=============================================================================
void Gray::SetTextureGray(int i)
{

	GrayObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Gray::MakeVertexGray(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	SetVertexGray(i);


	// rhw�̐ݒ�
	GrayObj[i].vertexWk[0].rhw = 1.0f;
	GrayObj[i].vertexWk[1].rhw = 1.0f;
	GrayObj[i].vertexWk[2].rhw = 1.0f;
	GrayObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureGray(i);

	GrayObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	GrayObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	GrayObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	GrayObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}