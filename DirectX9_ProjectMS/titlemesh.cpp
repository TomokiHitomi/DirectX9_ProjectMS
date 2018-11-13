////=============================================================================
////
//// プレイヤー処理 [titlemesh.cpp]
//// Author : GP12A295 09 樺澤広之
////
////=============================================================================
//#include "main.h"
//#include "input.h"
//#include "titlemesh.h"
//#include <math.h>
//// デバッグ用
//#ifdef _DEBUG
//#include "debugproc.h"
//#endif
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//
////=============================================================================
//// コンストラクタ
////=============================================================================
//Titlemesh::Titlemesh()
//{
//	// オブジェクトIDとプライオリティの設定処理
//	SetIdAndPriority(ObjectID::TITLEMESH, Priority::Middle, Priority::Lowest);
//
//	Init();
//}
//
////=============================================================================
//// デストラクタ
////=============================================================================
//Titlemesh::~Titlemesh()
//{
//	Uninit();
//}
//
////=============================================================================
//// 初期化処理
////=============================================================================
//HRESULT Titlemesh::Init()
//{
//	//int type = 0;
//	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	//for (int i = 0; i < NUM_TITLEMESH; i++)
//	//{
//	//	if (i == 0)
//	//	{
//	//		if (type == 0)
//	//		{
//	//			D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLEMESH_000, &Title[i].pD3DTexture);
//	//		}
//	//		Title[i].Pos = D3DXVECTOR3(TEXTURE_TITLEMESH_POSITION000_X, TEXTURE_TITLEMESH_POSITION000_Y, 0.0f);
//	//		Title[i].TextureSize = D3DXVECTOR2(TEXTURE_TITLEMESH_SIZE000_X, TEXTURE_TITLEMESH_SIZE000_Y);
//	//		Title[i].Count = 0;
//	//		Title[i].Alfa = 255;
//	//		Title[i].Use = true;
//	//		Title[i].Texture = Title[i].pD3DTexture;
//	//	}
//	//}
//	//return S_OK;
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//
//	// ポリゴン表示位置の中心座標を設定
//	TitleMesh->Pos=D3DXVECTOR3(TEXTURE_TITLEMESH_POSITION000_X, TEXTURE_TITLEMESH_POSITION000_Y, TEXTURE_TITLEMESH_POSITION000_Z);
//	TitleMesh->Rot= D3DXVECTOR3(TEXTURE_TITLEMESH_ROTATION000_X, TEXTURE_TITLEMESH_ROTATION000_Y, TEXTURE_TITLEMESH_ROTATION000_Z);
//	// ブロック数の設定
//	TitleMesh->NumBlockX=FIELD_NUM_X;
//	TitleMesh->NumBlockZ=FIELD_NUM_Z;
//
//	// テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLEMESH_000,&TitleMesh->pD3DTexture);
//
//
//	// 頂点数の設定
//	TitleMesh->NumVertex = (TitleMesh->NumBlockX + 1) * (TitleMesh->NumBlockZ + 1);
//
//	// インデックス数の設定
//	TitleMesh->NumVertexIndex = (TitleMesh->NumBlockX + 1) * 2 * TitleMesh->NumBlockZ + (TitleMesh->NumBlockZ - 1) * 2;
//
//	// ポリゴン数の設定
//	TitleMesh->NumPolygon = TitleMesh->NumBlockX * TitleMesh->NumBlockZ * 2 + (TitleMesh->NumBlockZ - 1) * 4;
//
//	// ブロックサイズの設定
//	TitleMesh->BlockSizeX = TitleMesh->BlockSizeX;
//	TitleMesh->BlockSizeZ = TitleMesh->BlockSizeZ;
//
//	// オブジェクトの頂点バッファを生成
//	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * TitleMesh->NumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
//		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
//		FVF_VERTEX_3D,						// 使用する頂点フォーマット
//		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
//		&TitleMesh->pD3DVtxBuff,				// 頂点バッファインターフェースへのポインタ
//		NULL)))								// NULLに設定
//	{
//		return E_FAIL;
//	}
//
//	// オブジェクトのインデックスバッファを生成
//	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) *TitleMesh->NumVertexIndex,		// 頂点データ用に確保するバッファサイズ(バイト単位)
//		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
//		D3DFMT_INDEX16,						// 使用するインデックスフォーマット
//		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
//		&TitleMesh->pD3DIdxBuff,				// インデックスバッファインターフェースへのポインタ
//		NULL)))								// NULLに設定
//	{
//		return E_FAIL;
//	}
//
//	{//頂点バッファの中身を埋める
//		VERTEX_3D *pVtx;
//#if 0
//		const float texSizeX = 1.0f / g_nNumBlockX;
//		const float texSizeZ = 1.0f / g_nNumBlockZ;
//#else
//		const float texSizeX = 1.0f;
//		const float texSizeZ = 1.0f;
//#endif
//
//		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
//		TitleMesh->pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//		for (int nCntVtxZ = 0; nCntVtxZ < (TitleMesh->NumBlockZ + 1); nCntVtxZ++)
//		{
//			for (int nCntVtxX = 0; nCntVtxX < (TitleMesh->NumBlockX + 1); nCntVtxX++)
//			{
//				// 頂点座標の設定
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.x = -(TitleMesh->NumBlockX / 2.0f) * TitleMesh->BlockSizeX + nCntVtxX * TitleMesh->BlockSizeX;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.y = 0.0f;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.z = (TitleMesh->NumBlockZ / 2.0f) * TitleMesh->BlockSizeZ - nCntVtxZ * TitleMesh->BlockSizeZ;
//
//				// 法線の設定
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);
//
//				// 反射光の設定
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//				// テクスチャ座標の設定
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
//			}
//		}
//
//		// 頂点データをアンロックする
//		TitleMesh->pD3DVtxBuff->Unlock();
//	}
//
//	{//インデックスバッファの中身を埋める
//		WORD *pIdx;
//
//		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
//		TitleMesh->pD3DIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
//
//		int nCntIdx = 0;
//		for (int nCntVtxZ = 0; nCntVtxZ < TitleMesh->NumBlockZ; nCntVtxZ++)
//		{
//			if (nCntVtxZ > 0)
//			{// 縮退ポリゴンのためのダブりの設定
//				pIdx[nCntIdx] = (nCntVtxZ + 1) * (TitleMesh->NumBlockX + 1);
//				nCntIdx++;
//			}
//
//			for (int nCntVtxX = 0; nCntVtxX < (TitleMesh->NumBlockX + 1); nCntVtxX++)
//			{
//				pIdx[nCntIdx] = (nCntVtxZ + 1) * (TitleMesh->NumBlockX + 1) + nCntVtxX;
//				nCntIdx++;
//				pIdx[nCntIdx] = nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX;
//				nCntIdx++;
//			}
//
//			if (nCntVtxZ < (TitleMesh->NumBlockZ - 1))
//			{// 縮退ポリゴンのためのダブりの設定
//				pIdx[nCntIdx] = nCntVtxZ * (TitleMesh->NumBlockX + 1) + TitleMesh->NumBlockX;
//				nCntIdx++;
//			}
//		}
//
//		// インデックスデータをアンロックする
//		TitleMesh->pD3DIdxBuff->Unlock();
//	}
//
//	return S_OK;
//
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void Titlemesh::Uninit(void)
//{
//	for (int i = 0; i < NUM_TITLEMESH; i++)
//	{
//		if (TitleMesh.pD3DTexture != NULL)	// (*31)
//		{	// テクスチャの開放
//			TitleMesh.pD3DTexture->Release();
//			TitleMesh.pD3DTexture = NULL;
//		}
//	}
//	
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void Titlemesh::Update(void)
//{
//#ifdef _DEBUG
//	PrintDebugProc("Title[0].Alfa:%d\n", Title[0].Alfa);
//	PrintDebugProc("\n");
//
//	PrintDebugProc("Title[1].Alfa:%d\n", Title[1].Alfa);
//	PrintDebugProc("\n");
//#endif
//	for (int i = 0; i< NUM_TITLEMESH; i++)
//	{
//		if (GetKeyboardPress(DIK_DOWN))
//		{
//			Title[0].Pos.y--;
//		}
//		if (GetKeyboardPress(DIK_UP))
//		{
//			Title[0].Pos.y++;
//		}
//
//		//	頂点カラーの設定
//		SetVertexTitlemesh(i);
//		// テクスチャ座標を設定
//		SetTextureTitlemesh(i);
//	}
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void Titlemesh::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int i = 0; i < NUM_TITLEMESH; i++)
//	{
//		if (TitleMesh.Use == true)
//		{
//			pDevice->SetTexture(0, TitleMesh.pD3DTexture);
//
//
//			// ポリゴンの描画
//			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, TitleMesh.vertexWk, sizeof(VERTEX_2D));
//		}
//	}
//}
////=============================================================================
//// set関数
////=============================================================================
//void Titlemesh::SetVertexTitlemesh(int CreateCount)
//{
//
//	if (CreateCount == 0)
//	{
//		Title[CreateCount].vertexWk[0].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[0].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[0].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[1].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[1].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[1].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[2].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[2].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[2].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[3].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[3].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[3].vtx.z = 0.0f;
//	}
//	if (CreateCount == 1)
//	{
//		Title[CreateCount].vertexWk[0].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[0].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[0].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[1].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[1].vtx.y = Title[CreateCount].Pos.y - Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[1].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[2].vtx.x = Title[CreateCount].Pos.x - Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[2].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[2].vtx.z = 0.0f;
//		Title[CreateCount].vertexWk[3].vtx.x = Title[CreateCount].Pos.x + Title[CreateCount].TextureSize.x;
//		Title[CreateCount].vertexWk[3].vtx.y = Title[CreateCount].Pos.y + Title[CreateCount].TextureSize.y;
//		Title[CreateCount].vertexWk[3].vtx.z = 0.0f;
//	}
//}
//
////=============================================================================
//// テクスチャ座標の設定 (*34)
////=============================================================================
//void Titlemesh::SetTextureTitlemesh(int i)
//{
//	if (i == 0)
//	{
//		TitleMesh.vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//		TitleMesh.vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//		TitleMesh.vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//		TitleMesh.vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//	}
//	if (i == 1)
//	{
//		TitleMesh.vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, Title[1].Alfa);
//		TitleMesh.vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, Title[1].Alfa);
//		TitleMesh.vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, Title[1].Alfa);
//		TitleMesh.vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, Title[1].Alfa);
//	}
//
//}
////=============================================================================
//// 頂点の作成
////=============================================================================
//HRESULT Titlemesh::MakeVertexTitlemesh(int i)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//	// 頂点座標の設定
//	SetVertexTitlemesh(i);
//
//
//	// rhwの設定
//	TitleMesh.vertexWk[0].rhw = 1.0f;
//	TitleMesh.vertexWk[1].rhw = 1.0f;
//	TitleMesh.vertexWk[2].rhw = 1.0f;
//	TitleMesh.vertexWk[3].rhw = 1.0f;
//
//	TitleMesh.vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//	TitleMesh.vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//	TitleMesh.vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//	TitleMesh.vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_TITLEMESH_COLOR_DEFAULT_R, TEXTURE_TITLEMESH_COLOR_DEFAULT_G, TEXTURE_TITLEMESH_COLOR_DEFAULT_B, TEXTURE_TITLEMESH_COLOR_DEFAULT_A);
//	
//	TitleMesh.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	TitleMesh.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//	TitleMesh.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//	Title[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//	
//	return S_OK;
//}
