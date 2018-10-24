//=============================================================================
//
// プレイヤー処理 [selectface.cpp]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "selectface.h"
#include <math.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void SetVertexSelect(int CreateSelectCount);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect000 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect001 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect002 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect003 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect004 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect005 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect006 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect007 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect008 = NULL;							// テクスチャへのポリゴン (*33)
LPDIRECT3DTEXTURE9		g_pD3DTextureSelect009 = NULL;							// テクスチャへのポリゴン (*33)


int SelectMovePlayer000[NUM_SELECT] = { 1,0,0,0 };
int SelectMovePlayer001[NUM_SELECT] = { 1,0,0,0 };
int SelectSizeCount000 = 0;
int SelectSizeCount001 = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
Selectface::Selectface()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::SELECTFACE, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Selectface::~Selectface()
{
	Uninit();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Selectface::Init()
{
	int type = 0;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int CreateSelectCount = 0; CreateSelectCount < NUM_SELECT; CreateSelectCount++)
	{
		if (CreateSelectCount == 0)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT00, &g_pD3DTextureSelect000);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT00_POSITION_X, TEXTURE_SELECT00_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT00_SIZE_X, TEXTURE_SELECT00_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect000;
		}
		if (CreateSelectCount == 1)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT01, &g_pD3DTextureSelect001);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT01_POSITION_X, TEXTURE_SELECT01_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT01_SIZE_X, TEXTURE_SELECT01_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect001;
		}
		if (CreateSelectCount == 2)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT02, &g_pD3DTextureSelect002);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT02_POSITION_X, TEXTURE_SELECT02_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT02_SIZE_X, TEXTURE_SELECT02_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect002;
		}
		if (CreateSelectCount == 3)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT03, &g_pD3DTextureSelect003);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT03_POSITION_X, TEXTURE_SELECT03_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT03_SIZE_X, TEXTURE_SELECT03_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect003;
		}
		if (CreateSelectCount == 4)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT04, &g_pD3DTextureSelect004);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT04_POSITION_X, TEXTURE_SELECT04_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT04_SIZE_X, TEXTURE_SELECT04_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect004;
		}
		if (CreateSelectCount == 5)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT05, &g_pD3DTextureSelect005);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT05_POSITION_X, TEXTURE_SELECT05_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT05_SIZE_X, TEXTURE_SELECT05_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect005;
		}
		if (CreateSelectCount == 6)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT06, &g_pD3DTextureSelect006);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT06_POSITION_X, TEXTURE_SELECT06_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT06_SIZE_X, TEXTURE_SELECT06_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect006;
		}
		if (CreateSelectCount == 7)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT07, &g_pD3DTextureSelect007);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT07_POSITION_X, TEXTURE_SELECT07_POSITION_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT07_SIZE_X, TEXTURE_SELECT07_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect007;
		}
		if (CreateSelectCount == 8)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT08, &g_pD3DTextureSelect008);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT00_MOVE_X, TEXTURE_SELECT00_MOVE_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT08_SIZE_X, TEXTURE_SELECT08_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect008;
		}
		if (CreateSelectCount == 9)
		{
			if (type == 0)
			{
				D3DXCreateTextureFromFile(pDevice, TEXTURE_GAME_SELECT09, &g_pD3DTextureSelect009);
			}
			Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT00_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT00_MOVE_Y, 0.0f);
			Select[CreateSelectCount].TextureSelectSize = D3DXVECTOR2(TEXTURE_SELECT09_SIZE_X, TEXTURE_SELECT09_SIZE_Y);
			Select[CreateSelectCount].UseSelect = true;
			Select[CreateSelectCount].Texture = g_pD3DTextureSelect009;
		}
		// 頂点情報の作成
		MakeVertexSelect(CreateSelectCount);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Selectface::Uninit(void)
{
	if (g_pD3DTextureSelect000 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect000->Release();
		g_pD3DTextureSelect000 = NULL;
	}
	if (g_pD3DTextureSelect001 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect001->Release();
		g_pD3DTextureSelect001 = NULL;
	}
	if (g_pD3DTextureSelect002 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect002->Release();
		g_pD3DTextureSelect002 = NULL;
	}
	if (g_pD3DTextureSelect003 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect003->Release();
		g_pD3DTextureSelect003 = NULL;
	}
	if (g_pD3DTextureSelect004 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect004->Release();
		g_pD3DTextureSelect004 = NULL;
	}
	if (g_pD3DTextureSelect005 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect005->Release();
		g_pD3DTextureSelect005 = NULL;
	}
	if (g_pD3DTextureSelect006 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect006->Release();
		g_pD3DTextureSelect006 = NULL;
	}
	if (g_pD3DTextureSelect007 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect007->Release();
		g_pD3DTextureSelect007 = NULL;
	}
	if (g_pD3DTextureSelect008 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect008->Release();
		g_pD3DTextureSelect008 = NULL;
	}
	if (g_pD3DTextureSelect009 != NULL)	// (*31)
	{	// テクスチャの開放
		g_pD3DTextureSelect009->Release();
		g_pD3DTextureSelect009 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Selectface::Update(void)
{

	for (int CreateSelectCount = 0; CreateSelectCount < NUM_SELECT; CreateSelectCount++)
	{
		if (CreateSelectCount == 8)
		{
			SelectSizeCount000++;
		}
		if (CreateSelectCount == 8 && SelectSizeCount000 <=FRAME/4)
		{
			//y=x^2
			Select[CreateSelectCount].TextureSelectSize.x += TEXTURE_SELECT08_SIZE_MOVE_X * TEXTURE_SELECT08_SIZE_MOVE_OFFSET_X;
			Select[CreateSelectCount].TextureSelectSize.y += TEXTURE_SELECT08_SIZE_MOVE_Y * TEXTURE_SELECT08_SIZE_MOVE_OFFSET_Y;
		}
		if (CreateSelectCount == 8 && SelectSizeCount000 <=FRAME/2 && SelectSizeCount000>FRAME/4)
		{
			Select[CreateSelectCount].TextureSelectSize.x -= TEXTURE_SELECT08_SIZE_MOVE_X * TEXTURE_SELECT08_SIZE_MOVE_OFFSET_X;
			Select[CreateSelectCount].TextureSelectSize.y -= TEXTURE_SELECT08_SIZE_MOVE_Y * TEXTURE_SELECT08_SIZE_MOVE_OFFSET_Y;
		}
		if (CreateSelectCount == 8 && SelectSizeCount000 > FRAME /2)
		{
			SelectSizeCount000 = 0;
		}

		if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonPressed(0, BUTTON_LEFT))
		{
			if (CreateSelectCount == 8 && SelectMovePlayer000[0]==1)
			{
				SelectMovePlayer000[0] = 0;
				SelectMovePlayer000[1] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT01_MOVE_X, TEXTURE_SELECT01_MOVE_Y, 0.0f);
				break;
			}
			if (CreateSelectCount == 8 && SelectMovePlayer000[1] == 1)
			{
				SelectMovePlayer000[1] = 0;
				SelectMovePlayer000[2] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT02_MOVE_X, TEXTURE_SELECT02_MOVE_Y, 0.0f);
				break;
			}
			if (CreateSelectCount == 8 && SelectMovePlayer000[2] == 1)
			{
				SelectMovePlayer000[2] = 0;
				SelectMovePlayer000[3] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT03_MOVE_X, TEXTURE_SELECT03_MOVE_Y, 0.0f);
				break;
			}
		}
		if (GetKeyboardTrigger(DIK_LEFT) || IsButtonPressed(0, BUTTON_LEFT))
		{
			if (CreateSelectCount == 8 && SelectMovePlayer000[1] == 1)
			{
				SelectMovePlayer000[0] = 1;
				SelectMovePlayer000[1] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT00_MOVE_X, TEXTURE_SELECT00_MOVE_Y, 0.0f);
			}
			if (CreateSelectCount == 8 && SelectMovePlayer000[2] == 1)
			{
				SelectMovePlayer000[1] = 1;
				SelectMovePlayer000[2] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT01_MOVE_X, TEXTURE_SELECT01_MOVE_Y, 0.0f);
			}
			if (CreateSelectCount == 8 && SelectMovePlayer000[3] == 1)
			{
				SelectMovePlayer000[2] = 1;
				SelectMovePlayer000[3] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT02_MOVE_X, TEXTURE_SELECT02_MOVE_Y, 0.0f);
			}
		}


		if (CreateSelectCount == 9)
		{
			SelectSizeCount001++;
		}
		if (CreateSelectCount == 9 && SelectSizeCount001 <= FRAME / 4)
		{
			//y=x^2
			Select[CreateSelectCount].TextureSelectSize.x += TEXTURE_SELECT09_SIZE_MOVE_X * TEXTURE_SELECT09_SIZE_MOVE_OFFSET_X;
			Select[CreateSelectCount].TextureSelectSize.y += TEXTURE_SELECT09_SIZE_MOVE_Y * TEXTURE_SELECT09_SIZE_MOVE_OFFSET_Y;
		}
		if (CreateSelectCount == 9 && SelectSizeCount001 <= FRAME / 2 && SelectSizeCount001>FRAME / 4)
		{
			Select[CreateSelectCount].TextureSelectSize.x -= TEXTURE_SELECT09_SIZE_MOVE_X * TEXTURE_SELECT09_SIZE_MOVE_OFFSET_X;
			Select[CreateSelectCount].TextureSelectSize.y -= TEXTURE_SELECT09_SIZE_MOVE_Y * TEXTURE_SELECT09_SIZE_MOVE_OFFSET_Y;
		}
		if (CreateSelectCount == 9 && SelectSizeCount001 > FRAME / 2)
		{
			SelectSizeCount001 = 0;
		}

		if (GetKeyboardTrigger(DIK_D) || IsButtonPressed(0, BUTTON_LEFT))
		{
			if (CreateSelectCount == 9 && SelectMovePlayer001[0] == 1)
			{
				SelectMovePlayer001[0] = 0;
				SelectMovePlayer001[1] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT01_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT01_MOVE_Y, 0.0f);
				break;
			}
			if (CreateSelectCount == 9 && SelectMovePlayer001[1] == 1)
			{
				SelectMovePlayer001[1] = 0;
				SelectMovePlayer001[2] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT02_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT02_MOVE_Y, 0.0f);
				break;
			}
			if (CreateSelectCount == 9 && SelectMovePlayer001[2] == 1)
			{
				SelectMovePlayer001[2] = 0;
				SelectMovePlayer001[3] = 1;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT03_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT03_MOVE_Y, 0.0f);
				break;
			}
		}
		if (GetKeyboardTrigger(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))
		{
			if (CreateSelectCount == 9 && SelectMovePlayer001[1] == 1)
			{
				SelectMovePlayer001[0] = 1;
				SelectMovePlayer001[1] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT00_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT00_MOVE_Y, 0.0f);
			}
			if (CreateSelectCount == 9 && SelectMovePlayer001[2] == 1)
			{
				SelectMovePlayer001[1] = 1;
				SelectMovePlayer001[2] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT01_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT01_MOVE_Y, 0.0f);
			}
			if (CreateSelectCount == 9 && SelectMovePlayer001[3] == 1)
			{
				SelectMovePlayer001[2] = 1;
				SelectMovePlayer001[3] = 0;
				Select[CreateSelectCount].posSelect = D3DXVECTOR3(TEXTURE_SELECT02_MOVE_X+ TEXTURE_SELECT_MOVE_DISTANCE_X, TEXTURE_SELECT02_MOVE_Y, 0.0f);
			}
		}

		//	頂点カラーの設定
		SetVertexSelect(CreateSelectCount);
		// テクスチャ座標を設定
		SetTextureSelect(CreateSelectCount);
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void Selectface::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//SELECT *Select = GetSelect(0);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int CreateSelectCount = 0; CreateSelectCount < NUM_SELECT; CreateSelectCount++)
	{
		if (Select[CreateSelectCount].UseSelect == true)
		{
			if (CreateSelectCount == 0) { pDevice->SetTexture(0, g_pD3DTextureSelect000); }
			if (CreateSelectCount == 1) { pDevice->SetTexture(0, g_pD3DTextureSelect001); }
			if (CreateSelectCount == 2) { pDevice->SetTexture(0, g_pD3DTextureSelect002); }
			if (CreateSelectCount == 3) { pDevice->SetTexture(0, g_pD3DTextureSelect003); }
			if (CreateSelectCount == 4) { pDevice->SetTexture(0, g_pD3DTextureSelect004); }
			if (CreateSelectCount == 5) { pDevice->SetTexture(0, g_pD3DTextureSelect005); }
			if (CreateSelectCount == 6) { pDevice->SetTexture(0, g_pD3DTextureSelect006); }
			if (CreateSelectCount == 7) { pDevice->SetTexture(0, g_pD3DTextureSelect007); }
			if (CreateSelectCount == 8) { pDevice->SetTexture(0, g_pD3DTextureSelect008); }
			if (CreateSelectCount == 9) { pDevice->SetTexture(0, g_pD3DTextureSelect009); }


			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Select[CreateSelectCount].vertexSelectWk, sizeof(VERTEX_2D));
		}
	}
}
//=============================================================================
// set関数
//=============================================================================
void Selectface::SetVertexSelect(int CreateSelectCount)
{

	if (CreateSelectCount == 0 && SelectMovePlayer000[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 0 && SelectMovePlayer001[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 0 && SelectMovePlayer000[0] == 0 && SelectMovePlayer001[0] == 0)
	{
			Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
			Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
			Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
			Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
			Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 1 && SelectMovePlayer000[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 1 && SelectMovePlayer001[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 1 && SelectMovePlayer000[1] == 0 && SelectMovePlayer001[1] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 2 && SelectMovePlayer000[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 2 && SelectMovePlayer001[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 2 && SelectMovePlayer000[2] == 0 && SelectMovePlayer001[2] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 3 && SelectMovePlayer000[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 3 && SelectMovePlayer001[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 3 && SelectMovePlayer000[3] == 0 && SelectMovePlayer001[3] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 4 && SelectMovePlayer000[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 4 && SelectMovePlayer001[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 4 && SelectMovePlayer000[0] == 0 && SelectMovePlayer001[0] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 5 && SelectMovePlayer000[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 5 && SelectMovePlayer001[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 5 && SelectMovePlayer000[1] == 0 && SelectMovePlayer001[1] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 6 && SelectMovePlayer000[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 6 && SelectMovePlayer001[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 6 && SelectMovePlayer000[2] == 0 && SelectMovePlayer001[2] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 7 && SelectMovePlayer000[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 7 && SelectMovePlayer001[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
	if (CreateSelectCount == 7 && SelectMovePlayer000[3] == 0 && SelectMovePlayer001[3] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_BASE_X);
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}

	//if (CreateSelectCount < 8)
	//{
	//	Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
	//	Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
	//	Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
	//	Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + (Select[CreateSelectCount].TextureSelectSize.x*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + (Select[CreateSelectCount].TextureSelectSize.y*TEXTURE_SELECT_SIZE_VERTEX_X);
	//	Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	//}
	if (CreateSelectCount >= 8)
	{
		Select[CreateSelectCount].vertexSelectWk[0].vtx.x = Select[CreateSelectCount].posSelect.x - Select[CreateSelectCount].TextureSelectSize.x;
		Select[CreateSelectCount].vertexSelectWk[0].vtx.y = Select[CreateSelectCount].posSelect.y - Select[CreateSelectCount].TextureSelectSize.y;
		Select[CreateSelectCount].vertexSelectWk[0].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.x = Select[CreateSelectCount].posSelect.x + Select[CreateSelectCount].TextureSelectSize.x;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.y = Select[CreateSelectCount].posSelect.y - Select[CreateSelectCount].TextureSelectSize.y;
		Select[CreateSelectCount].vertexSelectWk[1].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.x = Select[CreateSelectCount].posSelect.x - Select[CreateSelectCount].TextureSelectSize.x;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.y = Select[CreateSelectCount].posSelect.y + Select[CreateSelectCount].TextureSelectSize.y;
		Select[CreateSelectCount].vertexSelectWk[2].vtx.z = 0.0f;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.x = Select[CreateSelectCount].posSelect.x + Select[CreateSelectCount].TextureSelectSize.x;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.y = Select[CreateSelectCount].posSelect.y + Select[CreateSelectCount].TextureSelectSize.y;
		Select[CreateSelectCount].vertexSelectWk[3].vtx.z = 0.0f;
	}
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Selectface::MakeVertexSelect(int CreateSelectCount)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//SELECT *Select = GetSelect(0);

	// 頂点座標の設定
	SetVertexSelect(CreateSelectCount);
	//// rhwの設定
	//Select[CreateSelectCount].vertexSelectWk[0].rhw = 1.0f;
	//Select[CreateSelectCount].vertexSelectWk[1].rhw = 1.0f;
	//Select[CreateSelectCount].vertexSelectWk[2].rhw = 1.0f;
	//Select[CreateSelectCount].vertexSelectWk[3].rhw = 1.0f;


	// 反射光の設定 (*33)
	if (CreateSelectCount < 8)
	{
		// rhwの設定
		Select[CreateSelectCount].vertexSelectWk[0].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[1].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[2].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[3].rhw = 1.0f;

		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);

		// テクスチャ座標の設定 (*33)
		Select[CreateSelectCount].vertexSelectWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		Select[CreateSelectCount].vertexSelectWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		Select[CreateSelectCount].vertexSelectWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		Select[CreateSelectCount].vertexSelectWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	if (CreateSelectCount >= 8)
	{
		// rhwの設定
		Select[CreateSelectCount].vertexSelectWk[0].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[1].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[2].rhw = 1.0f;
		Select[CreateSelectCount].vertexSelectWk[3].rhw = 1.0f;

		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);

		// テクスチャ座標の設定 (*33)
		Select[CreateSelectCount].vertexSelectWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		Select[CreateSelectCount].vertexSelectWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		Select[CreateSelectCount].vertexSelectWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		Select[CreateSelectCount].vertexSelectWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}




	//// テクスチャ座標の設定 (*33)
	//Select[CreateSelectCount].vertexSelectWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//Select[CreateSelectCount].vertexSelectWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//Select[CreateSelectCount].vertexSelectWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//Select[CreateSelectCount].vertexSelectWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Selectface::SetTextureSelect(int CreateSelectCount)
{

	if (CreateSelectCount == 0&& SelectMovePlayer000[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 0 && SelectMovePlayer001[0] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 0 && SelectMovePlayer000[0] == 0&& SelectMovePlayer001[0] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
	}


	if (CreateSelectCount == 1 && SelectMovePlayer000[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 1 && SelectMovePlayer001[1] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 1 && SelectMovePlayer000[1] == 0 && SelectMovePlayer001[1] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
	}

	if (CreateSelectCount == 2 && SelectMovePlayer000[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 2 && SelectMovePlayer001[2] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 2 && SelectMovePlayer000[2] == 0&& SelectMovePlayer001[2] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
	}

	if (CreateSelectCount == 3 && SelectMovePlayer000[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 3 && SelectMovePlayer001[3] == 1)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}
	if (CreateSelectCount == 3 && SelectMovePlayer000[3] == 0&& SelectMovePlayer001[3] == 0)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
	}
	// 反射光の設定 (*33)
	if (CreateSelectCount < 8&& CreateSelectCount >= 4)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_DEFAULT_R,TEXTURE_SELECT_COLOR_DEFAULT_G,TEXTURE_SELECT_COLOR_DEFAULT_B,TEXTURE_SELECT_COLOR_DEFAULT_A);
	}
	if (CreateSelectCount >= 8)
	{
		Select[CreateSelectCount].vertexSelectWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
		Select[CreateSelectCount].vertexSelectWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_SELECT_COLOR_CHANGE_R,TEXTURE_SELECT_COLOR_CHANGE_G,TEXTURE_SELECT_COLOR_CHANGE_B,TEXTURE_SELECT_COLOR_CHANGE_A);
	}

}
////=============================================================================
////SELECT *GetSelect関数
////=============================================================================
//Selectface *Selectface::GetSelect(int Number)
//{
//	return (&Select[Number]);
//}