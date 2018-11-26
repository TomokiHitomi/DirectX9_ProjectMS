//=============================================================================
//
// プレイヤー処理 [timeuplogo.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "timeuplogo.h"
#include "character.h"

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
Timeuplogo::Timeuplogo()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::TIMEUPLOGO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Timeuplogo::~Timeuplogo()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Timeuplogo::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_TIMEUPLOGO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_TIMEUPLOGO_000, &TimeuplogoObj[i].pD3DTexture);
			}
			TimeuplogoObj[i].Pos = D3DXVECTOR3(TEXTURE_TIMEUPLOGO_POSITION000_X, TEXTURE_TIMEUPLOGO_POSITION000_Y, 0.0f);
			TimeuplogoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_TIMEUPLOGO_SIZE000_X, TEXTURE_TIMEUPLOGO_SIZE000_Y);
			TimeuplogoObj[i].Count = 0;
			TimeuplogoObj[i].Alfa = 255;
			TimeuplogoObj[i].Color = 255;
			TimeuplogoObj[i].Use = false;
			TimeuplogoObj[i].Nowselect = 0;
			TimeuplogoObj[i].Texture = TimeuplogoObj[i].pD3DTexture;
		}

		TimeuplogoObj[i].Scale = D3DXVECTOR2(TEXTURE_TIMEUPLOGO_SCALE_X, TEXTURE_TIMEUPLOGO_SCALE_Y);
		TimeuplogoObj[i].Angle = TEXTURE_TIMEUPLOGO_ANGLE_X;
		MakeVertexTimeuplogo(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Timeuplogo::Uninit(void)
{
	for (int i = 0; i < NUM_TIMEUPLOGO; i++)
	{
		if (TimeuplogoObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			TimeuplogoObj[i].pD3DTexture->Release();
			TimeuplogoObj[i].pD3DTexture = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Timeuplogo::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
#endif
	for (int i = 0; i< NUM_TIMEUPLOGO; i++)
	{
		if (GetKeyboardTrigger(DIK_I))
		{
			TimeuplogoObj[0].Use = true;
			TimeuplogoObj[0].Nowselect = 0;
			TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		}
		if (GetKeyboardTrigger(DIK_O))
		{
			TimeuplogoObj[0].Use = false;
		}
		//if (GetKeyboardTrigger(DIK_G))
		//{
		//	TimeuplogoObj[0].Use = true;
		//	TimeuplogoObj[0].Nowselect = 0;
		//}
		//if (GetKeyboardTrigger(DIK_H))
		//{
		//	TimeuplogoObj[0].Use = true;
		//	TimeuplogoObj[0].Nowselect = 1;
		//}
		//if (GetKeyboardTrigger(DIK_J))
		//{
		//	TimeuplogoObj[0].Use = true;
		//	TimeuplogoObj[0].Nowselect = 2;
		//}
		//if (TimeuplogoObj[0].Use == true)
		//{
		//	TimeuplogoObj[0].Count++;
		//	TimeuplogoObj[0].TextureSize.x -= TEXTURE_TIMEUPLOGO_SIZE000_X / TEXTURE_TIMEUPLOGO_TIME_000;
		//	TimeuplogoObj[0].TextureSize.y -= TEXTURE_TIMEUPLOGO_SIZE000_Y / TEXTURE_TIMEUPLOGO_TIME_000;
		//}
		//if (TimeuplogoObj[0].Count < TEXTURE_TIMEUPLOGO_TIME_000&&TimeuplogoObj[0].Nowselect == 0)
		//{
		//	TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		//}
		//if (TimeuplogoObj[0].Count < TEXTURE_TIMEUPLOGO_TIME_000&&TimeuplogoObj[0].Nowselect == 1)
		//{
		//	TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		//}
		//if (TimeuplogoObj[0].Count < TEXTURE_TIMEUPLOGO_TIME_000&&TimeuplogoObj[0].Nowselect == 2)
		//{
		//	TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		//}
		//if (TimeuplogoObj[0].Count > TEXTURE_TIMEUPLOGO_TIME_000&&TimeuplogoObj[0].Nowselect == 3)
		//{
		//	TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		//}
		//if (TimeuplogoObj[0].Count == TEXTURE_TIMEUPLOGO_TIME_000)
		//{
		//	TimeuplogoObj[0].Nowselect = 3;
		//	TexTimeuplogo(i, TimeuplogoObj[0].Nowselect);
		//	TimeuplogoObj[0].TextureSize = D3DXVECTOR2(TEXTURE_TIMEUPLOGO_SIZE000_X, TEXTURE_TIMEUPLOGO_SIZE000_Y);
		//	//TimeuplogoObj[0].Count = 0;
		//	//TimeuplogoObj[0].Use = false;
		//}
		//if (TimeuplogoObj[0].Count == TEXTURE_TIMEUPLOGO_TIME_000 * 2)
		//{
		//	TimeuplogoObj[0].TextureSize = D3DXVECTOR2(TEXTURE_TIMEUPLOGO_SIZE000_X, TEXTURE_TIMEUPLOGO_SIZE000_Y);
		//	TimeuplogoObj[0].Nowselect = 3;
		//	TimeuplogoObj[0].Count = 0;
		//	TimeuplogoObj[0].Use = false;
		//}


		//	頂点カラーの設定
		SetVertexTimeuplogo(i);
		// テクスチャ座標を設定
		SetTextureTimeuplogo(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Timeuplogo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_TIMEUPLOGO; i++)
	{
		if (TimeuplogoObj[i].Use == true)
		{
			pDevice->SetTexture(0, TimeuplogoObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, TimeuplogoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Timeuplogo::SetVertexTimeuplogo(int CreateCount)
{
	if (CreateCount < NUM_TIMEUPLOGO)
	{
		TimeuplogoObj[CreateCount].vertexWk[0].vtx.x = TimeuplogoObj[CreateCount].Pos.x - TimeuplogoObj[CreateCount].TextureSize.x;
		TimeuplogoObj[CreateCount].vertexWk[0].vtx.y = TimeuplogoObj[CreateCount].Pos.y - TimeuplogoObj[CreateCount].TextureSize.y;
		TimeuplogoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		TimeuplogoObj[CreateCount].vertexWk[1].vtx.x = TimeuplogoObj[CreateCount].Pos.x + TimeuplogoObj[CreateCount].TextureSize.x;
		TimeuplogoObj[CreateCount].vertexWk[1].vtx.y = TimeuplogoObj[CreateCount].Pos.y - TimeuplogoObj[CreateCount].TextureSize.y;
		TimeuplogoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		TimeuplogoObj[CreateCount].vertexWk[2].vtx.x = TimeuplogoObj[CreateCount].Pos.x - TimeuplogoObj[CreateCount].TextureSize.x;
		TimeuplogoObj[CreateCount].vertexWk[2].vtx.y = TimeuplogoObj[CreateCount].Pos.y + TimeuplogoObj[CreateCount].TextureSize.y;
		TimeuplogoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		TimeuplogoObj[CreateCount].vertexWk[3].vtx.x = TimeuplogoObj[CreateCount].Pos.x + TimeuplogoObj[CreateCount].TextureSize.x;
		TimeuplogoObj[CreateCount].vertexWk[3].vtx.y = TimeuplogoObj[CreateCount].Pos.y + TimeuplogoObj[CreateCount].TextureSize.y;
		TimeuplogoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Timeuplogo::SetTextureTimeuplogo(int i)
{

	TimeuplogoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Alfa);
	TimeuplogoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Alfa);
	TimeuplogoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Alfa);
	TimeuplogoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Color, (int)TimeuplogoObj[i].Alfa);

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Timeuplogo::MakeVertexTimeuplogo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexTimeuplogo(i);


	// rhwの設定
	TimeuplogoObj[i].vertexWk[0].rhw = 1.0f;
	TimeuplogoObj[i].vertexWk[1].rhw = 1.0f;
	TimeuplogoObj[i].vertexWk[2].rhw = 1.0f;
	TimeuplogoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureTimeuplogo(i);
	TexTimeuplogo(i,0);
	//TimeuplogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//TimeuplogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//TimeuplogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//TimeuplogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
void Timeuplogo::TexTimeuplogo(int i,int flag)
{
	if (flag == 0)
	{
		TimeuplogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		TimeuplogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		TimeuplogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		TimeuplogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}

//=============================================================================
// タイムアップ設置処理
//=============================================================================
void Timeuplogo::Set(bool bUse)
{
	if (bUse)
	{
		TimeuplogoObj[0].Use = true;
		TimeuplogoObj[0].Nowselect = 0;
		TexTimeuplogo(0, TimeuplogoObj[0].Nowselect);
	}
	else
	{
		TimeuplogoObj[0].Use = false;
	}
}