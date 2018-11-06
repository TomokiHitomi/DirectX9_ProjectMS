//=============================================================================
//
// �v���C���[���� [titlelogo.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titlelogo.h"
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
//LPDIRECT3DTEXTURE9		g_pD3DTextureTitlelogo000 = NULL;							// �e�N�X�`���ւ̃|���S�� (*33)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Titlelogo::Titlelogo()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::TITLELOGO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Titlelogo::~Titlelogo()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Titlelogo::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_TITLELOGO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLELOGO_000, &Title[i].pD3DTexture);
			}
			Title[i].Pos = D3DXVECTOR3(TEXTURE_TITLELOGO_POSITION000_X, TEXTURE_TITLELOGO_POSITION000_Y, 0.0f);
			Title[i].TextureSize = D3DXVECTOR2(TEXTURE_TITLELOGO_SIZE000_X, TEXTURE_TITLELOGO_SIZE000_Y);
			Title[i].Count = 0;
			Title[i].Alfa = 255;
			Title[i].Use = true;
			Title[i].Texture = Title[i].pD3DTexture;
		}
		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLELOGO_001, &Title[i].pD3DTexture);
			}
			Title[i].Pos = D3DXVECTOR3(TEXTURE_TITLELOGO_POSITION001_X, TEXTURE_TITLELOGO_POSITION001_Y, 0.0f);
			Title[i].TextureSize = D3DXVECTOR2(TEXTURE_TITLELOGO_SIZE001_X, TEXTURE_TITLELOGO_SIZE001_Y);
			Title[i].Count = 0;
			Title[i].Alfa = 254;
			Title[i].Use = true;
			Title[i].Flash = true;
			Title[i].Texture = Title[i].pD3DTexture;
		}
		MakeVertexTitlelogo(i);
	}
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void Titlelogo::Uninit(void)
{
	for (int i = 0; i < NUM_TITLELOGO; i++)
	{
		if (Title[i].pD3DTexture != NULL)	// (*31)
		{	// �e�N�X�`���̊J��
			Title[i].pD3DTexture->Release();
			Title[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Titlelogo::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("Title[0].Alfa:%d\n", Title[0].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("Title[1].Alfa:%d\n", Title[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_TITLELOGO; i++)
	{
		if (GetKeyboardPress(DIK_DOWN))
		{
			Title[0].Pos.y--;
		}
		if (GetKeyboardPress(DIK_UP))
		{
			Title[0].Pos.y++;
		}

		if (i == 1)
		{
			Title[i].Count++;
			if (Title[i].Count < FRAME)
			{
				Title[i].TextureSize.x -= TEXTURE_TITLELOGO_PIXEL001_X / SCREEN_WIDTH;
				Title[i].TextureSize.y -= TEXTURE_TITLELOGO_PIXEL001_Y / SCREEN_HEIGHT;
				Title[i].Alfa -= TEXTURE_TITLELOGO_COLOR_DEFAULT_A /FRAME;
			}
			if (Title[i].Count >= FRAME && Title[i].Count < FRAME*2 && Title[i].Alfa <= TEXTURE_TITLELOGO_COLOR_DEFAULT_A)
			{
				Title[i].TextureSize.x += TEXTURE_TITLELOGO_PIXEL001_X / SCREEN_WIDTH;
				Title[i].TextureSize.y += TEXTURE_TITLELOGO_PIXEL001_Y / SCREEN_HEIGHT;
				Title[i].Alfa += TEXTURE_TITLELOGO_COLOR_DEFAULT_A /FRAME;
			}
			if (Title[i].Count >= FRAME * 2)
			{
				Title[i].Count = 0;
				Title[i].Alfa = TEXTURE_TITLELOGO_COLOR_DEFAULT_A;
			}
			if (Title[i].Alfa >= TEXTURE_TITLELOGO_COLOR_DEFAULT_A)
			{
				Title[i].Count = 0;
				Title[i].Alfa = TEXTURE_TITLELOGO_COLOR_DEFAULT_A;
			}
		}
		//	���_�J���[�̐ݒ�
		SetVertexTitlelogo(i);
		// �e�N�X�`�����W��ݒ�
		SetTextureTitlelogo(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Titlelogo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_TITLELOGO; i++)
	{
		if (Title[i].Use == true)
		{
			pDevice->SetTexture(0, Title[i].pD3DTexture);


			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Title[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set�֐�
//=============================================================================
void Titlelogo::SetVertexTitlelogo(int CreateCount)
{

	if (CreateCount == 0)
	{
		Title[CreateCount].vertexWk[0].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[0].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[0].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[1].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[1].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[1].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[2].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[2].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[2].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[3].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[3].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
	if (CreateCount == 1)
	{
		Title[CreateCount].vertexWk[0].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[0].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[0].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[1].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[1].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[1].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[2].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[2].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[2].vtx.z = 0.0f;
		Title[CreateCount].vertexWk[3].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
		Title[CreateCount].vertexWk[3].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
		Title[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ� (*34)
//=============================================================================
void Titlelogo::SetTextureTitlelogo(int i)
{
	if (i == 0)
	{
		Title[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
		Title[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
		Title[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
		Title[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
	}
	if (i == 1)
	{
		Title[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, Title[1].Alfa);
		Title[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, Title[1].Alfa);
		Title[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, Title[1].Alfa);
		Title[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, Title[1].Alfa);
	}

}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Titlelogo::MakeVertexTitlelogo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	SetVertexTitlelogo(i);


	// rhw�̐ݒ�
	Title[i].vertexWk[0].rhw = 1.0f;
	Title[i].vertexWk[1].rhw = 1.0f;
	Title[i].vertexWk[2].rhw = 1.0f;
	Title[i].vertexWk[3].rhw = 1.0f;

	Title[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
	Title[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
	Title[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
	Title[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLELOGO_COLOR_DEFAULT_R, TEXTURE_TITLELOGO_COLOR_DEFAULT_G, TEXTURE_TITLELOGO_COLOR_DEFAULT_B, TEXTURE_TITLELOGO_COLOR_DEFAULT_A);
	
	Title[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Title[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Title[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Title[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}