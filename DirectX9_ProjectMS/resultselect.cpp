//=============================================================================
//
// プレイヤー処理 [resultselect.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "resultselect.h"
#include "character.h"
#include "joycon.h"
#include "scene.h"
#include "fade.h"
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
Resultselect::Resultselect()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::RESULTSELECT, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Resultselect::~Resultselect()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Resultselect::Init()
{
	int type = 0;
	nSelect = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < NUM_RESULTSELECT; i++)
	{
		if (i == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULTSELECT_000, &ResultselectObj[i].pD3DTexture);
			}
			ResultselectObj[i].Pos = D3DXVECTOR3(TEXTURE_RESULTSELECT_POSITION000_X, TEXTURE_RESULTSELECT_POSITION000_Y, 0.0f);
			ResultselectObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[i].Count = 0;
			ResultselectObj[i].Alfa = 255;
			ResultselectObj[i].Use = false;
			ResultselectObj[i].Nowselect = true;
			ResultselectObj[i].Texture = ResultselectObj[i].pD3DTexture;
		}
		if (i == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULTSELECT_001, &ResultselectObj[i].pD3DTexture);
			}
			ResultselectObj[i].Pos = D3DXVECTOR3(TEXTURE_RESULTSELECT_POSITION001_X, TEXTURE_RESULTSELECT_POSITION001_Y, 0.0f);
			ResultselectObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);
			ResultselectObj[i].Count = 0;
			ResultselectObj[i].Alfa = 255;
			ResultselectObj[i].Use = false;
			ResultselectObj[i].Nowselect = false;
			ResultselectObj[i].Texture = ResultselectObj[i].pD3DTexture;
		}
		if (i == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_RESULTSELECT_002, &ResultselectObj[i].pD3DTexture);
			}
			ResultselectObj[i].Pos = D3DXVECTOR3(TEXTURE_RESULTSELECT_POSITION002_X, TEXTURE_RESULTSELECT_POSITION002_Y, 0.0f);
			ResultselectObj[i].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);
			ResultselectObj[i].Count = 0;
			ResultselectObj[i].Alfa = 255;
			ResultselectObj[i].Use = false;
			ResultselectObj[i].Nowselect = false;
			ResultselectObj[i].Texture = ResultselectObj[i].pD3DTexture;
		}

		ResultselectObj[i].Scale = D3DXVECTOR2(TEXTURE_RESULTSELECT_SCALE_X, TEXTURE_RESULTSELECT_SCALE_Y);
		ResultselectObj[i].Angle = TEXTURE_RESULTSELECT_ANGLE_X;
		MakeVertexResultselect(i);
	}
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void Resultselect::Uninit(void)
{
	for (int i = 0; i < NUM_RESULTSELECT; i++)
	{
		if (ResultselectObj[i].pD3DTexture != NULL)	// (*31)
		{	// テクスチャの開放
			ResultselectObj[i].pD3DTexture->Release();
			ResultselectObj[i].pD3DTexture = NULL;
		}
	}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void Resultselect::Update(void)
{
	//CharacterManager::FIREMAN;
#ifdef _DEBUG
	PrintDebugProc("ResultselectObj[0].Alfa:%d\n", ResultselectObj[0].Alfa);
	PrintDebugProc("\n");

	PrintDebugProc("ResultselectObj[1].Alfa:%d\n", ResultselectObj[1].Alfa);
	PrintDebugProc("\n");
#endif
	for (int i = 0; i< NUM_RESULTSELECT; i++)
	{
		if (GetKeyboardTrigger(DIK_U))
		{
			ResultselectObj[i].Use = true;
		}
		if (ResultselectObj[0].Nowselect == true&& ResultselectObj[0].Count <FRAME*2)
		{
			ResultselectObj[0].Count++;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count = 0;

			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
			ResultselectObj[0].TextureSize.x += TEXTURE_RESULTSELECT_SIZE000_X/1000;
			ResultselectObj[0].TextureSize.y += TEXTURE_RESULTSELECT_SIZE000_Y/1000;
		}
		if (ResultselectObj[0].Nowselect == true && ResultselectObj[0].Count <=FRAME*4&& ResultselectObj[0].Count >=FRAME * 2)
		{
			ResultselectObj[0].Count++;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count = 0;

			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
			ResultselectObj[0].TextureSize.x -= TEXTURE_RESULTSELECT_SIZE000_X/1000;
			ResultselectObj[0].TextureSize.y -= TEXTURE_RESULTSELECT_SIZE000_Y/1000;
		}
		if (ResultselectObj[0].Nowselect == true && ResultselectObj[0].Count ==FRAME*4)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count = 0;

			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
		}
		//1
		if (ResultselectObj[1].Nowselect == true && ResultselectObj[1].Count <FRAME * 2)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count++;
			ResultselectObj[2].Count = 0;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
			ResultselectObj[1].TextureSize.x += TEXTURE_RESULTSELECT_SIZE001_X / 1000;
			ResultselectObj[1].TextureSize.y += TEXTURE_RESULTSELECT_SIZE001_Y / 1000;
		}
		if (ResultselectObj[1].Nowselect == true && ResultselectObj[1].Count <= FRAME * 4 && ResultselectObj[1].Count >= FRAME * 2)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count ++;
			ResultselectObj[2].Count = 0;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
			ResultselectObj[1].TextureSize.x -= TEXTURE_RESULTSELECT_SIZE001_X / 1000;
			ResultselectObj[1].TextureSize.y -= TEXTURE_RESULTSELECT_SIZE001_Y / 1000;
		}
		if (ResultselectObj[1].Nowselect == true && ResultselectObj[1].Count == FRAME * 4)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count = 0;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[2].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE002_X, TEXTURE_RESULTSELECT_SIZE002_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
		}
		//2
		if (ResultselectObj[2].Nowselect == true && ResultselectObj[2].Count <FRAME * 2)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count ++;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].TextureSize.x += TEXTURE_RESULTSELECT_SIZE002_X / 1000;
			ResultselectObj[2].TextureSize.y += TEXTURE_RESULTSELECT_SIZE002_Y / 1000;
		}
		if (ResultselectObj[2].Nowselect == true && ResultselectObj[2].Count <= FRAME * 4 && ResultselectObj[2].Count >= FRAME * 2)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count ++;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].TextureSize.x -= TEXTURE_RESULTSELECT_SIZE002_X / 1000;
			ResultselectObj[2].TextureSize.y -= TEXTURE_RESULTSELECT_SIZE002_Y / 1000;
		}
		if (ResultselectObj[2].Nowselect == true && ResultselectObj[2].Count == FRAME * 4)
		{
			ResultselectObj[0].Count = 0;
			ResultselectObj[1].Count = 0;
			ResultselectObj[2].Count = 0;

			ResultselectObj[0].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE000_X, TEXTURE_RESULTSELECT_SIZE000_Y);
			ResultselectObj[1].TextureSize = D3DXVECTOR2(TEXTURE_RESULTSELECT_SIZE001_X, TEXTURE_RESULTSELECT_SIZE001_Y);

			ResultselectObj[0].Nowselect = false;
			ResultselectObj[1].Nowselect = false;
		}


		if (!BaseScene::bSceneChange)
		{
			// Joyconの数だけ回す
			for (unsigned int i = 0; i < GetJoyconSize(); i++)
			{
				// 上ボタン・キーが入力されていた場合
				if (JcTriggered(i, JC_L_BUTTON_UP | JC_L_STICK_UP | JC_R_STICK_UP)
					|| GetKeyboardTrigger(DIK_UP))
				{
					// セレクトを加算
					nSelect++;
					break;
				}

				// 上ボタン・キーが入力されていた場合
				else if (JcTriggered(i, JC_L_BUTTON_DOWN | JC_L_STICK_DOWN | JC_R_STICK_DOWN)
					|| GetKeyboardTrigger(DIK_DOWN))
				{
					nSelect--;
					if (nSelect < 0) nSelect = 2;
					break;
				}

				// 決定になりえるボタンが押されている場合、遷移フラグを true
				else if (JcTriggered(i, JC_L_BUTTON_L | JC_L_BUTTON_ZL
					| JC_R_BUTTON_R | JC_R_BUTTON_ZR | JC_R_BUTTON_A)
					|| GetKeyboardTrigger(DIK_RETURN))
				{
					// 遷移フラグを true 
					BaseScene::bSceneChange = true;
					break;
				}
			}

			// セレクトされている項目のフラグを立てる
			switch (nSelect % 3)
			{
			case 0:
				ResultselectObj[0].Nowselect = true;
				ResultselectObj[1].Nowselect = false;
				ResultselectObj[2].Nowselect = false;
				break;
			case 1:
				ResultselectObj[0].Nowselect = false;
				ResultselectObj[1].Nowselect = true;
				ResultselectObj[2].Nowselect = false;
				break;
			case 2:
				ResultselectObj[0].Nowselect = false;
				ResultselectObj[1].Nowselect = false;
				ResultselectObj[2].Nowselect = true;
				break;
			}

			// 遷移フラグが true なら遷移開始
			if (BaseScene::bSceneChange)
			{
				switch (nSelect % 3)
				{
				case 0:
					SetFadeScene(SceneManager::GAME);
					break;
				case 1:
					SetFadeScene(SceneManager::SELECT);
					break;
				case 2:
					SetFadeScene(SceneManager::TITLE);
					break;
				}
			}
		}

		// デバッグ用
		if (GetKeyboardPress(DIK_Z))
		{
			ResultselectObj[0].Nowselect = true;
			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].Nowselect = false;
		}
		if (GetKeyboardPress(DIK_X))
		{
			ResultselectObj[0].Nowselect = false;
			ResultselectObj[1].Nowselect = true;
			ResultselectObj[2].Nowselect = false;
		}
		if (GetKeyboardPress(DIK_C))
		{
			ResultselectObj[0].Nowselect = false;
			ResultselectObj[1].Nowselect = false;
			ResultselectObj[2].Nowselect = true;
		}

		//	頂点カラーの設定
		SetVertexResultselect(i);
		// テクスチャ座標を設定
		SetTextureResultselect(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Resultselect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_RESULTSELECT; i++)
	{
		if (ResultselectObj[i].Use == true)
		{
			pDevice->SetTexture(0, ResultselectObj[i].pD3DTexture);


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, ResultselectObj[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Resultselect::SetVertexResultselect(int CreateCount)
{
	if (CreateCount < NUM_RESULTSELECT)
	{
		ResultselectObj[CreateCount].vertexWk[0].vtx.x = ResultselectObj[CreateCount].Pos.x - ResultselectObj[CreateCount].TextureSize.x;
		ResultselectObj[CreateCount].vertexWk[0].vtx.y = ResultselectObj[CreateCount].Pos.y - ResultselectObj[CreateCount].TextureSize.y;
		ResultselectObj[CreateCount].vertexWk[0].vtx.z = 0.0f;
		ResultselectObj[CreateCount].vertexWk[1].vtx.x = ResultselectObj[CreateCount].Pos.x + ResultselectObj[CreateCount].TextureSize.x;
		ResultselectObj[CreateCount].vertexWk[1].vtx.y = ResultselectObj[CreateCount].Pos.y - ResultselectObj[CreateCount].TextureSize.y;
		ResultselectObj[CreateCount].vertexWk[1].vtx.z = 0.0f;
		ResultselectObj[CreateCount].vertexWk[2].vtx.x = ResultselectObj[CreateCount].Pos.x - ResultselectObj[CreateCount].TextureSize.x;
		ResultselectObj[CreateCount].vertexWk[2].vtx.y = ResultselectObj[CreateCount].Pos.y + ResultselectObj[CreateCount].TextureSize.y;
		ResultselectObj[CreateCount].vertexWk[2].vtx.z = 0.0f;
		ResultselectObj[CreateCount].vertexWk[3].vtx.x = ResultselectObj[CreateCount].Pos.x + ResultselectObj[CreateCount].TextureSize.x;
		ResultselectObj[CreateCount].vertexWk[3].vtx.y = ResultselectObj[CreateCount].Pos.y + ResultselectObj[CreateCount].TextureSize.y;
		ResultselectObj[CreateCount].vertexWk[3].vtx.z = 0.0f;
	}
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Resultselect::SetTextureResultselect(int i)
{
	if (i == 0)
	{
		ResultselectObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT000_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_A);
		ResultselectObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT000_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_A);
		ResultselectObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT000_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_A);
		ResultselectObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT000_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT000_A);
	}
	if (i == 1)
	{
		ResultselectObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT001_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_A);
		ResultselectObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT001_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_A);
		ResultselectObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT001_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_A);
		ResultselectObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT001_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT001_A);
	}
	if (i == 2)
	{
		ResultselectObj[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT002_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_A);
		ResultselectObj[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT002_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_A);
		ResultselectObj[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT002_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_A);
		ResultselectObj[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_RESULTSELECT_COLOR_DEFAULT002_R, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_G, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_B, TEXTURE_RESULTSELECT_COLOR_DEFAULT002_A);
	}

}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Resultselect::MakeVertexResultselect(int i)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点座標の設定
	SetVertexResultselect(i);


	// rhwの設定
	ResultselectObj[i].vertexWk[0].rhw = 1.0f;
	ResultselectObj[i].vertexWk[1].rhw = 1.0f;
	ResultselectObj[i].vertexWk[2].rhw = 1.0f;
	ResultselectObj[i].vertexWk[3].rhw = 1.0f;

	SetTextureResultselect(i);

	ResultselectObj[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	ResultselectObj[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	ResultselectObj[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	ResultselectObj[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}