//=============================================================================
//
// プレイヤー処理 [roundlogo.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "roundlogo.h"
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
Roundlogo::Roundlogo()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::ROUNDLOGO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Roundlogo::~Roundlogo()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Roundlogo::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_ROUNDLOGO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_ROUNDLOGO_000, &RoundlogoObj[i].pD3DTexture);
			}
			RoundlogoObj[i].Pos = D3DXVECTOR3(TEXTURE_ROUNDLOGO_POSITION000_X, TEXTURE_ROUNDLOGO_POSITION000_Y, 0.0f);
			RoundlogoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_ROUNDLOGO_SIZE000_X, TEXTURE_ROUNDLOGO_SIZE000_Y);
			RoundlogoObj[i].Count = 0;
			RoundlogoObj[i].Alfa = 255;
			RoundlogoObj[i].Color = 255;
			RoundlogoObj[i].Use = false;
			RoundlogoObj[i].Nowselect = 0;
			RoundlogoObj[i].Texture = RoundlogoObj[i].pD3DTexture;
		}

		RoundlogoObj[i].Scale = D3DXVECTOR2(TEXTURE_ROUNDLOGO_SCALE_X, TEXTURE_ROUNDLOGO_SCALE_Y);
		RoundlogoObj[i].Angle = TEXTURE_ROUNDLOGO_ANGLE_X;
		MakeVertexRoundlogo(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Roundlogo::Uninit(void)
{
	for (int i = 0; i < NUM_ROUNDLOGO; i++)
	{
		if (RoundlogoObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			RoundlogoObj[i].pD3DTexture->Release();
			RoundlogoObj[i].pD3DTexture = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Roundlogo::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
#endif
	for (int i = 0; i< NUM_ROUNDLOGO; i++)
	{
		//if (GetKeyboardTrigger(DIK_1))
		//{
		//	RoundlogoObj[0].Use = true;
		//	RoundlogoObj[1].Use = true;
		//}
		//if (RoundlogoObj[1].Use == true)
		//{
		//	if (RoundlogoObj[1].Count < FRAME/2)
		//	{
		//		RoundlogoObj[1].Count++;
		//		RoundlogoObj[1].Pos.x -= (TEXTURE_ROUNDLOGO_POSITION001_X -RoundlogoObj[0].Pos.x) / (FRAME/2);
		//	}
		//	if (RoundlogoObj[1].Count == FRAME/2)
		//	{
		//		RoundlogoObj[1].Pos = RoundlogoObj[0].Pos;
		//	}
		//}
		//if (GetKeyboardTrigger(DIK_U))
		//{
		//	RoundlogoObj[0].Use = false;
		//	RoundlogoObj[1].Use = false;
		//}
		if (GetKeyboardTrigger(DIK_G))
		{
			RoundlogoObj[0].Use = true;
			RoundlogoObj[0].Nowselect = 0;
		}
		if (GetKeyboardTrigger(DIK_H))
		{
			RoundlogoObj[0].Use = true;
			RoundlogoObj[0].Nowselect = 1;
		}
		if (GetKeyboardTrigger(DIK_J))
		{
			RoundlogoObj[0].Use = true;
			RoundlogoObj[0].Nowselect = 2;
		}
		if (RoundlogoObj[0].Use == true)
		{
			RoundlogoObj[0].Count++;
			RoundlogoObj[0].TextureSize.x -= TEXTURE_ROUNDLOGO_SIZE000_X / TEXTURE_ROUNDLOGO_TIME_000;
			RoundlogoObj[0].TextureSize.y -= TEXTURE_ROUNDLOGO_SIZE000_Y / TEXTURE_ROUNDLOGO_TIME_000;
		}
		if (RoundlogoObj[0].Count < TEXTURE_ROUNDLOGO_TIME_000&&RoundlogoObj[0].Nowselect == 0)
		{
			TexRoundlogo(i, RoundlogoObj[0].Nowselect);
		}
		if (RoundlogoObj[0].Count < TEXTURE_ROUNDLOGO_TIME_000&&RoundlogoObj[0].Nowselect == 1)
		{
			TexRoundlogo(i, RoundlogoObj[0].Nowselect);
		}
		if (RoundlogoObj[0].Count < TEXTURE_ROUNDLOGO_TIME_000&&RoundlogoObj[0].Nowselect == 2)
		{
			TexRoundlogo(i, RoundlogoObj[0].Nowselect);
		}
		if (RoundlogoObj[0].Count > TEXTURE_ROUNDLOGO_TIME_000&&RoundlogoObj[0].Nowselect == 3)
		{
			TexRoundlogo(i, RoundlogoObj[0].Nowselect);
		}
		if (RoundlogoObj[0].Count == TEXTURE_ROUNDLOGO_TIME_000)
		{
			RoundlogoObj[0].Nowselect = 3;
			TexRoundlogo(i, RoundlogoObj[0].Nowselect);
			RoundlogoObj[0].TextureSize = D3DXVECTOR2(TEXTURE_ROUNDLOGO_SIZE000_X, TEXTURE_ROUNDLOGO_SIZE000_Y);
			//RoundlogoObj[0].Count = 0;
			//RoundlogoObj[0].Use = false;
		}
		if (RoundlogoObj[0].Count == TEXTURE_ROUNDLOGO_TIME_000 * 2)
		{
			RoundlogoObj[0].TextureSize = D3DXVECTOR2(TEXTURE_ROUNDLOGO_SIZE000_X, TEXTURE_ROUNDLOGO_SIZE000_Y);
			RoundlogoObj[0].Nowselect = 3;
			RoundlogoObj[0].Count = 0;
			RoundlogoObj[0].Use = false;
		}


		//	頂点カラーの設定
		SetVertexRoundlogo(i);
		// テクスチャ座標を設定
		SetTextureRoundlogo(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Roundlogo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_ROUNDLOGO; i++)
	{
		if (RoundlogoObj[i].Use == true)
		{
			pDevice->SetTexture(0, RoundlogoObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, RoundlogoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Roundlogo::SetVertexRoundlogo(int CreateCount)
{
	if (CreateCount < NUM_ROUNDLOGO)
	{
		RoundlogoObj[CreateCount].vertexWk[0].vtx.x = RoundlogoObj[CreateCount].Pos.x - RoundlogoObj[CreateCount].TextureSize.x;
		RoundlogoObj[CreateCount].vertexWk[0].vtx.y = RoundlogoObj[CreateCount].Pos.y - RoundlogoObj[CreateCount].TextureSize.y;
		RoundlogoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		RoundlogoObj[CreateCount].vertexWk[1].vtx.x = RoundlogoObj[CreateCount].Pos.x + RoundlogoObj[CreateCount].TextureSize.x;
		RoundlogoObj[CreateCount].vertexWk[1].vtx.y = RoundlogoObj[CreateCount].Pos.y - RoundlogoObj[CreateCount].TextureSize.y;
		RoundlogoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		RoundlogoObj[CreateCount].vertexWk[2].vtx.x = RoundlogoObj[CreateCount].Pos.x - RoundlogoObj[CreateCount].TextureSize.x;
		RoundlogoObj[CreateCount].vertexWk[2].vtx.y = RoundlogoObj[CreateCount].Pos.y + RoundlogoObj[CreateCount].TextureSize.y;
		RoundlogoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		RoundlogoObj[CreateCount].vertexWk[3].vtx.x = RoundlogoObj[CreateCount].Pos.x + RoundlogoObj[CreateCount].TextureSize.x;
		RoundlogoObj[CreateCount].vertexWk[3].vtx.y = RoundlogoObj[CreateCount].Pos.y + RoundlogoObj[CreateCount].TextureSize.y;
		RoundlogoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Roundlogo::SetTextureRoundlogo(int i)
{

	RoundlogoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Alfa);
	RoundlogoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Alfa);
	RoundlogoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Alfa);
	RoundlogoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Color, (int)RoundlogoObj[i].Alfa);

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Roundlogo::MakeVertexRoundlogo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexRoundlogo(i);


	// rhwの設定
	RoundlogoObj[i].vertexWk[0].rhw = 1.0f;
	RoundlogoObj[i].vertexWk[1].rhw = 1.0f;
	RoundlogoObj[i].vertexWk[2].rhw = 1.0f;
	RoundlogoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureRoundlogo(i);
	TexRoundlogo(i,0);
	//RoundlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//RoundlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//RoundlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//RoundlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
void Roundlogo::TexRoundlogo(int i,int flag)
{
	if (flag == 0)
	{
		RoundlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		RoundlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		RoundlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		RoundlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 0.25f);
	}
	if (flag == 1)
	{
		RoundlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.25f);
		RoundlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.25f);
		RoundlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		RoundlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 0.5f);
	}
	if (flag == 2)
	{
		RoundlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		RoundlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.5f);
		RoundlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 0.75f);
		RoundlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 0.75f);
	}
	if (flag == 3)
	{
		RoundlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.75f);
		RoundlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.75f);
		RoundlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		RoundlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
}

//=============================================================================
// ラウンドセット関数
//=============================================================================
void Roundlogo::Set(int nRound)
{
	RoundlogoObj[0].Use = true;
	RoundlogoObj[0].Nowselect = nRound;
}

//=============================================================================
// 使用フラグ取得関数
//=============================================================================
bool Roundlogo::GetUse(void)
{
	return RoundlogoObj[0].Use;
}