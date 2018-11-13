//=============================================================================
//
// プレイヤー処理 [gage.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "gage.h"
#include "character.h"
#include <math.h>
// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Gage::Gage()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::GAGE, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Gage::~Gage()
{
	Uninit();
}

//=============================================================================
// 初期化処理
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
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_001, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION001_X, TEXTURE_GAGE_POSITION001_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE001_X, TEXTURE_GAGE_SIZE001_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_002, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION002_X, TEXTURE_GAGE_POSITION002_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE002_X, TEXTURE_GAGE_SIZE002_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 3)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_003, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION003_X, TEXTURE_GAGE_POSITION003_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE003_X, TEXTURE_GAGE_SIZE003_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 4)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_004, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION004_X, TEXTURE_GAGE_POSITION004_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE004_X, TEXTURE_GAGE_SIZE004_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 5)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_005, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION005_X, TEXTURE_GAGE_POSITION005_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE005_X, TEXTURE_GAGE_SIZE005_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 6)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_006, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION006_X, TEXTURE_GAGE_POSITION006_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE006_X, TEXTURE_GAGE_SIZE006_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 7)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_007, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION007_X, TEXTURE_GAGE_POSITION007_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE007_X, TEXTURE_GAGE_SIZE007_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 8)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_008, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION008_X, TEXTURE_GAGE_POSITION008_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE008_X, TEXTURE_GAGE_SIZE008_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 9)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_009, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION009_X, TEXTURE_GAGE_POSITION009_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE009_X, TEXTURE_GAGE_SIZE009_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
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
			GageObj[i].Use = true;
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
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_014, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION014_X, TEXTURE_GAGE_POSITION014_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE014_X, TEXTURE_GAGE_SIZE014_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = true;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 15)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_015, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION015_X, TEXTURE_GAGE_POSITION015_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE015_X, TEXTURE_GAGE_SIZE015_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 16)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_016, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION016_X, TEXTURE_GAGE_POSITION016_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE016_X, TEXTURE_GAGE_SIZE016_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		if (i == 17)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAGE_017, &GageObj[i].pD3DTexture);
			}
			GageObj[i].Pos = D3DXVECTOR3(TEXTURE_GAGE_POSITION017_X, TEXTURE_GAGE_POSITION017_Y, 0.0f);
			GageObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GAGE_SIZE017_X, TEXTURE_GAGE_SIZE017_Y);
			GageObj[i].TextureSizeAdd = D3DXVECTOR2(TEXTURE_GAGE_SIZEADD_X, TEXTURE_GAGE_SIZEADD_Y);
			GageObj[i].Count = 0;
			GageObj[i].Alfa = 255;
			GageObj[i].Use = false;
			GageObj[i].Damege = true;
			GageObj[i].Texture = GageObj[i].pD3DTexture;
		}
		GageObj[i].Scale = D3DXVECTOR2(TEXTURE_GAGE_SCALE_X, TEXTURE_GAGE_SCALE_Y);
		GageObj[i].Angle = TEXTURE_GAGE_ANGLE_X;
		MakeVertexGage(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Gage::Uninit(void)
{
	for (int i = 0; i < NUM_GAGE; i++)
	{
		if (GageObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			GageObj[i].pD3DTexture->Release();
			GageObj[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Gage::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("GageObj[0].Alfa:%d\n", GageObj[0].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("GageObj[1].Alfa:%d\n", GageObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_GAGE; i++)
	{
		
		//if (GetKeyboardPress(DIK_1))
		//{
		//	GageObj[0].TextureSize.x--;
		//}
		//if (GetKeyboardPress(DIK_2))
		//{
		//	GageObj[1].TextureSize.x--;
		//}
		//if (GetKeyboardPress(DIK_3))
		//{
		//	GageObj[2].TextureSize.x--;
		//}
		//if (GetKeyboardPress(DIK_4))
		//{
		//	GageObj[3].TextureSize.x--;
		//}
		if (GetKeyboardPress(DIK_1))
		{
			GageObj[2].Use = true;
			GageObj[4].TextureSize.x--;

		}
		if (GetKeyboardPress(DIK_2))
		{
			GageObj[3].Use = true;
			GageObj[5].TextureSize.x--;
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
			GageObj[8].TextureSize.x++;

		}
		if (GetKeyboardPress(DIK_4))
		{
			GageObj[9].TextureSize.x++;
		}
		if (GetKeyboardPress(DIK_5))
		{
			GageObj[8].TextureSize.x--;
			GageObj[8].TextureSizeAdd.y -= 0.14f;

		}
		if (GetKeyboardPress(DIK_6))
		{
			GageObj[9].TextureSize.x--;
			GageObj[9].TextureSizeAdd.y -= 0.14f;
		}
		if (GetKeyboardPress(DIK_Q))
		{
			GageObj[10].Use = true;
			GageObj[11].Use = false;
			GageObj[12].Use = false;
			GageObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_W))
		{
			GageObj[10].Use = false;
			GageObj[11].Use = true;
			GageObj[12].Use = false;
			GageObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_E))
		{
			GageObj[10].Use = false;
			GageObj[11].Use = false;
			GageObj[12].Use = true;
			GageObj[13].Use = false;
		}
		if (GetKeyboardPress(DIK_R))
		{
			GageObj[10].Use = false;
			GageObj[11].Use = false;
			GageObj[12].Use = false;
			GageObj[13].Use = true;
		}
		if (GetKeyboardPress(DIK_A))
		{
			GageObj[14].Use = true;
			GageObj[15].Use = false;
			GageObj[16].Use = false;
			GageObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_S))
		{
			GageObj[14].Use = false;
			GageObj[15].Use = true;
			GageObj[16].Use = false;
			GageObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_D))
		{
			GageObj[14].Use = false;
			GageObj[15].Use = false;
			GageObj[16].Use = true;
			GageObj[17].Use = false;
		}
		if (GetKeyboardPress(DIK_F))
		{
			GageObj[14].Use = false;
			GageObj[15].Use = false;
			GageObj[16].Use = false;
			GageObj[17].Use = true;
		}
		if (GetKeyboardPress(DIK_UP))
		{
			GageObj[i].Pos.y--;
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			GageObj[i].Pos.y++;
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			GageObj[i].Angle-=0.01;
		}
		if (GetKeyboardPress(DIK_LEFT))
		{
			GageObj[i].Angle+=0.01;
		}
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

	//	if (i == 1)
	//	{
	//		GageObj[i].Count++;
	//		if (GageObj[i].Count < FRAME)
	//		{
	//			GageObj[i].TextureSize.x -= TEXTURE_GAGE_PIXEL001_X / SCREEN_WIDTH;
	//			GageObj[i].TextureSize.y -= TEXTURE_GAGE_PIXEL001_Y / SCREEN_HEIGHT;
	//			GageObj[i].Alfa -= TEXTURE_GAGE_COLOR_DEFAULT_A /FRAME;
	//		}
	//		if (GageObj[i].Count >= FRAME && GageObj[i].Count < FRAME*2 && GageObj[i].Alfa <= TEXTURE_GAGE_COLOR_DEFAULT_A)
	//		{
	//			GageObj[i].TextureSize.x += TEXTURE_GAGE_PIXEL001_X / SCREEN_WIDTH;
	//			GageObj[i].TextureSize.y += TEXTURE_GAGE_PIXEL001_Y / SCREEN_HEIGHT;
	//			GageObj[i].Alfa += TEXTURE_GAGE_COLOR_DEFAULT_A /FRAME;
	//		}
	//		if (GageObj[i].Count >= FRAME * 2)
	//		{
	//			GageObj[i].Count = 0;
	//			GageObj[i].Alfa = TEXTURE_GAGE_COLOR_DEFAULT_A;
	//		}
	//		if (GageObj[i].Alfa >= TEXTURE_GAGE_COLOR_DEFAULT_A)
	//		{
	//			GageObj[i].Count = 0;
	//			GageObj[i].Alfa = TEXTURE_GAGE_COLOR_DEFAULT_A;
	//		}
	//	}
		//	頂点カラーの設定
		SetVertexGage(i);
		// テクスチャ座標を設定
		SetTextureGage(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Gage::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_GAGE; i++)
	{
		if (GageObj[i].Use == true)
		{
			pDevice->SetTexture(0, GageObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, GageObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
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
// テクスチャ座標の設定 (*34)
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
// 頂点の作成
//=============================================================================
HRESULT Gage::MakeVertexGage(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexGage(i);


	// rhwの設定
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