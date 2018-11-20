//=============================================================================
//
// �v���C���[���� [rightleft.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "rightleft.h"
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
Rightleft::Rightleft()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::RIGHTLEFT, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Rightleft::~Rightleft()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Rightleft::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_RIGHTLEFT; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RIGHTLEFT_000, &RightleftObj[i].pD3DTexture);
			}
			RightleftObj[i].Pos = D3DXVECTOR3(TEXTURE_RIGHTLEFT_POSITION000_X, TEXTURE_RIGHTLEFT_POSITION000_Y, 0.0f);
			RightleftObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RIGHTLEFT_SIZE000_X, TEXTURE_RIGHTLEFT_SIZE000_Y);
			RightleftObj[i].Count = 0;
			RightleftObj[i].Alfa = 255;
			RightleftObj[i].Color = 255;
			RightleftObj[i].Use = true;
			RightleftObj[i].Nowselect = false;
			RightleftObj[i].Texture = RightleftObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RIGHTLEFT_001, &RightleftObj[i].pD3DTexture);
			}
			RightleftObj[i].Pos = D3DXVECTOR3(TEXTURE_RIGHTLEFT_POSITION001_X, TEXTURE_RIGHTLEFT_POSITION001_Y, 0.0f);
			RightleftObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RIGHTLEFT_SIZE001_X, TEXTURE_RIGHTLEFT_SIZE001_Y);
			RightleftObj[i].Count = 0;
			RightleftObj[i].Alfa = 255;
			RightleftObj[i].Color = 255;
			RightleftObj[i].Use = true;
			RightleftObj[i].Nowselect = false;
			RightleftObj[i].Texture = RightleftObj[i].pD3DTexture;
		}
		if (i == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RIGHTLEFT_000, &RightleftObj[i].pD3DTexture);
			}
			RightleftObj[i].Pos = D3DXVECTOR3(TEXTURE_RIGHTLEFT_POSITION002_X, TEXTURE_RIGHTLEFT_POSITION002_Y, 0.0f);
			RightleftObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RIGHTLEFT_SIZE002_X, TEXTURE_RIGHTLEFT_SIZE002_Y);
			RightleftObj[i].Count = 0;
			RightleftObj[i].Alfa = 255;
			RightleftObj[i].Color = 255;
			RightleftObj[i].Use = true;
			RightleftObj[i].Nowselect = false;
			RightleftObj[i].Texture = RightleftObj[i].pD3DTexture;
		}
		if (i == 3)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RIGHTLEFT_001, &RightleftObj[i].pD3DTexture);
			}
			RightleftObj[i].Pos = D3DXVECTOR3(TEXTURE_RIGHTLEFT_POSITION003_X, TEXTURE_RIGHTLEFT_POSITION003_Y, 0.0f);
			RightleftObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RIGHTLEFT_SIZE003_X, TEXTURE_RIGHTLEFT_SIZE003_Y);
			RightleftObj[i].Count = 0;
			RightleftObj[i].Alfa = 255;
			RightleftObj[i].Color = 255;
			RightleftObj[i].Use = true;
			RightleftObj[i].Nowselect = false;
			RightleftObj[i].Texture = RightleftObj[i].pD3DTexture;
		}
		RightleftObj[i].Scale = D3DXVECTOR2(TEXTURE_RIGHTLEFT_SCALE_X, TEXTURE_RIGHTLEFT_SCALE_Y);
		RightleftObj[i].Angle = TEXTURE_RIGHTLEFT_ANGLE_X;
		MakeVertexRightleft(i);
	}
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void Rightleft::Uninit(void)
{
	for (int i = 0; i < NUM_RIGHTLEFT; i++)
	{
		if (RightleftObj[i].pD3DTexture != NULL)	// (*31)
		{	// �e�N�X�`���̊J��
			RightleftObj[i].pD3DTexture->Release();
			RightleftObj[i].pD3DTexture = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void Rightleft::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("RightleftObj[2].Alfa:%d\n", RightleftObj[2].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("RightleftObj[1].Alfa:%d\n", RightleftObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_RIGHTLEFT; i++)
	{
		if (GetKeyboardTrigger(DIK_Z)&& RightleftObj[0].Nowselect == false)
		{
			RightleftObj[0].Nowselect = true;
			RightleftObj[0].Color=0;
		}
		if(RightleftObj[0].Nowselect == true)
		{
			RightleftObj[0].Count++;
			RightleftObj[0].Color += TEXTURE_RIGHTLEFT_SCOND_COLOR;
			if (RightleftObj[0].Count == FRAME * TEXTURE_RIGHTLEFT_SCOND)
			{
				RightleftObj[0].Count = 0;
				RightleftObj[0].Color = 255;
				RightleftObj[0].Nowselect = false;
			}
		}
		if (GetKeyboardTrigger(DIK_X) && RightleftObj[1].Nowselect == false)
		{
			RightleftObj[1].Nowselect = true;
			RightleftObj[1].Color = 0;
		}
		if (RightleftObj[1].Nowselect == true)
		{
			RightleftObj[1].Count++;
			RightleftObj[1].Color += TEXTURE_RIGHTLEFT_SCOND_COLOR;
			if (RightleftObj[1].Count == FRAME * TEXTURE_RIGHTLEFT_SCOND)
			{
				RightleftObj[1].Count = 0;
				RightleftObj[1].Color = 255;
				RightleftObj[1].Nowselect = false;
			}
		}
		if (GetKeyboardTrigger(DIK_C) && RightleftObj[2].Nowselect == false)
		{
			RightleftObj[2].Nowselect = true;
			RightleftObj[2].Color = 0;
		}
		if (RightleftObj[2].Nowselect == true)
		{
			RightleftObj[2].Count++;
			RightleftObj[2].Color += TEXTURE_RIGHTLEFT_SCOND_COLOR;
			if (RightleftObj[2].Count == FRAME * TEXTURE_RIGHTLEFT_SCOND)
			{
				RightleftObj[2].Count = 0;
				RightleftObj[2].Color = 255;
				RightleftObj[2].Nowselect = false;
			}
		}
		if (GetKeyboardTrigger(DIK_V) && RightleftObj[3].Nowselect == false)
		{
			RightleftObj[3].Nowselect = true;
			RightleftObj[3].Color = 0;
		}
		if (RightleftObj[3].Nowselect == true)
		{
			RightleftObj[3].Count++;
			RightleftObj[3].Color += TEXTURE_RIGHTLEFT_SCOND_COLOR;
			if (RightleftObj[3].Count == FRAME * TEXTURE_RIGHTLEFT_SCOND)
			{
				RightleftObj[3].Count = 0;
				RightleftObj[3].Color = 255;
				RightleftObj[3].Nowselect = false;
			}
		}
		//	���_�J���[�̐ݒ�
		SetVertexRightleft(i);
		// �e�N�X�`�����W��ݒ�
		SetTextureRightleft(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Rightleft::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_RIGHTLEFT; i++)
	{
		if (RightleftObj[i].Use == true)
		{
			pDevice->SetTexture(0, RightleftObj[i].pD3DTexture);


			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, RightleftObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set�֐�
//=============================================================================
void Rightleft::SetVertexRightleft(int CreateCount)
{
	if (CreateCount < NUM_RIGHTLEFT)
	{
		RightleftObj[CreateCount].vertexWk[0].vtx.x = RightleftObj[CreateCount].Pos.x - RightleftObj[CreateCount].TextureSize.x;
		RightleftObj[CreateCount].vertexWk[0].vtx.y = RightleftObj[CreateCount].Pos.y - RightleftObj[CreateCount].TextureSize.y;
		RightleftObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		RightleftObj[CreateCount].vertexWk[1].vtx.x = RightleftObj[CreateCount].Pos.x + RightleftObj[CreateCount].TextureSize.x;
		RightleftObj[CreateCount].vertexWk[1].vtx.y = RightleftObj[CreateCount].Pos.y - RightleftObj[CreateCount].TextureSize.y;
		RightleftObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		RightleftObj[CreateCount].vertexWk[2].vtx.x = RightleftObj[CreateCount].Pos.x - RightleftObj[CreateCount].TextureSize.x;
		RightleftObj[CreateCount].vertexWk[2].vtx.y = RightleftObj[CreateCount].Pos.y + RightleftObj[CreateCount].TextureSize.y;
		RightleftObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		RightleftObj[CreateCount].vertexWk[3].vtx.x = RightleftObj[CreateCount].Pos.x + RightleftObj[CreateCount].TextureSize.x;
		RightleftObj[CreateCount].vertexWk[3].vtx.y = RightleftObj[CreateCount].Pos.y + RightleftObj[CreateCount].TextureSize.y;
		RightleftObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ� (*34)
//=============================================================================
void Rightleft::SetTextureRightleft(int i)
{

	RightleftObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Alfa);
	RightleftObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Alfa);
	RightleftObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Alfa);
	RightleftObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Color, (int)RightleftObj[i].Alfa);

}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Rightleft::MakeVertexRightleft(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	SetVertexRightleft(i);


	// rhw�̐ݒ�
	RightleftObj[i].vertexWk[0].rhw = 1.0f;
	RightleftObj[i].vertexWk[1].rhw = 1.0f;
	RightleftObj[i].vertexWk[2].rhw = 1.0f;
	RightleftObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureRightleft(i);

	RightleftObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	RightleftObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	RightleftObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	RightleftObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}