//=============================================================================
//
// プレイヤー処理 [gray.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "gray.h"
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
Gray::Gray()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::GRAY, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Gray::~Gray()
{
	Uninit();
}

//=============================================================================
// 初期化処理
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
// 終了処理
//=============================================================================
void Gray::Uninit(void)
{
	for (int i = 0; i < NUM_GRAY; i++)
	{
		if (GrayObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			GrayObj[i].pD3DTexture->Release();
			GrayObj[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
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
		//	頂点カラーの設定
		SetVertexGray(i);
		// テクスチャ座標を設定
		SetTextureGray(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Gray::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_GRAY; i++)
	{
		if (GrayObj[i].Use == true)
		{
			pDevice->SetTexture(0, GrayObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, GrayObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
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
// テクスチャ座標の設定 (*34)
//=============================================================================
void Gray::SetTextureGray(int i)
{

	GrayObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	GrayObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAY_COLOR_DEFAULT000_R, TEXTURE_GRAY_COLOR_DEFAULT000_G, TEXTURE_GRAY_COLOR_DEFAULT000_B, TEXTURE_GRAY_COLOR_DEFAULT000_A);
	
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Gray::MakeVertexGray(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexGray(i);


	// rhwの設定
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