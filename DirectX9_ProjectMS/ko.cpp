//=============================================================================
//
// プレイヤー処理 [ko.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "ko.h"
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
Ko::Ko()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::KO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Ko::~Ko()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Ko::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_KO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_KO_000, &KoObj[i].pD3DTexture);
			}
			KoObj[i].Pos = D3DXVECTOR3(TEXTURE_KO_POSITION000_X, TEXTURE_KO_POSITION000_Y, 0.0f);
			KoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_KO_SIZE000_X, TEXTURE_KO_SIZE000_Y);
			KoObj[i].Count = 0;
			KoObj[i].Alfa = 255;
			KoObj[i].Color = 255;
			KoObj[i].Use = false;
			KoObj[i].Nowselect = false;
			KoObj[i].Texture = KoObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			KoObj[i].Pos = D3DXVECTOR3(TEXTURE_KO_POSITION001_X, TEXTURE_KO_POSITION001_Y, 0.0f);
			KoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_KO_SIZE001_X, TEXTURE_KO_SIZE001_Y);
			KoObj[i].Count = 0;
			KoObj[i].Alfa = 255;
			KoObj[i].Color = 255;
			KoObj[i].Use = false;
			KoObj[i].Nowselect = false;
			KoObj[i].Texture = KoObj[0].pD3DTexture;
		}
		KoObj[i].Scale = D3DXVECTOR2(TEXTURE_KO_SCALE_X, TEXTURE_KO_SCALE_Y);
		KoObj[i].Angle = TEXTURE_KO_ANGLE_X;
		MakeVertexKo(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Ko::Uninit(void)
{
	for (int i = 0; i < NUM_KO; i++)
	{
		if (i == 0 || i == 1)
		{
			if (KoObj[0].pD3DTexture != NULL)	// (*31)
			{	// テクスチャの開放
				KoObj[0].pD3DTexture->Release();
				KoObj[0].pD3DTexture = NULL;
			}
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Ko::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("KoObj[2].Alfa:%d\n", KoObj[2].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("KoObj[1].Alfa:%d\n", KoObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_KO; i++)
	{
		if (GetKeyboardTrigger(DIK_T))
		{
			KoObj[0].Use = true;
			KoObj[0].Nowselect = true;
			KoObj[0].Color = 255;
			KoObj[1].Use = true;
			KoObj[1].Nowselect = true;
			KoObj[1].Color = 0;
		}
		if (GetKeyboardTrigger(DIK_Y))
		{
			KoObj[0].Use = true;
			KoObj[0].Nowselect = true;
			KoObj[0].Color = 0;
			KoObj[1].Use = true;
			KoObj[1].Nowselect = true;
			KoObj[1].Color = 255;
		}
		//	頂点カラーの設定
		SetVertexKo(i);
		// テクスチャ座標を設定
		SetTextureKo(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Ko::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_KO; i++)
	{
		if (KoObj[i].Use == true)
		{
			if (i == 0 || i == 1)
			{
				pDevice->SetTexture(0, KoObj[0].pD3DTexture);
			}

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, KoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Ko::SetVertexKo(int CreateCount)
{
	if (CreateCount < NUM_KO)
	{
		KoObj[CreateCount].vertexWk[0].vtx.x = KoObj[CreateCount].Pos.x - KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[0].vtx.y = KoObj[CreateCount].Pos.y - KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[1].vtx.x = KoObj[CreateCount].Pos.x + KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[1].vtx.y = KoObj[CreateCount].Pos.y - KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[2].vtx.x = KoObj[CreateCount].Pos.x - KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[2].vtx.y = KoObj[CreateCount].Pos.y + KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		KoObj[CreateCount].vertexWk[3].vtx.x = KoObj[CreateCount].Pos.x + KoObj[CreateCount].TextureSize.x;
		KoObj[CreateCount].vertexWk[3].vtx.y = KoObj[CreateCount].Pos.y + KoObj[CreateCount].TextureSize.y;
		KoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Ko::SetTextureKo(int i)
{

	KoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);
	KoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Color, (int)KoObj[i].Alfa);

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Ko::MakeVertexKo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexKo(i);


	// rhwの設定
	KoObj[i].vertexWk[0].rhw = 1.0f;
	KoObj[i].vertexWk[1].rhw = 1.0f;
	KoObj[i].vertexWk[2].rhw = 1.0f;
	KoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureKo(i);

	KoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	KoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	KoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	KoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}