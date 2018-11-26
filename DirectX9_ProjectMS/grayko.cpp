//=============================================================================
//
// プレイヤー処理 [grayko.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "grayko.h"
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
Grayko::Grayko()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::GRAYKO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Grayko::~Grayko()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Grayko::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_GRAYKO; i++)
	{

		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GRAYKO_000, &GraykoObj[i].pD3DTexture);
			}
			GraykoObj[i].Pos = D3DXVECTOR3(TEXTURE_GRAYKO_POSITION002_X, TEXTURE_GRAYKO_POSITION002_Y, 0.0f);
			GraykoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GRAYKO_SIZE001_X, TEXTURE_GRAYKO_SIZE001_Y);
			GraykoObj[i].Count = 0;
			GraykoObj[i].Alfa = 255;
			GraykoObj[i].Use = false;
			GraykoObj[i].Nowselect = true;
			GraykoObj[i].Texture = GraykoObj[i].pD3DTexture;
		}

		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GRAYKO_000, &GraykoObj[i].pD3DTexture);
			}
			GraykoObj[i].Pos = D3DXVECTOR3(TEXTURE_GRAYKO_POSITION001_X, TEXTURE_GRAYKO_POSITION001_Y, 0.0f);
			GraykoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_GRAYKO_SIZE001_X, TEXTURE_GRAYKO_SIZE001_Y);
			GraykoObj[i].Count = 0;
			GraykoObj[i].Alfa = 255;
			GraykoObj[i].Use = false;
			GraykoObj[i].Nowselect = true;
			GraykoObj[i].Texture = GraykoObj[i].pD3DTexture;
		}


		GraykoObj[i].Scale = D3DXVECTOR2(TEXTURE_GRAYKO_SCALE_X, TEXTURE_GRAYKO_SCALE_Y);
		GraykoObj[i].Angle = TEXTURE_GRAYKO_ANGLE_X;
		MakeVertexGrayko(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Grayko::Uninit(void)
{
	for (int i = 0; i < NUM_GRAYKO; i++)
	{
		if (GraykoObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			GraykoObj[i].pD3DTexture->Release();
			GraykoObj[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Grayko::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
#endif
	for (int i = 0; i< NUM_GRAYKO; i++)
	{
		if (GetKeyboardTrigger(DIK_Y))
		{
			GraykoObj[0].Use = true;
			GraykoObj[0].Pos = D3DXVECTOR3(TEXTURE_GRAYKO_POSITION001_X, TEXTURE_GRAYKO_POSITION001_Y, 0.0f);
			GraykoObj[1].Use = false;
		}
		if (GetKeyboardTrigger(DIK_T))
		{
			GraykoObj[0].Use = false;
			GraykoObj[1].Use = true;
			GraykoObj[1].Pos = D3DXVECTOR3(TEXTURE_GRAYKO_POSITION002_X, TEXTURE_GRAYKO_POSITION002_Y, 0.0f);
		}
		//	頂点カラーの設定
		SetVertexGrayko(i);
		// テクスチャ座標を設定
		SetTextureGrayko(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Grayko::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_GRAYKO; i++)
	{
		if (GraykoObj[i].Use == true)
		{
			pDevice->SetTexture(0, GraykoObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, GraykoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Grayko::SetVertexGrayko(int CreateCount)
{
	if (CreateCount < NUM_GRAYKO)
	{
		GraykoObj[CreateCount].vertexWk[0].vtx.x = GraykoObj[CreateCount].Pos.x - GraykoObj[CreateCount].TextureSize.x;
		GraykoObj[CreateCount].vertexWk[0].vtx.y = GraykoObj[CreateCount].Pos.y - GraykoObj[CreateCount].TextureSize.y;
		GraykoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		GraykoObj[CreateCount].vertexWk[1].vtx.x = GraykoObj[CreateCount].Pos.x + GraykoObj[CreateCount].TextureSize.x;
		GraykoObj[CreateCount].vertexWk[1].vtx.y = GraykoObj[CreateCount].Pos.y - GraykoObj[CreateCount].TextureSize.y;
		GraykoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		GraykoObj[CreateCount].vertexWk[2].vtx.x = GraykoObj[CreateCount].Pos.x - GraykoObj[CreateCount].TextureSize.x;
		GraykoObj[CreateCount].vertexWk[2].vtx.y = GraykoObj[CreateCount].Pos.y + GraykoObj[CreateCount].TextureSize.y;
		GraykoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		GraykoObj[CreateCount].vertexWk[3].vtx.x = GraykoObj[CreateCount].Pos.x + GraykoObj[CreateCount].TextureSize.x;
		GraykoObj[CreateCount].vertexWk[3].vtx.y = GraykoObj[CreateCount].Pos.y + GraykoObj[CreateCount].TextureSize.y;
		GraykoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Grayko::SetTextureGrayko(int i)
{

	GraykoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAYKO_COLOR_DEFAULT000_R, TEXTURE_GRAYKO_COLOR_DEFAULT000_G, TEXTURE_GRAYKO_COLOR_DEFAULT000_B, TEXTURE_GRAYKO_COLOR_DEFAULT000_A);
	GraykoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAYKO_COLOR_DEFAULT000_R, TEXTURE_GRAYKO_COLOR_DEFAULT000_G, TEXTURE_GRAYKO_COLOR_DEFAULT000_B, TEXTURE_GRAYKO_COLOR_DEFAULT000_A);
	GraykoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAYKO_COLOR_DEFAULT000_R, TEXTURE_GRAYKO_COLOR_DEFAULT000_G, TEXTURE_GRAYKO_COLOR_DEFAULT000_B, TEXTURE_GRAYKO_COLOR_DEFAULT000_A);
	GraykoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_GRAYKO_COLOR_DEFAULT000_R, TEXTURE_GRAYKO_COLOR_DEFAULT000_G, TEXTURE_GRAYKO_COLOR_DEFAULT000_B, TEXTURE_GRAYKO_COLOR_DEFAULT000_A);
	
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Grayko::MakeVertexGrayko(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexGrayko(i);


	// rhwの設定
	GraykoObj[i].vertexWk[0].rhw = 1.0f;
	GraykoObj[i].vertexWk[1].rhw = 1.0f;
	GraykoObj[i].vertexWk[2].rhw = 1.0f;
	GraykoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureGrayko(i);

	GraykoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	GraykoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	GraykoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	GraykoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}