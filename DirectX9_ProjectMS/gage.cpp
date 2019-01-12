//=============================================================================
//
// �v���C���[���� [gage.cpp]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "gage.h"
#include "gage3d.h"
#include "character.h"
#include "scene.h"
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
Gage::Gage()
{
	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
	SetIdAndPriority(ObjectID::GAGE, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Gage::~Gage()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Gage::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_GAGE; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_000, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION000_X, TEXTURE_GAGE_POSITION000_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE000_X, TEXTURE_GAGE_SIZE000_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION001_X, TEXTURE_GAGE_POSITION001_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE001_X, TEXTURE_GAGE_SIZE001_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 2)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION002_X, TEXTURE_GAGE_POSITION002_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE002_X, TEXTURE_GAGE_SIZE002_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 3)
		{

			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION003_X, TEXTURE_GAGE_POSITION003_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE003_X, TEXTURE_GAGE_SIZE003_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 4)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION004_X, TEXTURE_GAGE_POSITION004_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE004_X, TEXTURE_GAGE_SIZE004_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 5)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION005_X, TEXTURE_GAGE_POSITION005_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE005_X, TEXTURE_GAGE_SIZE005_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 6)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION006_X, TEXTURE_GAGE_POSITION006_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE006_X, TEXTURE_GAGE_SIZE006_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 7)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION007_X, TEXTURE_GAGE_POSITION007_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE007_X, TEXTURE_GAGE_SIZE007_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 8)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION008_X, TEXTURE_GAGE_POSITION008_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE008_X, TEXTURE_GAGE_SIZE008_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 9)
		{

			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION009_X, TEXTURE_GAGE_POSITION009_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE009_X, TEXTURE_GAGE_SIZE009_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 10)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_010, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION010_X, TEXTURE_GAGE_POSITION010_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE010_X, TEXTURE_GAGE_SIZE010_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 11)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_011, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION011_X, TEXTURE_GAGE_POSITION011_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE011_X, TEXTURE_GAGE_SIZE011_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 12)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_012, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION012_X, TEXTURE_GAGE_POSITION012_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE012_X, TEXTURE_GAGE_SIZE012_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 13)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_013, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION013_X, TEXTURE_GAGE_POSITION013_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE013_X, TEXTURE_GAGE_SIZE013_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 14)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION014_X, TEXTURE_GAGE_POSITION014_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE014_X, TEXTURE_GAGE_SIZE014_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[10].pD3DTexture;
		}
		if (i == 15)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION015_X, TEXTURE_GAGE_POSITION015_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE015_X, TEXTURE_GAGE_SIZE015_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[11].pD3DTexture;
		}
		if (i == 16)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION016_X, TEXTURE_GAGE_POSITION016_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE016_X, TEXTURE_GAGE_SIZE016_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[12].pD3DTexture;
		}
		if (i == 17)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION017_X, TEXTURE_GAGE_POSITION017_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE017_X, TEXTURE_GAGE_SIZE017_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[13].pD3DTexture;
		}
		GageObj[i].Scale = D3DXVECTOR2(TEXTURE_GAGE_SCALE_X, TEXTURE_GAGE_SCALE_Y);
		GageObj[i].Angle = TEXTURE_GAGE_ANGLE_X;
		GageObj[i].NowHp = TEXTURE_GAGE3D_MAX_HP;
		GageObj[i].NowSkill = 0.0f;
		//GageObj[i].pos = D3DXVECTOR3(i*10.0f, 0.0f, 0.0f);
		//GageObj[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//GageObj[i].scl = D3DXVECTOR3(1.0, 1.0, 1.0);

		MakeVertexGage(i);
	}


	int nTemp;
	nTemp = SceneManager::GetSelectChar(0);
	GageObj[10 + nTemp].Use = true;
	nTemp = SceneManager::GetSelectChar(1);
	GageObj[14 + nTemp].Use = true;

	return S_OK;
}

//=============================================================================
// HP�ESP�̏�����
//=============================================================================
void Gage::InitStatus(void)
{
	for (unsigned int i = 0; i < NUM_GAGE; i++)
	{
		if (i == 0)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION000_X, TEXTURE_GAGE_POSITION000_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE000_X, TEXTURE_GAGE_SIZE000_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION001_X, TEXTURE_GAGE_POSITION001_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE001_X, TEXTURE_GAGE_SIZE001_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 2)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION002_X, TEXTURE_GAGE_POSITION002_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE002_X, TEXTURE_GAGE_SIZE002_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 3)
		{

			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION003_X, TEXTURE_GAGE_POSITION003_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE003_X, TEXTURE_GAGE_SIZE003_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 4)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION004_X, TEXTURE_GAGE_POSITION004_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE004_X, TEXTURE_GAGE_SIZE004_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 5)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION005_X, TEXTURE_GAGE_POSITION005_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE005_X, TEXTURE_GAGE_SIZE005_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 6)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION006_X, TEXTURE_GAGE_POSITION006_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE006_X, TEXTURE_GAGE_SIZE006_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 7)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION007_X, TEXTURE_GAGE_POSITION007_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE007_X, TEXTURE_GAGE_SIZE007_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 8)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION008_X, TEXTURE_GAGE_POSITION008_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE008_X, TEXTURE_GAGE_SIZE008_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 9)
		{

			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION009_X, TEXTURE_GAGE_POSITION009_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE009_X, TEXTURE_GAGE_SIZE009_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[0].pD3DTexture;
		}
		if (i == 10)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION010_X, TEXTURE_GAGE_POSITION010_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE010_X, TEXTURE_GAGE_SIZE010_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 11)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION011_X, TEXTURE_GAGE_POSITION011_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE011_X, TEXTURE_GAGE_SIZE011_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 12)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION012_X, TEXTURE_GAGE_POSITION012_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE012_X, TEXTURE_GAGE_SIZE012_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 13)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION013_X, TEXTURE_GAGE_POSITION013_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE013_X, TEXTURE_GAGE_SIZE013_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 14)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION014_X, TEXTURE_GAGE_POSITION014_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE014_X, TEXTURE_GAGE_SIZE014_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[10].pD3DTexture;
		}
		if (i == 15)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION015_X, TEXTURE_GAGE_POSITION015_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE015_X, TEXTURE_GAGE_SIZE015_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[11].pD3DTexture;
		}
		if (i == 16)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION016_X, TEXTURE_GAGE_POSITION016_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE016_X, TEXTURE_GAGE_SIZE016_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[12].pD3DTexture;
		}
		if (i == 17)
		{
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION017_X, TEXTURE_GAGE_POSITION017_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE017_X, TEXTURE_GAGE_SIZE017_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[13].pD3DTexture;
		}
		GageObj[i].Scale = D3DXVECTOR2(TEXTURE_GAGE_SCALE_X, TEXTURE_GAGE_SCALE_Y);
		GageObj[i].Angle = TEXTURE_GAGE_ANGLE_X;
		GageObj[i].NowHp = TEXTURE_GAGE3D_MAX_HP;
		GageObj[i].NowSkill = 0.0f;
	}

	int nTemp;
	nTemp = SceneManager::GetSelectChar(0);
	GageObj[10 + nTemp].Use = true;
	nTemp = SceneManager::GetSelectChar(1);
	GageObj[14 + nTemp].Use = true;
}



//=============================================================================
// �I������
//=============================================================================
void Gage::Uninit(void)
{
	for (int i = 0; i < NUM_GAGE; i++)
	{
		if (i < 10)
		{
			if (GageObj[0].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				GageObj[0].pD3DTexture->Release();
				GageObj[0].pD3DTexture = NULL;
			}
		}
		if (i == 10||i==14)
		{
			if (GageObj[10].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				GageObj[10].pD3DTexture->Release();
				GageObj[10].pD3DTexture = NULL;
			}
		}
		if (i == 11 || i == 15)
		{
			if (GageObj[11].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				GageObj[11].pD3DTexture->Release();
				GageObj[11].pD3DTexture = NULL;
			}
		}
		if (i == 12 || i == 16)
		{
			if (GageObj[12].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				GageObj[12].pD3DTexture->Release();
				GageObj[12].pD3DTexture = NULL;
			}
		}
		if (i == 13 || i == 17)
		{
			if (GageObj[13].pD3DTexture != NULL)	// (*31)
			{	// �e�N�X�`���̊J��
				GageObj[13].pD3DTexture->Release();
				GageObj[13].pD3DTexture = NULL;
			}
		}
		//if (GageObj[i].pD3DXBuffMat != NULL)
		//{// �}�e���A���̊J��
		//	GageObj[i].pD3DXBuffMat->Release();
		//	GageObj[i].pD3DXBuffMat = NULL;
		//}
	}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void Gage::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("GageObj[4].TextureSize.x :%f\n", GageObj[4].TextureSize.x);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_GAGE; i++)
	{
		if (GetKeyboardPress(DIK_1))
		{
			DamegeReduce(OFFSET_DAMEGE_000, 0);
		}
		if (GetKeyboardPress(DIK_2))
		{
			DamegeReduce(OFFSET_DAMEGE_000, 1);
		}
		if (GetKeyboardRelease(DIK_1))
		{
			GageObj[2].Use = false;
		}
		if (GetKeyboardRelease(DIK_2))
		{
			GageObj[3].Use = false;
		}
		if (GetKeyboardPress(DIK_3))
		{
			SkillAdd(SKILL_000,0);
		}
		if (GetKeyboardPress(DIK_4))
		{
			SkillAdd(SKILL_000, 1);
		}
		if (GetKeyboardPress(DIK_5))
		{
			GageObj[8].TextureSize.x--;

		}
		if (GetKeyboardPress(DIK_6))
		{
			GageObj[9].TextureSize.x--;
		}
		//if (GetKeyboardPress(DIK_Q))
		//{
		//	GageObj[10].Use = true;
		//	GageObj[11].Use = false;
		//	GageObj[12].Use = false;
		//	GageObj[13].Use = false;
		//}
		//if (GetKeyboardPress(DIK_W))
		//{
		//	GageObj[10].Use = false;
		//	GageObj[11].Use = true;
		//	GageObj[12].Use = false;
		//	GageObj[13].Use = false;
		//}
		//if (GetKeyboardPress(DIK_E))
		//{
		//	GageObj[10].Use = false;
		//	GageObj[11].Use = false;
		//	GageObj[12].Use = true;
		//	GageObj[13].Use = false;
		//}
		//if (GetKeyboardPress(DIK_R))
		//{
		//	GageObj[10].Use = false;
		//	GageObj[11].Use = false;
		//	GageObj[12].Use = false;
		//	GageObj[13].Use = true;
		//}
		//if (GetKeyboardPress(DIK_A))
		//{
		//	GageObj[14].Use = true;
		//	GageObj[15].Use = false;
		//	GageObj[16].Use = false;
		//	GageObj[17].Use = false;
		//}
		//if (GetKeyboardPress(DIK_S))
		//{
		//	GageObj[14].Use = false;
		//	GageObj[15].Use = true;
		//	GageObj[16].Use = false;
		//	GageObj[17].Use = false;
		//}
		//if (GetKeyboardPress(DIK_D))
		//{
		//	GageObj[14].Use = false;
		//	GageObj[15].Use = false;
		//	GageObj[16].Use = true;
		//	GageObj[17].Use = false;
		//}
		//if (GetKeyboardPress(DIK_F))
		//{
		//	GageObj[14].Use = false;
		//	GageObj[15].Use = false;
		//	GageObj[16].Use = false;
		//	GageObj[17].Use = true;
		//}
		if (GetKeyboardPress(DIK_Z))
		{
			GageObj[i].Scale.x += 0.01;
			GageObj[i].Scale.y += 0.01;

		}
		if (GetKeyboardPress(DIK_X))
		{
			GageObj[i].Scale.x -= 0.01;
			GageObj[i].Scale.y -= 0.01;
		}

		//	���_�J���[�̐ݒ�
		SetVertexGage(i);
		// �e�N�X�`�����W��ݒ�
		SetTextureGage(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Gage::Draw(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	//// ���C���e�B���O�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//for (int i = 0; i < NUM_GAGE; i++)
	//{
	//	D3DXMatrixIdentity(&GageObj[i].mtxWorld);																	//���[���h�}�g���N�X�̏�����
	//	D3DXMatrixScaling(&mtxScl, GageObj[i].scl.x, GageObj[i].scl.y, GageObj[i].scl.z);						//�g��𔽉f(�g��)
	//	D3DXMatrixMultiply(&GageObj[i].mtxWorld, &GageObj[i].mtxWorld, &mtxScl);									//�s��̍���(�g��)
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, GageObj[i].rot.y, GageObj[i].rot.x, GageObj[i].rot.z);			//��]�̔��f(��])
	//	D3DXMatrixMultiply(&GageObj[i].mtxWorld, &GageObj[i].mtxWorld, &mtxRot);									//�s��̍���(��])
	//	D3DXMatrixTranslation(&mtxTranslate, GageObj[i].pos.x, GageObj[i].pos.y, GageObj[i].pos.z);				//�ړ��̔��f(�ړ�)
	//	D3DXMatrixMultiply(&GageObj[i].mtxWorld, &GageObj[i].mtxWorld, &mtxTranslate);							//�s��̍���(�ړ�)
	//	pDevice->SetTransform(D3DTS_WORLD, &GageObj[i].mtxWorld);													//���[���h�}�g���N�X�̐ݒ�
	//	pDevice->SetStreamSource(0, GageObj[i].pD3DVtxBuff, 0, sizeof(VERTEX_2D));								//���_�o�b�t�@
	//	pDevice->SetFVF(FVF_VERTEX_2D);
	//	pDevice->SetTexture(0, GageObj[i].pD3DTexture);
	//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//																												//pD3DXMat = (D3DXMATERIAL*)GageObj[i].pD3DXBuffMat->GetBufferPointer();											//�}�e���A�����ɑ΂���|�C���^�̎擾
	//}
	//// ���C���e�B���O�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
		
	for (int i = 0; i < NUM_GAGE; i++)
	{
		
		if (GageObj[i].Use == true)
		{

			//// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			//pDevice->SetStreamSource(0, GageObj[i].vertexWk, 0, sizeof(VERTEX_2D));

			if (i == 0) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 1) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 2) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 3) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 4) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 5) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 6) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 7) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 8) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 9) { pDevice->SetTexture(0, GageObj[0].pD3DTexture); }
			if (i == 10) { pDevice->SetTexture(0, GageObj[10].pD3DTexture); }
			if (i == 11) { pDevice->SetTexture(0, GageObj[11].pD3DTexture); }
			if (i == 12) { pDevice->SetTexture(0, GageObj[12].pD3DTexture); }
			if (i == 13) { pDevice->SetTexture(0, GageObj[13].pD3DTexture); }
			if (i == 14) { pDevice->SetTexture(0, GageObj[10].pD3DTexture); }
			if (i == 15) { pDevice->SetTexture(0, GageObj[11].pD3DTexture); }
			if (i == 16) { pDevice->SetTexture(0, GageObj[12].pD3DTexture); }
			if (i == 17) { pDevice->SetTexture(0, GageObj[13].pD3DTexture); }

			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, GageObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set�֐�
//=============================================================================
void Gage::SetVertexGage(int CreateCount)
{
	if (CreateCount < NUM_GAGE)
	{
		GageObj[CreateCount].vertexWk[0].vtx.x = GageObj[CreateCount].Pos.x;
		GageObj[CreateCount].vertexWk[0].vtx.y = GageObj[CreateCount].Pos.y;
		GageObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		GageObj[CreateCount].vertexWk[1].vtx.x = GageObj[CreateCount].Pos.x + (cosf(GageObj[CreateCount].Angle)*GageObj[CreateCount].TextureSize.x);
		GageObj[CreateCount].vertexWk[1].vtx.y = GageObj[CreateCount].Pos.y + (sinf(GageObj[CreateCount].Angle)*GageObj[CreateCount].TextureSize.x);
		GageObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		GageObj[CreateCount].vertexWk[2].vtx.x = GageObj[CreateCount].Pos.x;
		GageObj[CreateCount].vertexWk[2].vtx.y = GageObj[CreateCount].Pos.y + GageObj[CreateCount].TextureSize.y;
		GageObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		GageObj[CreateCount].vertexWk[3].vtx.x = GageObj[CreateCount].Pos.x + (cosf(GageObj[CreateCount].Angle)*GageObj[CreateCount].TextureSize.x);
		GageObj[CreateCount].vertexWk[3].vtx.y = GageObj[CreateCount].Pos.y + (sinf(GageObj[CreateCount].Angle)*GageObj[CreateCount].TextureSize.x)+GageObj[CreateCount].TextureSize.y;
		GageObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ� (*34)
//=============================================================================
void Gage::SetTextureGage(int i)
{
	if (i == 0)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT000_R, TEXTURE_GAGE_COLOR_DEFAULT000_G, TEXTURE_GAGE_COLOR_DEFAULT000_B, TEXTURE_GAGE_COLOR_DEFAULT000_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT000_R, TEXTURE_GAGE_COLOR_DEFAULT000_G, TEXTURE_GAGE_COLOR_DEFAULT000_B, TEXTURE_GAGE_COLOR_DEFAULT000_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT000_R, TEXTURE_GAGE_COLOR_DEFAULT000_G, TEXTURE_GAGE_COLOR_DEFAULT000_B, TEXTURE_GAGE_COLOR_DEFAULT000_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT000_R, TEXTURE_GAGE_COLOR_DEFAULT000_G, TEXTURE_GAGE_COLOR_DEFAULT000_B, TEXTURE_GAGE_COLOR_DEFAULT000_A);
	}
	if (i == 1)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT001_R, TEXTURE_GAGE_COLOR_DEFAULT001_G, TEXTURE_GAGE_COLOR_DEFAULT001_B, TEXTURE_GAGE_COLOR_DEFAULT001_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT001_R, TEXTURE_GAGE_COLOR_DEFAULT001_G, TEXTURE_GAGE_COLOR_DEFAULT001_B, TEXTURE_GAGE_COLOR_DEFAULT001_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT001_R, TEXTURE_GAGE_COLOR_DEFAULT001_G, TEXTURE_GAGE_COLOR_DEFAULT001_B, TEXTURE_GAGE_COLOR_DEFAULT001_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT001_R, TEXTURE_GAGE_COLOR_DEFAULT001_G, TEXTURE_GAGE_COLOR_DEFAULT001_B, TEXTURE_GAGE_COLOR_DEFAULT001_A);
	}
	if (i == 2)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT002_R, TEXTURE_GAGE_COLOR_DEFAULT002_G, TEXTURE_GAGE_COLOR_DEFAULT002_B, TEXTURE_GAGE_COLOR_DEFAULT002_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT002_R, TEXTURE_GAGE_COLOR_DEFAULT002_G, TEXTURE_GAGE_COLOR_DEFAULT002_B, TEXTURE_GAGE_COLOR_DEFAULT002_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT002_R, TEXTURE_GAGE_COLOR_DEFAULT002_G, TEXTURE_GAGE_COLOR_DEFAULT002_B, TEXTURE_GAGE_COLOR_DEFAULT002_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT002_R, TEXTURE_GAGE_COLOR_DEFAULT002_G, TEXTURE_GAGE_COLOR_DEFAULT002_B, TEXTURE_GAGE_COLOR_DEFAULT002_A);
	}
	if (i == 3)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT003_R, TEXTURE_GAGE_COLOR_DEFAULT003_G, TEXTURE_GAGE_COLOR_DEFAULT003_B, TEXTURE_GAGE_COLOR_DEFAULT003_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT003_R, TEXTURE_GAGE_COLOR_DEFAULT003_G, TEXTURE_GAGE_COLOR_DEFAULT003_B, TEXTURE_GAGE_COLOR_DEFAULT003_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT003_R, TEXTURE_GAGE_COLOR_DEFAULT003_G, TEXTURE_GAGE_COLOR_DEFAULT003_B, TEXTURE_GAGE_COLOR_DEFAULT003_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT003_R, TEXTURE_GAGE_COLOR_DEFAULT003_G, TEXTURE_GAGE_COLOR_DEFAULT003_B, TEXTURE_GAGE_COLOR_DEFAULT003_A);
	}
	if (i == 4)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT004_R, TEXTURE_GAGE_COLOR_DEFAULT004_G, TEXTURE_GAGE_COLOR_DEFAULT004_B, TEXTURE_GAGE_COLOR_DEFAULT004_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT004_R, TEXTURE_GAGE_COLOR_DEFAULT004_G, TEXTURE_GAGE_COLOR_DEFAULT004_B, TEXTURE_GAGE_COLOR_DEFAULT004_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT004_R, TEXTURE_GAGE_COLOR_DEFAULT004_G, TEXTURE_GAGE_COLOR_DEFAULT004_B, TEXTURE_GAGE_COLOR_DEFAULT004_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT004_R, TEXTURE_GAGE_COLOR_DEFAULT004_G, TEXTURE_GAGE_COLOR_DEFAULT004_B, TEXTURE_GAGE_COLOR_DEFAULT004_A);
	}
	if (i == 5)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT005_R, TEXTURE_GAGE_COLOR_DEFAULT005_G, TEXTURE_GAGE_COLOR_DEFAULT005_B, TEXTURE_GAGE_COLOR_DEFAULT005_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT005_R, TEXTURE_GAGE_COLOR_DEFAULT005_G, TEXTURE_GAGE_COLOR_DEFAULT005_B, TEXTURE_GAGE_COLOR_DEFAULT005_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT005_R, TEXTURE_GAGE_COLOR_DEFAULT005_G, TEXTURE_GAGE_COLOR_DEFAULT005_B, TEXTURE_GAGE_COLOR_DEFAULT005_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT005_R, TEXTURE_GAGE_COLOR_DEFAULT005_G, TEXTURE_GAGE_COLOR_DEFAULT005_B, TEXTURE_GAGE_COLOR_DEFAULT005_A);
	}
	if (i == 6)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT006_R, TEXTURE_GAGE_COLOR_DEFAULT006_G, TEXTURE_GAGE_COLOR_DEFAULT006_B, TEXTURE_GAGE_COLOR_DEFAULT006_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT006_R, TEXTURE_GAGE_COLOR_DEFAULT006_G, TEXTURE_GAGE_COLOR_DEFAULT006_B, TEXTURE_GAGE_COLOR_DEFAULT006_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT006_R, TEXTURE_GAGE_COLOR_DEFAULT006_G, TEXTURE_GAGE_COLOR_DEFAULT006_B, TEXTURE_GAGE_COLOR_DEFAULT006_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT006_R, TEXTURE_GAGE_COLOR_DEFAULT006_G, TEXTURE_GAGE_COLOR_DEFAULT006_B, TEXTURE_GAGE_COLOR_DEFAULT006_A);
	}
	if (i == 7)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT007_R, TEXTURE_GAGE_COLOR_DEFAULT007_G, TEXTURE_GAGE_COLOR_DEFAULT007_B, TEXTURE_GAGE_COLOR_DEFAULT007_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT007_R, TEXTURE_GAGE_COLOR_DEFAULT007_G, TEXTURE_GAGE_COLOR_DEFAULT007_B, TEXTURE_GAGE_COLOR_DEFAULT007_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT007_R, TEXTURE_GAGE_COLOR_DEFAULT007_G, TEXTURE_GAGE_COLOR_DEFAULT007_B, TEXTURE_GAGE_COLOR_DEFAULT007_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT007_R, TEXTURE_GAGE_COLOR_DEFAULT007_G, TEXTURE_GAGE_COLOR_DEFAULT007_B, TEXTURE_GAGE_COLOR_DEFAULT007_A);
	}
	if (i == 8)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT008_R, TEXTURE_GAGE_COLOR_DEFAULT008_G, TEXTURE_GAGE_COLOR_DEFAULT008_B, TEXTURE_GAGE_COLOR_DEFAULT008_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT008_R, TEXTURE_GAGE_COLOR_DEFAULT008_G, TEXTURE_GAGE_COLOR_DEFAULT008_B, TEXTURE_GAGE_COLOR_DEFAULT008_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT008_R, TEXTURE_GAGE_COLOR_DEFAULT008_G, TEXTURE_GAGE_COLOR_DEFAULT008_B, TEXTURE_GAGE_COLOR_DEFAULT008_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT008_R, TEXTURE_GAGE_COLOR_DEFAULT008_G, TEXTURE_GAGE_COLOR_DEFAULT008_B, TEXTURE_GAGE_COLOR_DEFAULT008_A);
	}
	if (i == 9)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT009_R, TEXTURE_GAGE_COLOR_DEFAULT009_G, TEXTURE_GAGE_COLOR_DEFAULT009_B, TEXTURE_GAGE_COLOR_DEFAULT009_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT009_R, TEXTURE_GAGE_COLOR_DEFAULT009_G, TEXTURE_GAGE_COLOR_DEFAULT009_B, TEXTURE_GAGE_COLOR_DEFAULT009_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT009_R, TEXTURE_GAGE_COLOR_DEFAULT009_G, TEXTURE_GAGE_COLOR_DEFAULT009_B, TEXTURE_GAGE_COLOR_DEFAULT009_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT009_R, TEXTURE_GAGE_COLOR_DEFAULT009_G, TEXTURE_GAGE_COLOR_DEFAULT009_B, TEXTURE_GAGE_COLOR_DEFAULT009_A);
	}
	if (i == 10)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT010_R, TEXTURE_GAGE_COLOR_DEFAULT010_G, TEXTURE_GAGE_COLOR_DEFAULT010_B, TEXTURE_GAGE_COLOR_DEFAULT010_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT010_R, TEXTURE_GAGE_COLOR_DEFAULT010_G, TEXTURE_GAGE_COLOR_DEFAULT010_B, TEXTURE_GAGE_COLOR_DEFAULT010_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT010_R, TEXTURE_GAGE_COLOR_DEFAULT010_G, TEXTURE_GAGE_COLOR_DEFAULT010_B, TEXTURE_GAGE_COLOR_DEFAULT010_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT010_R, TEXTURE_GAGE_COLOR_DEFAULT010_G, TEXTURE_GAGE_COLOR_DEFAULT010_B, TEXTURE_GAGE_COLOR_DEFAULT010_A);
	}
	if (i == 11)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT011_R, TEXTURE_GAGE_COLOR_DEFAULT011_G, TEXTURE_GAGE_COLOR_DEFAULT011_B, TEXTURE_GAGE_COLOR_DEFAULT011_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT011_R, TEXTURE_GAGE_COLOR_DEFAULT011_G, TEXTURE_GAGE_COLOR_DEFAULT011_B, TEXTURE_GAGE_COLOR_DEFAULT011_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT011_R, TEXTURE_GAGE_COLOR_DEFAULT011_G, TEXTURE_GAGE_COLOR_DEFAULT011_B, TEXTURE_GAGE_COLOR_DEFAULT011_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT011_R, TEXTURE_GAGE_COLOR_DEFAULT011_G, TEXTURE_GAGE_COLOR_DEFAULT011_B, TEXTURE_GAGE_COLOR_DEFAULT011_A);
	}
	if (i == 12)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT012_R, TEXTURE_GAGE_COLOR_DEFAULT012_G, TEXTURE_GAGE_COLOR_DEFAULT012_B, TEXTURE_GAGE_COLOR_DEFAULT012_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT012_R, TEXTURE_GAGE_COLOR_DEFAULT012_G, TEXTURE_GAGE_COLOR_DEFAULT012_B, TEXTURE_GAGE_COLOR_DEFAULT012_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT012_R, TEXTURE_GAGE_COLOR_DEFAULT012_G, TEXTURE_GAGE_COLOR_DEFAULT012_B, TEXTURE_GAGE_COLOR_DEFAULT012_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT012_R, TEXTURE_GAGE_COLOR_DEFAULT012_G, TEXTURE_GAGE_COLOR_DEFAULT012_B, TEXTURE_GAGE_COLOR_DEFAULT012_A);
	}
	if (i == 13)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT013_R, TEXTURE_GAGE_COLOR_DEFAULT013_G, TEXTURE_GAGE_COLOR_DEFAULT013_B, TEXTURE_GAGE_COLOR_DEFAULT013_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT013_R, TEXTURE_GAGE_COLOR_DEFAULT013_G, TEXTURE_GAGE_COLOR_DEFAULT013_B, TEXTURE_GAGE_COLOR_DEFAULT013_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT013_R, TEXTURE_GAGE_COLOR_DEFAULT013_G, TEXTURE_GAGE_COLOR_DEFAULT013_B, TEXTURE_GAGE_COLOR_DEFAULT013_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT013_R, TEXTURE_GAGE_COLOR_DEFAULT013_G, TEXTURE_GAGE_COLOR_DEFAULT013_B, TEXTURE_GAGE_COLOR_DEFAULT013_A);
	}
	if (i == 14)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT014_R, TEXTURE_GAGE_COLOR_DEFAULT014_G, TEXTURE_GAGE_COLOR_DEFAULT014_B, TEXTURE_GAGE_COLOR_DEFAULT014_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT014_R, TEXTURE_GAGE_COLOR_DEFAULT014_G, TEXTURE_GAGE_COLOR_DEFAULT014_B, TEXTURE_GAGE_COLOR_DEFAULT014_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT014_R, TEXTURE_GAGE_COLOR_DEFAULT014_G, TEXTURE_GAGE_COLOR_DEFAULT014_B, TEXTURE_GAGE_COLOR_DEFAULT014_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT014_R, TEXTURE_GAGE_COLOR_DEFAULT014_G, TEXTURE_GAGE_COLOR_DEFAULT014_B, TEXTURE_GAGE_COLOR_DEFAULT014_A);
	}
	if (i == 15)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT015_R, TEXTURE_GAGE_COLOR_DEFAULT015_G, TEXTURE_GAGE_COLOR_DEFAULT015_B, TEXTURE_GAGE_COLOR_DEFAULT015_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT015_R, TEXTURE_GAGE_COLOR_DEFAULT015_G, TEXTURE_GAGE_COLOR_DEFAULT015_B, TEXTURE_GAGE_COLOR_DEFAULT015_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT015_R, TEXTURE_GAGE_COLOR_DEFAULT015_G, TEXTURE_GAGE_COLOR_DEFAULT015_B, TEXTURE_GAGE_COLOR_DEFAULT015_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT015_R, TEXTURE_GAGE_COLOR_DEFAULT015_G, TEXTURE_GAGE_COLOR_DEFAULT015_B, TEXTURE_GAGE_COLOR_DEFAULT015_A);
	}
	if (i == 16)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT016_R, TEXTURE_GAGE_COLOR_DEFAULT016_G, TEXTURE_GAGE_COLOR_DEFAULT016_B, TEXTURE_GAGE_COLOR_DEFAULT016_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT016_R, TEXTURE_GAGE_COLOR_DEFAULT016_G, TEXTURE_GAGE_COLOR_DEFAULT016_B, TEXTURE_GAGE_COLOR_DEFAULT016_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT016_R, TEXTURE_GAGE_COLOR_DEFAULT016_G, TEXTURE_GAGE_COLOR_DEFAULT016_B, TEXTURE_GAGE_COLOR_DEFAULT016_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT016_R, TEXTURE_GAGE_COLOR_DEFAULT016_G, TEXTURE_GAGE_COLOR_DEFAULT016_B, TEXTURE_GAGE_COLOR_DEFAULT016_A);
	}
	if (i == 17)
	{
		GageObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT017_R, TEXTURE_GAGE_COLOR_DEFAULT017_G, TEXTURE_GAGE_COLOR_DEFAULT017_B, TEXTURE_GAGE_COLOR_DEFAULT017_A);
		GageObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT017_R, TEXTURE_GAGE_COLOR_DEFAULT017_G, TEXTURE_GAGE_COLOR_DEFAULT017_B, TEXTURE_GAGE_COLOR_DEFAULT017_A);
		GageObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT017_R, TEXTURE_GAGE_COLOR_DEFAULT017_G, TEXTURE_GAGE_COLOR_DEFAULT017_B, TEXTURE_GAGE_COLOR_DEFAULT017_A);
		GageObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GAGE_COLOR_DEFAULT017_R, TEXTURE_GAGE_COLOR_DEFAULT017_G, TEXTURE_GAGE_COLOR_DEFAULT017_B, TEXTURE_GAGE_COLOR_DEFAULT017_A);
	}

}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Gage::MakeVertexGage(int i)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	//if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
	//	D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
	//	FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
	//	D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
	//	&GageObj[i].pD3DVtxBuff,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	//	NULL)))						// NULL�ɐݒ�
	//{
	//	return E_FAIL;
	//}

	//{//���_�o�b�t�@�̒��g�𖄂߂�
	//	VERTEX_3D *pVtx;

	//	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	//	GageObj[i].pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	// ���_���W�̐ݒ�(local)
	//	pVtx[0].vtx = D3DXVECTOR3(-1.0, 1.0, 1.0);
	//	pVtx[1].vtx = D3DXVECTOR3(1.0, 1.0, 1.0);
	//	pVtx[2].vtx = D3DXVECTOR3(-1.0, 1.0, -1.0);
	//	pVtx[3].vtx = D3DXVECTOR3(1.0, 1.0, -1.0);

	//	// �@���x�N�g���̐ݒ�
	//	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	// ���ˌ��̐ݒ�
	//	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// �e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	// ���_�f�[�^���A�����b�N����
	//	GageObj[i].pD3DVtxBuff->Unlock();
	//}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// ���_���W�̐ݒ�
	SetVertexGage(i);


	// rhw�̐ݒ�
	GageObj[i].vertexWk[0].rhw = 1.0f;
	GageObj[i].vertexWk[1].rhw = 1.0f;
	GageObj[i].vertexWk[2].rhw = 1.0f;
	GageObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureGage(i);

	GageObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	GageObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	GageObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	GageObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}
void Gage::DamegeReduce(float Damege,int player)
{
	if(player == 0)
	{

		GageObj[2].Use = true;
		GageObj[4].NowHp -= Damege;
		if (GageObj[4].NowHp < 0.0f) GageObj[4].NowHp = 0.0f;
		GageObj[4].TextureSize.x = TEXTURE_GAGE_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * GageObj[4].NowHp;
		//if (GageObj[4].TextureSize.x <= 0.0f)
		//{
		//	GageObj[4].TextureSize.x = 0.0f;
		//}	
	}
	if (player == 1)
	{
		GageObj[3].Use = true;
		GageObj[5].NowHp -= Damege;
		if (GageObj[5].NowHp < 0.0f) GageObj[5].NowHp = 0.0f;
		GageObj[5].TextureSize.x = TEXTURE_GAGE_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * GageObj[5].NowHp;
		//if (GageObj[5].TextureSize.x <= 0.0f)
		//{
		//	GageObj[5].TextureSize.x = 0.0f;
		//}
	}
}
void Gage::DamegeAdd(float Damege, int player)
{
	if (player == 0)
	{
		GageObj[4].NowHp += Damege;
		if (GageObj[4].NowHp > TEXTURE_GAGE3D_MAX_HP) GageObj[4].NowHp = TEXTURE_GAGE3D_MAX_HP;
		GageObj[4].TextureSize.x = TEXTURE_GAGE_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * GageObj[4].NowHp;
		//if (GageObj[4].TextureSize.x <= TEXTURE_GAGE_SIZE004_X)
		//{
		//	GageObj[4].TextureSize.x = TEXTURE_GAGE_SIZE004_X;
		//}
	}
	if (player == 1)
	{
		GageObj[5].NowHp += Damege;
		if (GageObj[5].NowHp > TEXTURE_GAGE3D_MAX_HP) GageObj[5].NowHp = TEXTURE_GAGE3D_MAX_HP;
		GageObj[5].TextureSize.x = TEXTURE_GAGE_SIZE005_X / TEXTURE_GAGE3D_MAX_HP *GageObj[5].NowHp;
		//if (GageObj[5].TextureSize.x <= TEXTURE_GAGE_SIZE005_X)
		//{
		//	GageObj[5].TextureSize.x = TEXTURE_GAGE_SIZE005_X;
		//}
	}
}
void Gage::SkillReduce(float Damege, int player)
{
	if (player == 0)
	{
		GageObj[8].NowSkill -= Damege;
		if (GageObj[8].NowSkill < 0.0f) GageObj[8].NowSkill = 0.0f;
		GageObj[8].TextureSize.x = TEXTURE_GAGE_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * GageObj[8].NowSkill;
		//if (GageObj[8].TextureSize.x < 0.0f)
		//{
		//	GageObj[8].TextureSize.x = 0.0f;
		//}
	}
	if (player == 1)
	{
		GageObj[9].NowSkill -= Damege;
		if (GageObj[9].NowSkill < 0.0f) GageObj[9].NowSkill = 0.0f;
		GageObj[9].TextureSize.x = TEXTURE_GAGE_SIZE005_X / TEXTURE_GAGE3D_MAX_HP * GageObj[9].NowSkill;
		//if (GageObj[9].TextureSize.x < 0.0f)
		//{
		//	GageObj[9].TextureSize.x = 0.0f;
		//}
	}
}
void Gage::SkillAdd(float Damege, int player)
{
	if (player == 0)
	{
		GageObj[8].NowSkill += Damege;
		if (GageObj[8].NowSkill > TEXTURE_GAGE3D_MAX_HP) GageObj[8].NowSkill = TEXTURE_GAGE3D_MAX_HP;
		GageObj[8].TextureSize.x = TEXTURE_GAGE_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * GageObj[8].NowSkill;
		//if (GageObj[8].TextureSize.x >= TEXTURE_GAGE_SIZE004_X)
		//{
		//	GageObj[8].TextureSize.x = TEXTURE_GAGE_SIZE004_X;
		//}
	}
	if (player == 1)
	{
		GageObj[9].NowSkill += Damege;
		if (GageObj[9].NowSkill > TEXTURE_GAGE3D_MAX_HP) GageObj[9].NowSkill = TEXTURE_GAGE3D_MAX_HP;
		GageObj[9].TextureSize.x = TEXTURE_GAGE_SIZE005_X / TEXTURE_GAGE3D_MAX_HP * GageObj[9].NowSkill;
		//if (GageObj[9].TextureSize.x >= TEXTURE_GAGE_SIZE005_X)
		//{
		//	GageObj[9].TextureSize.x = TEXTURE_GAGE_SIZE005_X;
		//}
	}
}