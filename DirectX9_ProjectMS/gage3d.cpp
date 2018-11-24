//=============================================================================
//
// プレイヤー処理 [gage3d.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "gage3d.h"
#include "character.h"
#include "camera.h"
#include "player.h"
#include <math.h>
// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBRORD_GAGE3D
#define POSITION_GAGE3D
#define MALTI_CAMERA
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Gage3d::Gage3d()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::GAGE3D, Priority::Middle, Priority::Lowest);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Gage3d::~Gage3d()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Gage3d::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_GAGE3D; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_000, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION000_X, TEXTURE_GAGE3D_POSITION000_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE000_X, TEXTURE_GAGE3D_SIZE000_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_001, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION001_X, TEXTURE_GAGE3D_POSITION001_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE001_X, TEXTURE_GAGE3D_SIZE001_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_002, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION002_X, TEXTURE_GAGE3D_POSITION002_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE002_X, TEXTURE_GAGE3D_SIZE002_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 3)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_003, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION003_X, TEXTURE_GAGE3D_POSITION003_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE003_X, TEXTURE_GAGE3D_SIZE003_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 4)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_004, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION004_X, TEXTURE_GAGE3D_POSITION004_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE004_X, TEXTURE_GAGE3D_SIZE004_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 5)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_005, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION005_X, TEXTURE_GAGE3D_POSITION005_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE005_X, TEXTURE_GAGE3D_SIZE005_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 6)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_006, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION006_X, TEXTURE_GAGE3D_POSITION006_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE006_X, TEXTURE_GAGE3D_SIZE006_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 7)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_007, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION007_X, TEXTURE_GAGE3D_POSITION007_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE007_X, TEXTURE_GAGE3D_SIZE007_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 8)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_008, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION008_X, TEXTURE_GAGE3D_POSITION008_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE008_X, TEXTURE_GAGE3D_SIZE008_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 9)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_009, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION009_X, TEXTURE_GAGE3D_POSITION009_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE009_X, TEXTURE_GAGE3D_SIZE009_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 10)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_010, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION010_X, TEXTURE_GAGE3D_POSITION010_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE010_X, TEXTURE_GAGE3D_SIZE010_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 11)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_011, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION011_X, TEXTURE_GAGE3D_POSITION011_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE011_X, TEXTURE_GAGE3D_SIZE011_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 12)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_012, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION012_X, TEXTURE_GAGE3D_POSITION012_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE012_X, TEXTURE_GAGE3D_SIZE012_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 13)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_013, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION013_X, TEXTURE_GAGE3D_POSITION013_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE013_X, TEXTURE_GAGE3D_SIZE013_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 14)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_014, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION014_X, TEXTURE_GAGE3D_POSITION014_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE014_X, TEXTURE_GAGE3D_SIZE014_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = true;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 15)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_015, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION015_X, TEXTURE_GAGE3D_POSITION015_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE015_X, TEXTURE_GAGE3D_SIZE015_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 16)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_016, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION016_X, TEXTURE_GAGE3D_POSITION016_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE016_X, TEXTURE_GAGE3D_SIZE016_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		if (i == 17)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE3D_017, &Gage3dObj[i].pD3DTexture);
			}
			Gage3dObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE3D_POSITION017_X, TEXTURE_GAGE3D_POSITION017_Y, 0.0f);
			Gage3dObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE3D_SIZE017_X, TEXTURE_GAGE3D_SIZE017_Y);
			Gage3dObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE3D_SIZEADD_X, TEXTURE_GAGE3D_SIZEADD_Y);
			Gage3dObj[i].Count = 0;
			Gage3dObj[i].Alfa = 255;
			Gage3dObj[i].Use = false;
			Gage3dObj[i].Damege = true;
			Gage3dObj[i].Texture = Gage3dObj[i].pD3DTexture;
		}
		Gage3dObj[i].Scale = D3DXVECTOR2(TEXTURE_GAGE3D_SCALE_X, TEXTURE_GAGE3D_SCALE_Y);
		Gage3dObj[i].Angle = TEXTURE_GAGE3D_ANGLE_X;
		Gage3dObj[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Gage3dObj[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Gage3dObj[i].scl = D3DXVECTOR3(1.0, 1.0, 1.0);
		Gage3dObj[i].NowHp = TEXTURE_GAGE3D_MAX_HP;
		Gage3dObj[i].NowSkill = 0.0;
		MakeVertexGage3d(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Gage3d::Uninit(void)
{
	for (int i = 0; i < NUM_GAGE3D; i++)
	{
		if (Gage3dObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			Gage3dObj[i].pD3DTexture->Release();
			Gage3dObj[i].pD3DTexture = NULL;
		}


		//if (Gage3dObj[i].pD3DXBuffMat != NULL)
		//{// マテリアルの開放
		//	Gage3dObj[i].pD3DXBuffMat->Release();
		//	Gage3dObj[i].pD3DXBuffMat = NULL;
		//}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Gage3d::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG

#endif
	
	for (int i = 0; i< NUM_GAGE3D; i++)
	{
#ifdef POSITION_GAGE3D
		if (i == 0 || i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 13 )
		{
			D3DXVECTOR3 temp1p;
			temp1p = ObjectManager::GetObjectPointer<PlayerManager>(ObjectManager::PLAYER)->GetPlayer(PlayerManager::PLAYER_1P)->GetPos();
			Gage3dObj[i].pos.x = temp1p.x;
			Gage3dObj[i].pos.y = temp1p.y + TEXTURE_GAGE3D_POSITION0UP_Y;
			Gage3dObj[i].pos.z = temp1p.z;

			if (i == 10 || i == 11 || i == 12 || i == 13)
			{
				Gage3dObj[i].pos.y = temp1p.y+ Gage3dObj[i].TextureSize.y+ TEXTURE_GAGE3D_POSITION0UP_Y;
			}
		}
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 14 || i == 15 || i == 16 || i == 17)
		{
			D3DXVECTOR3 temp2p;
			temp2p = ObjectManager::GetObjectPointer<PlayerManager>(ObjectManager::PLAYER)->GetPlayer(PlayerManager::PLAYER_2P)->GetPos();
			Gage3dObj[i].pos.x = temp2p.x;
			Gage3dObj[i].pos.y = temp2p.y + TEXTURE_GAGE3D_POSITION0UP_Y;
			Gage3dObj[i].pos.z = temp2p.z;

			if (i == 14 || i == 15 || i == 16 || i == 17)
			{
				Gage3dObj[i].pos.y = temp2p.y + Gage3dObj[i].TextureSize.y + TEXTURE_GAGE3D_POSITION0UP_Y;
			}
		}
#endif

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
			Gage3dObj[2].Use = false;
		}
		if (GetKeyboardRelease(DIK_2))
		{
			Gage3dObj[3].Use = false;
		}
		if (GetKeyboardPress(DIK_3))
		{
			SkillAdd(SKILL_000, 0);

		}
		if (GetKeyboardPress(DIK_4))
		{
			SkillAdd(SKILL_000, 1);

		}
		if (GetKeyboardPress(DIK_5))
		{
			Gage3dObj[8].TextureSize.x--;
			Gage3dObj[8].TextureSizeAdd.y -= 0.14f;

		}
		if (GetKeyboardPress(DIK_6))
		{
			Gage3dObj[9].TextureSize.x--;
			Gage3dObj[9].TextureSizeAdd.y -= 0.14f;
		}
		if (GetKeyboardPress(DIK_Q))
		{
			Gage3dObj[10].Use = true;
			Gage3dObj[11].Use = false;
			Gage3dObj[12].Use = false;
			Gage3dObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_W))
		{
			Gage3dObj[10].Use = false;
			Gage3dObj[11].Use = true;
			Gage3dObj[12].Use = false;
			Gage3dObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_E))
		{
			Gage3dObj[10].Use = false;
			Gage3dObj[11].Use = false;
			Gage3dObj[12].Use = true;
			Gage3dObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_R))
		{
			Gage3dObj[10].Use = false;
			Gage3dObj[11].Use = false;
			Gage3dObj[12].Use = false;
			Gage3dObj[13].Use = true;
		}
		if (GetKeyboardPress(DIK_A))
		{
			Gage3dObj[14].Use = true;
			Gage3dObj[15].Use = false;
			Gage3dObj[16].Use = false;
			Gage3dObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_S))
		{
			Gage3dObj[14].Use = false;
			Gage3dObj[15].Use = true;
			Gage3dObj[16].Use = false;
			Gage3dObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_D))
		{
			Gage3dObj[14].Use = false;
			Gage3dObj[15].Use = false;
			Gage3dObj[16].Use = true;
			Gage3dObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_F))
		{
			Gage3dObj[14].Use = false;
			Gage3dObj[15].Use = false;
			Gage3dObj[16].Use = false;
			Gage3dObj[17].Use = true;
		}
		if (GetKeyboardPress(DIK_Z))
		{
			Gage3dObj[i].Scale.x += 0.01;
			Gage3dObj[i].Scale.y += 0.01;

		}
		if (GetKeyboardPress(DIK_X))
		{
			Gage3dObj[i].Scale.x -= 0.01;
			Gage3dObj[i].Scale.y -= 0.01;
		}


		//	頂点カラーの設定
		SetVertexGage3d(i);
		// テクスチャ座標を設定
		SetTextureGage3d(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Gage3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int i = 0; i < NUM_GAGE3D; i++)
	{
#ifdef MALTI_CAMERA
		if (CameraManager::GetType() == CameraManager::MULTI1)
		{

			// 1Pカメラのとき
			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 14 || i == 15 || i == 16 || i == 17)
			{
#endif
				if (Gage3dObj[i].Use == true)
				{
#ifdef BILLBRORD_GAGE3D
					pDevice->GetTransform(D3DTS_VIEW, &Gage3dObj[i].mtxView);
					D3DXMatrixIdentity(&Gage3dObj[i].mtxWorld);																	//ワールドマトリクスの初期化
					Gage3dObj[i].mtxWorld._11 = Gage3dObj[i].mtxView._11;
					Gage3dObj[i].mtxWorld._12 = Gage3dObj[i].mtxView._21;
					Gage3dObj[i].mtxWorld._13 = Gage3dObj[i].mtxView._31;
					Gage3dObj[i].mtxWorld._21 = Gage3dObj[i].mtxView._12;
					Gage3dObj[i].mtxWorld._22 = Gage3dObj[i].mtxView._22;
					Gage3dObj[i].mtxWorld._23 = Gage3dObj[i].mtxView._32;
					Gage3dObj[i].mtxWorld._31 = Gage3dObj[i].mtxView._13;
					Gage3dObj[i].mtxWorld._32 = Gage3dObj[i].mtxView._23;
					Gage3dObj[i].mtxWorld._33 = Gage3dObj[i].mtxView._33;
#endif
					D3DXMatrixScaling(&mtxScl, Gage3dObj[i].scl.x, Gage3dObj[i].scl.y, Gage3dObj[i].scl.z);						//拡大を反映(拡大)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxScl);									//行列の合成(拡大)
					D3DXMatrixRotationYawPitchRoll(&mtxRot, Gage3dObj[i].rot.y, Gage3dObj[i].rot.x, Gage3dObj[i].rot.z);			//回転の反映(回転)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxRot);									//行列の合成(回転)
					D3DXMatrixTranslation(&mtxTranslate, Gage3dObj[i].pos.x, Gage3dObj[i].pos.y, Gage3dObj[i].pos.z);				//移動の反映(移動)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxTranslate);							//行列の合成(移動)
					pDevice->SetTransform(D3DTS_WORLD, &Gage3dObj[i].mtxWorld);													//ワールドマトリクスの設定
					pDevice->SetStreamSource(0, Gage3dObj[i].pD3DVtxBuff, 0, sizeof(VERTEX_3D));								//頂点バッファ
					pDevice->SetFVF(FVF_VERTEX_3D);
					pDevice->SetTexture(0, Gage3dObj[i].pD3DTexture);
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
				}
#ifdef MALTI_CAMERA
			}

		}
#endif
#ifdef MALTI_CAMERA
		if (CameraManager::GetType() == CameraManager::MULTI2)
		{

			// 2Pカメラのとき
			if (i == 0 || i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 13)
			{

				if (Gage3dObj[i].Use == true)
				{
#endif
#ifdef BILLBRORD_GAGE3D
					pDevice->GetTransform(D3DTS_VIEW, &Gage3dObj[i].mtxView);
					D3DXMatrixIdentity(&Gage3dObj[i].mtxWorld);																	//ワールドマトリクスの初期化
					Gage3dObj[i].mtxWorld._11 = Gage3dObj[i].mtxView._11;
					Gage3dObj[i].mtxWorld._12 = Gage3dObj[i].mtxView._21;
					Gage3dObj[i].mtxWorld._13 = Gage3dObj[i].mtxView._31;
					Gage3dObj[i].mtxWorld._21 = Gage3dObj[i].mtxView._12;
					Gage3dObj[i].mtxWorld._22 = Gage3dObj[i].mtxView._22;
					Gage3dObj[i].mtxWorld._23 = Gage3dObj[i].mtxView._32;
					Gage3dObj[i].mtxWorld._31 = Gage3dObj[i].mtxView._13;
					Gage3dObj[i].mtxWorld._32 = Gage3dObj[i].mtxView._23;
					Gage3dObj[i].mtxWorld._33 = Gage3dObj[i].mtxView._33;
#endif
#ifdef MALTI_CAMERA
					D3DXMatrixScaling(&mtxScl, Gage3dObj[i].scl.x, Gage3dObj[i].scl.y, Gage3dObj[i].scl.z);						//拡大を反映(拡大)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxScl);									//行列の合成(拡大)
					D3DXMatrixRotationYawPitchRoll(&mtxRot, Gage3dObj[i].rot.y, Gage3dObj[i].rot.x, Gage3dObj[i].rot.z);			//回転の反映(回転)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxRot);									//行列の合成(回転)
					D3DXMatrixTranslation(&mtxTranslate, Gage3dObj[i].pos.x, Gage3dObj[i].pos.y, Gage3dObj[i].pos.z);				//移動の反映(移動)
					D3DXMatrixMultiply(&Gage3dObj[i].mtxWorld, &Gage3dObj[i].mtxWorld, &mtxTranslate);							//行列の合成(移動)
					pDevice->SetTransform(D3DTS_WORLD, &Gage3dObj[i].mtxWorld);													//ワールドマトリクスの設定
					pDevice->SetStreamSource(0, Gage3dObj[i].pD3DVtxBuff, 0, sizeof(VERTEX_3D));								//頂点バッファ
					pDevice->SetFVF(FVF_VERTEX_3D);
					pDevice->SetTexture(0, Gage3dObj[i].pD3DTexture);
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
				}
			}

		}
#endif
	}
	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);



}
//=============================================================================
// set関数
//=============================================================================
void Gage3d::SetVertexGage3d(int CreateCount)
{
	if (CreateCount < NUM_GAGE3D)
	{
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		Gage3dObj[CreateCount].pD3DVtxBuff->Lock(0, 0, (void**)&Gage3dObj[CreateCount].pVtx, 0);

		// 頂点座標の設定(local)
		// テクスチャ座標の設定
		Gage3dObj[CreateCount].pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		Gage3dObj[CreateCount].pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		Gage3dObj[CreateCount].pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		Gage3dObj[CreateCount].pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		Gage3dObj[CreateCount].pVtx[0].vtx.x = Gage3dObj[CreateCount].Pos.x;
		Gage3dObj[CreateCount].pVtx[0].vtx.y = Gage3dObj[CreateCount].Pos.y;
		Gage3dObj[CreateCount].pVtx[0].vtx.z = Gage3dObj[CreateCount].Pos.z;
		Gage3dObj[CreateCount].pVtx[1].vtx.x = Gage3dObj[CreateCount].Pos.x + (cosf(Gage3dObj[CreateCount].Angle)*Gage3dObj[CreateCount].TextureSize.x);
		Gage3dObj[CreateCount].pVtx[1].vtx.y = Gage3dObj[CreateCount].Pos.y + (sinf(Gage3dObj[CreateCount].Angle)*Gage3dObj[CreateCount].TextureSize.x);
		Gage3dObj[CreateCount].pVtx[1].vtx.z = Gage3dObj[CreateCount].Pos.z;
		Gage3dObj[CreateCount].pVtx[2].vtx.x = Gage3dObj[CreateCount].Pos.x;
		Gage3dObj[CreateCount].pVtx[2].vtx.y = Gage3dObj[CreateCount].Pos.y - Gage3dObj[CreateCount].TextureSize.y;
		Gage3dObj[CreateCount].pVtx[2].vtx.z = Gage3dObj[CreateCount].Pos.z;
		Gage3dObj[CreateCount].pVtx[3].vtx.x = Gage3dObj[CreateCount].Pos.x + (cosf(Gage3dObj[CreateCount].Angle)*Gage3dObj[CreateCount].TextureSize.x);
		Gage3dObj[CreateCount].pVtx[3].vtx.y = Gage3dObj[CreateCount].Pos.y + (sinf(Gage3dObj[CreateCount].Angle)*Gage3dObj[CreateCount].TextureSize.x)-Gage3dObj[CreateCount].TextureSize.y;
		Gage3dObj[CreateCount].pVtx[3].vtx.z = Gage3dObj[CreateCount].Pos.z;

	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Gage3d::SetTextureGage3d(int i)
{
	if (i == 0)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT000_R, TEXTURE_GAGE3D_COLOR_DEFAULT000_G, TEXTURE_GAGE3D_COLOR_DEFAULT000_B, TEXTURE_GAGE3D_COLOR_DEFAULT000_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT000_R, TEXTURE_GAGE3D_COLOR_DEFAULT000_G, TEXTURE_GAGE3D_COLOR_DEFAULT000_B, TEXTURE_GAGE3D_COLOR_DEFAULT000_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT000_R, TEXTURE_GAGE3D_COLOR_DEFAULT000_G, TEXTURE_GAGE3D_COLOR_DEFAULT000_B, TEXTURE_GAGE3D_COLOR_DEFAULT000_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT000_R, TEXTURE_GAGE3D_COLOR_DEFAULT000_G, TEXTURE_GAGE3D_COLOR_DEFAULT000_B, TEXTURE_GAGE3D_COLOR_DEFAULT000_A);
	}
	if (i == 1)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT001_R, TEXTURE_GAGE3D_COLOR_DEFAULT001_G, TEXTURE_GAGE3D_COLOR_DEFAULT001_B, TEXTURE_GAGE3D_COLOR_DEFAULT001_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT001_R, TEXTURE_GAGE3D_COLOR_DEFAULT001_G, TEXTURE_GAGE3D_COLOR_DEFAULT001_B, TEXTURE_GAGE3D_COLOR_DEFAULT001_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT001_R, TEXTURE_GAGE3D_COLOR_DEFAULT001_G, TEXTURE_GAGE3D_COLOR_DEFAULT001_B, TEXTURE_GAGE3D_COLOR_DEFAULT001_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT001_R, TEXTURE_GAGE3D_COLOR_DEFAULT001_G, TEXTURE_GAGE3D_COLOR_DEFAULT001_B, TEXTURE_GAGE3D_COLOR_DEFAULT001_A);
	}
	if (i == 2)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
	}
	if (i == 3)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT002_R, TEXTURE_GAGE3D_COLOR_DEFAULT002_G, TEXTURE_GAGE3D_COLOR_DEFAULT002_B, TEXTURE_GAGE3D_COLOR_DEFAULT002_A);
	}
	if (i == 4)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT004_R, TEXTURE_GAGE3D_COLOR_DEFAULT004_G, TEXTURE_GAGE3D_COLOR_DEFAULT004_B, TEXTURE_GAGE3D_COLOR_DEFAULT004_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT004_R, TEXTURE_GAGE3D_COLOR_DEFAULT004_G, TEXTURE_GAGE3D_COLOR_DEFAULT004_B, TEXTURE_GAGE3D_COLOR_DEFAULT004_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT004_R, TEXTURE_GAGE3D_COLOR_DEFAULT004_G, TEXTURE_GAGE3D_COLOR_DEFAULT004_B, TEXTURE_GAGE3D_COLOR_DEFAULT004_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT004_R, TEXTURE_GAGE3D_COLOR_DEFAULT004_G, TEXTURE_GAGE3D_COLOR_DEFAULT004_B, TEXTURE_GAGE3D_COLOR_DEFAULT004_A);
	}
	if (i == 5)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT005_R, TEXTURE_GAGE3D_COLOR_DEFAULT005_G, TEXTURE_GAGE3D_COLOR_DEFAULT005_B, TEXTURE_GAGE3D_COLOR_DEFAULT005_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT005_R, TEXTURE_GAGE3D_COLOR_DEFAULT005_G, TEXTURE_GAGE3D_COLOR_DEFAULT005_B, TEXTURE_GAGE3D_COLOR_DEFAULT005_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT005_R, TEXTURE_GAGE3D_COLOR_DEFAULT005_G, TEXTURE_GAGE3D_COLOR_DEFAULT005_B, TEXTURE_GAGE3D_COLOR_DEFAULT005_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT005_R, TEXTURE_GAGE3D_COLOR_DEFAULT005_G, TEXTURE_GAGE3D_COLOR_DEFAULT005_B, TEXTURE_GAGE3D_COLOR_DEFAULT005_A);
	}
	if (i == 6)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT006_R, TEXTURE_GAGE3D_COLOR_DEFAULT006_G, TEXTURE_GAGE3D_COLOR_DEFAULT006_B, TEXTURE_GAGE3D_COLOR_DEFAULT006_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT006_R, TEXTURE_GAGE3D_COLOR_DEFAULT006_G, TEXTURE_GAGE3D_COLOR_DEFAULT006_B, TEXTURE_GAGE3D_COLOR_DEFAULT006_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT006_R, TEXTURE_GAGE3D_COLOR_DEFAULT006_G, TEXTURE_GAGE3D_COLOR_DEFAULT006_B, TEXTURE_GAGE3D_COLOR_DEFAULT006_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT006_R, TEXTURE_GAGE3D_COLOR_DEFAULT006_G, TEXTURE_GAGE3D_COLOR_DEFAULT006_B, TEXTURE_GAGE3D_COLOR_DEFAULT006_A);
	}
	if (i == 7)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT007_R, TEXTURE_GAGE3D_COLOR_DEFAULT007_G, TEXTURE_GAGE3D_COLOR_DEFAULT007_B, TEXTURE_GAGE3D_COLOR_DEFAULT007_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT007_R, TEXTURE_GAGE3D_COLOR_DEFAULT007_G, TEXTURE_GAGE3D_COLOR_DEFAULT007_B, TEXTURE_GAGE3D_COLOR_DEFAULT007_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT007_R, TEXTURE_GAGE3D_COLOR_DEFAULT007_G, TEXTURE_GAGE3D_COLOR_DEFAULT007_B, TEXTURE_GAGE3D_COLOR_DEFAULT007_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT007_R, TEXTURE_GAGE3D_COLOR_DEFAULT007_G, TEXTURE_GAGE3D_COLOR_DEFAULT007_B, TEXTURE_GAGE3D_COLOR_DEFAULT007_A);
	}
	if (i == 8)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT008_R, TEXTURE_GAGE3D_COLOR_DEFAULT008_G, TEXTURE_GAGE3D_COLOR_DEFAULT008_B, TEXTURE_GAGE3D_COLOR_DEFAULT008_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT008_R, TEXTURE_GAGE3D_COLOR_DEFAULT008_G, TEXTURE_GAGE3D_COLOR_DEFAULT008_B, TEXTURE_GAGE3D_COLOR_DEFAULT008_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT008_R, TEXTURE_GAGE3D_COLOR_DEFAULT008_G, TEXTURE_GAGE3D_COLOR_DEFAULT008_B, TEXTURE_GAGE3D_COLOR_DEFAULT008_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT008_R, TEXTURE_GAGE3D_COLOR_DEFAULT008_G, TEXTURE_GAGE3D_COLOR_DEFAULT008_B, TEXTURE_GAGE3D_COLOR_DEFAULT008_A);
	}
	if (i == 9)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT009_R, TEXTURE_GAGE3D_COLOR_DEFAULT009_G, TEXTURE_GAGE3D_COLOR_DEFAULT009_B, TEXTURE_GAGE3D_COLOR_DEFAULT009_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT009_R, TEXTURE_GAGE3D_COLOR_DEFAULT009_G, TEXTURE_GAGE3D_COLOR_DEFAULT009_B, TEXTURE_GAGE3D_COLOR_DEFAULT009_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT009_R, TEXTURE_GAGE3D_COLOR_DEFAULT009_G, TEXTURE_GAGE3D_COLOR_DEFAULT009_B, TEXTURE_GAGE3D_COLOR_DEFAULT009_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT009_R, TEXTURE_GAGE3D_COLOR_DEFAULT009_G, TEXTURE_GAGE3D_COLOR_DEFAULT009_B, TEXTURE_GAGE3D_COLOR_DEFAULT009_A);
	}
	if (i == 10)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT010_R, TEXTURE_GAGE3D_COLOR_DEFAULT010_G, TEXTURE_GAGE3D_COLOR_DEFAULT010_B, TEXTURE_GAGE3D_COLOR_DEFAULT010_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT010_R, TEXTURE_GAGE3D_COLOR_DEFAULT010_G, TEXTURE_GAGE3D_COLOR_DEFAULT010_B, TEXTURE_GAGE3D_COLOR_DEFAULT010_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT010_R, TEXTURE_GAGE3D_COLOR_DEFAULT010_G, TEXTURE_GAGE3D_COLOR_DEFAULT010_B, TEXTURE_GAGE3D_COLOR_DEFAULT010_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT010_R, TEXTURE_GAGE3D_COLOR_DEFAULT010_G, TEXTURE_GAGE3D_COLOR_DEFAULT010_B, TEXTURE_GAGE3D_COLOR_DEFAULT010_A);
	}
	if (i == 11)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT011_R, TEXTURE_GAGE3D_COLOR_DEFAULT011_G, TEXTURE_GAGE3D_COLOR_DEFAULT011_B, TEXTURE_GAGE3D_COLOR_DEFAULT011_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT011_R, TEXTURE_GAGE3D_COLOR_DEFAULT011_G, TEXTURE_GAGE3D_COLOR_DEFAULT011_B, TEXTURE_GAGE3D_COLOR_DEFAULT011_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT011_R, TEXTURE_GAGE3D_COLOR_DEFAULT011_G, TEXTURE_GAGE3D_COLOR_DEFAULT011_B, TEXTURE_GAGE3D_COLOR_DEFAULT011_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT011_R, TEXTURE_GAGE3D_COLOR_DEFAULT011_G, TEXTURE_GAGE3D_COLOR_DEFAULT011_B, TEXTURE_GAGE3D_COLOR_DEFAULT011_A);
	}
	if (i == 12)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT012_R, TEXTURE_GAGE3D_COLOR_DEFAULT012_G, TEXTURE_GAGE3D_COLOR_DEFAULT012_B, TEXTURE_GAGE3D_COLOR_DEFAULT012_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT012_R, TEXTURE_GAGE3D_COLOR_DEFAULT012_G, TEXTURE_GAGE3D_COLOR_DEFAULT012_B, TEXTURE_GAGE3D_COLOR_DEFAULT012_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT012_R, TEXTURE_GAGE3D_COLOR_DEFAULT012_G, TEXTURE_GAGE3D_COLOR_DEFAULT012_B, TEXTURE_GAGE3D_COLOR_DEFAULT012_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT012_R, TEXTURE_GAGE3D_COLOR_DEFAULT012_G, TEXTURE_GAGE3D_COLOR_DEFAULT012_B, TEXTURE_GAGE3D_COLOR_DEFAULT012_A);
	}
	if (i == 13)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT013_R, TEXTURE_GAGE3D_COLOR_DEFAULT013_G, TEXTURE_GAGE3D_COLOR_DEFAULT013_B, TEXTURE_GAGE3D_COLOR_DEFAULT013_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT013_R, TEXTURE_GAGE3D_COLOR_DEFAULT013_G, TEXTURE_GAGE3D_COLOR_DEFAULT013_B, TEXTURE_GAGE3D_COLOR_DEFAULT013_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT013_R, TEXTURE_GAGE3D_COLOR_DEFAULT013_G, TEXTURE_GAGE3D_COLOR_DEFAULT013_B, TEXTURE_GAGE3D_COLOR_DEFAULT013_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT013_R, TEXTURE_GAGE3D_COLOR_DEFAULT013_G, TEXTURE_GAGE3D_COLOR_DEFAULT013_B, TEXTURE_GAGE3D_COLOR_DEFAULT013_A);
	}
	if (i == 14)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT014_R, TEXTURE_GAGE3D_COLOR_DEFAULT014_G, TEXTURE_GAGE3D_COLOR_DEFAULT014_B, TEXTURE_GAGE3D_COLOR_DEFAULT014_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT014_R, TEXTURE_GAGE3D_COLOR_DEFAULT014_G, TEXTURE_GAGE3D_COLOR_DEFAULT014_B, TEXTURE_GAGE3D_COLOR_DEFAULT014_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT014_R, TEXTURE_GAGE3D_COLOR_DEFAULT014_G, TEXTURE_GAGE3D_COLOR_DEFAULT014_B, TEXTURE_GAGE3D_COLOR_DEFAULT014_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT014_R, TEXTURE_GAGE3D_COLOR_DEFAULT014_G, TEXTURE_GAGE3D_COLOR_DEFAULT014_B, TEXTURE_GAGE3D_COLOR_DEFAULT014_A);
	}
	if (i == 15)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT015_R, TEXTURE_GAGE3D_COLOR_DEFAULT015_G, TEXTURE_GAGE3D_COLOR_DEFAULT015_B, TEXTURE_GAGE3D_COLOR_DEFAULT015_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT015_R, TEXTURE_GAGE3D_COLOR_DEFAULT015_G, TEXTURE_GAGE3D_COLOR_DEFAULT015_B, TEXTURE_GAGE3D_COLOR_DEFAULT015_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT015_R, TEXTURE_GAGE3D_COLOR_DEFAULT015_G, TEXTURE_GAGE3D_COLOR_DEFAULT015_B, TEXTURE_GAGE3D_COLOR_DEFAULT015_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT015_R, TEXTURE_GAGE3D_COLOR_DEFAULT015_G, TEXTURE_GAGE3D_COLOR_DEFAULT015_B, TEXTURE_GAGE3D_COLOR_DEFAULT015_A);
	}
	if (i == 16)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT016_R, TEXTURE_GAGE3D_COLOR_DEFAULT016_G, TEXTURE_GAGE3D_COLOR_DEFAULT016_B, TEXTURE_GAGE3D_COLOR_DEFAULT016_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT016_R, TEXTURE_GAGE3D_COLOR_DEFAULT016_G, TEXTURE_GAGE3D_COLOR_DEFAULT016_B, TEXTURE_GAGE3D_COLOR_DEFAULT016_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT016_R, TEXTURE_GAGE3D_COLOR_DEFAULT016_G, TEXTURE_GAGE3D_COLOR_DEFAULT016_B, TEXTURE_GAGE3D_COLOR_DEFAULT016_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT016_R, TEXTURE_GAGE3D_COLOR_DEFAULT016_G, TEXTURE_GAGE3D_COLOR_DEFAULT016_B, TEXTURE_GAGE3D_COLOR_DEFAULT016_A);
	}
	if (i == 17)
	{
		Gage3dObj[i].pVtx[0].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT017_R, TEXTURE_GAGE3D_COLOR_DEFAULT017_G, TEXTURE_GAGE3D_COLOR_DEFAULT017_B, TEXTURE_GAGE3D_COLOR_DEFAULT017_A);
		Gage3dObj[i].pVtx[1].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT017_R, TEXTURE_GAGE3D_COLOR_DEFAULT017_G, TEXTURE_GAGE3D_COLOR_DEFAULT017_B, TEXTURE_GAGE3D_COLOR_DEFAULT017_A);
		Gage3dObj[i].pVtx[2].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT017_R, TEXTURE_GAGE3D_COLOR_DEFAULT017_G, TEXTURE_GAGE3D_COLOR_DEFAULT017_B, TEXTURE_GAGE3D_COLOR_DEFAULT017_A);
		Gage3dObj[i].pVtx[3].diffuse = D3DXCOLOR(TEXTURE_GAGE3D_COLOR_DEFAULT017_R, TEXTURE_GAGE3D_COLOR_DEFAULT017_G, TEXTURE_GAGE3D_COLOR_DEFAULT017_B, TEXTURE_GAGE3D_COLOR_DEFAULT017_A);
	}

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Gage3d::MakeVertexGage3d(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&Gage3dObj[i].pD3DVtxBuff,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		


		SetVertexGage3d(i);
		// 法線ベクトルの設定
		Gage3dObj[i].pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Gage3dObj[i].pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Gage3dObj[i].pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Gage3dObj[i].pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		SetTextureGage3d(i);


		// 頂点データをアンロックする
		Gage3dObj[i].pD3DVtxBuff->Unlock();
	}


}
void Gage3d ::SetGage3d(D3DXVECTOR3 Pos)
{
	for (int i = 0; i < NUM_GAGE3D; i++)
	{
		Pos = Gage3dObj[i].pos;
	}
}
void Gage3d::DamegeReduce(float Damege, int player)
{
	if (player == 0)
	{
		Gage3dObj[2].Use = true;
		Gage3dObj[4].NowHp -= Damege;
		Gage3dObj[4].TextureSize.x = TEXTURE_GAGE3D_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * Gage3dObj[4].NowHp;
		if (Gage3dObj[4].TextureSize.x <= 0.0f)
		{
			Gage3dObj[4].TextureSize.x = 0.0f;
		}
	}
	if (player == 1)
	{
		Gage3dObj[3].Use = true;
		Gage3dObj[5].NowHp -= Damege;
		Gage3dObj[5].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X / TEXTURE_GAGE3D_MAX_HP * Gage3dObj[5].NowHp;
		if (Gage3dObj[5].TextureSize.x <= 0.0f)
		{
			Gage3dObj[5].TextureSize.x = 0.0f;
		}
	}
}

void Gage3d::DamegeAdd(float Damege, int player)
{
	if (player == 0)
	{
		Gage3dObj[4].NowHp += Damege;
		Gage3dObj[4].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X / TEXTURE_GAGE3D_MAX_HP / Gage3dObj[4].NowHp;
		if (Gage3dObj[4].TextureSize.x <= TEXTURE_GAGE3D_SIZE004_X)
		{
			Gage3dObj[4].TextureSize.x = TEXTURE_GAGE3D_SIZE004_X;
		}
	}
	if (player == 1)
	{
		Gage3dObj[5].NowHp += Damege;
		Gage3dObj[5].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X / TEXTURE_GAGE3D_MAX_HP / Gage3dObj[5].NowHp;
		if (Gage3dObj[5].TextureSize.x <= TEXTURE_GAGE3D_SIZE005_X)
		{
			Gage3dObj[5].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X;
		}
	}
}
void Gage3d::SkillReduce(float Damege, int player)
{
	if (player == 0)
	{
		Gage3dObj[8].NowSkill -= Damege;
		Gage3dObj[8].TextureSize.x = TEXTURE_GAGE3D_SIZE008_X / TEXTURE_GAGE3D_MAX_HP / Gage3dObj[8].NowSkill;
		if (Gage3dObj[8].TextureSize.x < 0.0f)
		{
			Gage3dObj[8].TextureSize.x = 0.0f;
		}
	}
	if (player == 1)
	{
		Gage3dObj[9].NowSkill -= Damege;
		Gage3dObj[9].TextureSize.x = TEXTURE_GAGE3D_SIZE009_X / TEXTURE_GAGE3D_MAX_HP / Gage3dObj[9].NowSkill;
		if (Gage3dObj[9].TextureSize.x < 0.0f)
		{
			Gage3dObj[9].TextureSize.x = 0.0f;
		}
	}
}
void Gage3d::SkillAdd(float Damege, int player)
{
	if (player == 0)
	{
		Gage3dObj[8].NowSkill += Damege;
		Gage3dObj[8].TextureSize.x = TEXTURE_GAGE3D_SIZE004_X / TEXTURE_GAGE3D_MAX_HP * Gage3dObj[8].NowSkill;
		if (Gage3dObj[8].TextureSize.x >= TEXTURE_GAGE3D_SIZE004_X)
		{
			Gage3dObj[8].TextureSize.x = TEXTURE_GAGE3D_SIZE004_X;
		}
	}
	if (player == 1)
	{
		Gage3dObj[9].NowSkill += Damege;
		Gage3dObj[9].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X / TEXTURE_GAGE3D_MAX_HP * Gage3dObj[9].NowSkill;
		if (Gage3dObj[9].TextureSize.x >= TEXTURE_GAGE3D_SIZE005_X)
		{
			Gage3dObj[9].TextureSize.x = TEXTURE_GAGE3D_SIZE005_X;
		}
	}
}