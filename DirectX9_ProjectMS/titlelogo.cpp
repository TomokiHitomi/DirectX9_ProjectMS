//=============================================================================
//
// プレイヤー処理 [titlelogo.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "titlelogo.h"
#include <math.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pD3DTextureTitlelogo000 = NULL;							// テクスチャへのポリゴン (*33)

//=============================================================================
// コンストラクタ
//=============================================================================
Titlelogo::Titlelogo()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::TITLELOGO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Titlelogo::~Titlelogo()
{
	Uninit();
}

//=============================================================================
// 初期化処理
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
			Title[i].Use = true;
			Title[i].Texture = Title[i].pD3DTexture;
		}
		MakeVertexTitlelogo(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Titlelogo::Uninit(void)
{
	for (int i = 0; i < NUM_TITLELOGO; i++)
	{
		if (Title[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			Title[i].pD3DTexture->Release();
			Title[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Titlelogo::Update(void)
{
	for (int i = 0; i< NUM_TITLELOGO; i++)
	{
		if (i == 1)
		{

			
			if (Title[1].Count < FRAME)
			{
				Title[1].Count++;
				Title[1].Alfa -= 255 / FRAME;
			}
			if (Title[1].Count >= FRAME && Title[1].Count < FRAME * 2)
			{
				Title[1].Count++;
				Title[1].Alfa += 255 / FRAME;
			}
			if (Title[1].Count >= FRAME * 2)
			{
				Title[1].Count = 0;
				Title[1].Alfa = 255;
			}
		}
		//	頂点カラーの設定
		SetVertexTitlelogo(i);
		// テクスチャ座標を設定
		SetTextureTitlelogo(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Titlelogo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_TITLELOGO; i++)
	{
		if (Title[i].Use == true)
		{
			pDevice->SetTexture(0, Title[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Title[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
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
// テクスチャ座標の設定 (*34)
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
// 頂点の作成
//=============================================================================
HRESULT Titlelogo::MakeVertexTitlelogo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexTitlelogo(i);


	// rhwの設定
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