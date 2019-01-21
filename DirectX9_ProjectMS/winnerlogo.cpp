//=============================================================================
//
// プレイヤー処理 [winnerlogo.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "winnerlogo.h"
#include "character.h"
#include "sound.h"

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
Winnerlogo::Winnerlogo()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::WINNERLOGO, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Winnerlogo::~Winnerlogo()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Winnerlogo::Init()
{
	int type = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_WINNERLOGO; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_WINNERLOGO_000, &WinnerlogoObj[i].pD3DTexture);
			}
			WinnerlogoObj[i].Pos = D3DXVECTOR3(TEXTURE_WINNERLOGO_POSITION000_X, TEXTURE_WINNERLOGO_POSITION000_Y, 0.0f);
			WinnerlogoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_WINNERLOGO_SIZE000_X, TEXTURE_WINNERLOGO_SIZE000_Y);
			WinnerlogoObj[i].Count = 0;
			WinnerlogoObj[i].Alfa = 255;
			WinnerlogoObj[i].Color = 0;
			WinnerlogoObj[i].Use = false;
			WinnerlogoObj[i].Nowselect = false;
			WinnerlogoObj[i].Texture = WinnerlogoObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			WinnerlogoObj[i].Pos = D3DXVECTOR3(TEXTURE_WINNERLOGO_POSITION001_X, TEXTURE_WINNERLOGO_POSITION001_Y, 0.0f);
			WinnerlogoObj[i].TextureSize = D3DXVECTOR2(TEXTURE_WINNERLOGO_SIZE001_X, TEXTURE_WINNERLOGO_SIZE001_Y);
			WinnerlogoObj[i].Count = 0;
			WinnerlogoObj[i].Alfa = 255;
			WinnerlogoObj[i].Color = 255;
			WinnerlogoObj[i].Use = false;
			WinnerlogoObj[i].Nowselect = false;
			WinnerlogoObj[i].Texture = WinnerlogoObj[0].pD3DTexture;
		}
		WinnerlogoObj[i].Scale = D3DXVECTOR2(TEXTURE_WINNERLOGO_SCALE_X, TEXTURE_WINNERLOGO_SCALE_Y);
		WinnerlogoObj[i].Angle = TEXTURE_WINNERLOGO_ANGLE_X;
		MakeVertexWinnerlogo(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Winnerlogo::Uninit(void)
{
	for (int i = 0; i < NUM_WINNERLOGO; i++)
	{
		if (i == 0 || i == 1)
		{
			if (WinnerlogoObj[0].pD3DTexture != NULL)	// (*31)
			{	// テクスチャの開放
				WinnerlogoObj[0].pD3DTexture->Release();
				WinnerlogoObj[0].pD3DTexture = NULL;
			}
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Winnerlogo::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
#endif
	for (int i = 0; i< NUM_WINNERLOGO; i++)
	{
		if (GetKeyboardTrigger(DIK_1))
		{
			WinnerlogoObj[i].Nowselect = true;
		}
		if (WinnerlogoObj[i].Nowselect == true)
		{

			Starttime();
		}
		if (GetKeyboardTrigger(DIK_U))
		{
			WinnerlogoObj[0].Use = false;
			WinnerlogoObj[1].Use = false;
		}

		//	頂点カラーの設定
		SetVertexWinnerlogo(i);
		// テクスチャ座標を設定
		SetTextureWinnerlogo(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Winnerlogo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_WINNERLOGO; i++)
	{
		if (WinnerlogoObj[i].Use == true)
		{
			if (i == 0 || i == 1)
			{
				pDevice->SetTexture(0, WinnerlogoObj[0].pD3DTexture);
			}

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, WinnerlogoObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Winnerlogo::SetVertexWinnerlogo(int CreateCount)
{
	if (CreateCount < NUM_WINNERLOGO)
	{
		WinnerlogoObj[CreateCount].vertexWk[0].vtx.x = WinnerlogoObj[CreateCount].Pos.x - WinnerlogoObj[CreateCount].TextureSize.x;
		WinnerlogoObj[CreateCount].vertexWk[0].vtx.y = WinnerlogoObj[CreateCount].Pos.y - WinnerlogoObj[CreateCount].TextureSize.y;
		WinnerlogoObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		WinnerlogoObj[CreateCount].vertexWk[1].vtx.x = WinnerlogoObj[CreateCount].Pos.x + WinnerlogoObj[CreateCount].TextureSize.x;
		WinnerlogoObj[CreateCount].vertexWk[1].vtx.y = WinnerlogoObj[CreateCount].Pos.y - WinnerlogoObj[CreateCount].TextureSize.y;
		WinnerlogoObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		WinnerlogoObj[CreateCount].vertexWk[2].vtx.x = WinnerlogoObj[CreateCount].Pos.x - WinnerlogoObj[CreateCount].TextureSize.x;
		WinnerlogoObj[CreateCount].vertexWk[2].vtx.y = WinnerlogoObj[CreateCount].Pos.y + WinnerlogoObj[CreateCount].TextureSize.y;
		WinnerlogoObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		WinnerlogoObj[CreateCount].vertexWk[3].vtx.x = WinnerlogoObj[CreateCount].Pos.x + WinnerlogoObj[CreateCount].TextureSize.x;
		WinnerlogoObj[CreateCount].vertexWk[3].vtx.y = WinnerlogoObj[CreateCount].Pos.y + WinnerlogoObj[CreateCount].TextureSize.y;
		WinnerlogoObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Winnerlogo::SetTextureWinnerlogo(int i)
{

	WinnerlogoObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA((int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Alfa);
	WinnerlogoObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA((int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Alfa);
	WinnerlogoObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA((int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Alfa);
	WinnerlogoObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA((int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Color, (int)WinnerlogoObj[i].Alfa);

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Winnerlogo::MakeVertexWinnerlogo(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexWinnerlogo(i);


	// rhwの設定
	WinnerlogoObj[i].vertexWk[0].rhw = 1.0f;
	WinnerlogoObj[i].vertexWk[1].rhw = 1.0f;
	WinnerlogoObj[i].vertexWk[2].rhw = 1.0f;
	WinnerlogoObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureWinnerlogo(i);

	WinnerlogoObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	WinnerlogoObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	WinnerlogoObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	WinnerlogoObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
void Winnerlogo::Starttime(void)
{
	WinnerlogoObj[0].Use = true;
	WinnerlogoObj[1].Use = true;
	if (WinnerlogoObj[1].Use == true)
	{
		if (WinnerlogoObj[1].Count < WINNER_TIME)
		{
			WinnerlogoObj[1].Count++;
			WinnerlogoObj[1].Pos.x -= (TEXTURE_WINNERLOGO_POSITION001_X - WinnerlogoObj[0].Pos.x) / (WINNER_TIME);
		}
		if (WinnerlogoObj[1].Count == WINNER_TIME)
		{
			WinnerlogoObj[1].Count++;
			SetVoice(VOICE_YOUWIN, E_DS8_FLAG_NONE, SOUND_OPTION_CONTINUE_ON, 0);
			WinnerlogoObj[1].Pos = WinnerlogoObj[0].Pos;
		}
	}
}

//=============================================================================
// セット処理
//=============================================================================
void Winnerlogo::Set(void)
{
	for (int i = 0; i < NUM_WINNERLOGO; i++)
	{
		WinnerlogoObj[i].Nowselect = true;
	}
}
