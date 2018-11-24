//=============================================================================
//
// プレーン処理 [plane.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "calculate.h"
#include "shader.h"
#include "plane.h"

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
Plane::Plane()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 各ポインタの初期化
	pTexture = NULL;	// テクスチャ
	pVtxBuff = NULL;	// 頂点バッファ
	pInstBuff = NULL;	// インスタンシングバッファ
	pIdxBuff = NULL;	// インデックスバッファ
	pDecl = NULL;		// 頂点宣言

	// シェーダ関連の初期化
	pEffect = NULL;		// シェーダ

	fColor = PLANE_COLOR_MAX;
	bColor = false;

	// テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		PLANE_TEXTURE,
		&pTexture)))
	{
		// エラー
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", PLANE_TEXTURE, MB_OK);
		//return S_FALSE;
	}


	if (pEffect == NULL)
	{
		// シェーダのアドレスを取得
		pEffect = ShaderManager::GetEffect(ShaderManager::PLANE);
	}

	MakeVertex(pDevice);
}

//=============================================================================
// デストラクタ
//=============================================================================
Plane::~Plane()
{
	Release();
}

//=============================================================================
// 解放処理
//=============================================================================
void Plane::Release(void)
{
	// 解放処理
	SAFE_RELEASE(pTexture);		// テクスチャ
	SAFE_RELEASE(pVtxBuff);		// 頂点バッファ
	SAFE_RELEASE(pInstBuff);	// インスタンシングバッファ
	SAFE_RELEASE(pIdxBuff);		// インデックスバッファ
	SAFE_RELEASE(pDecl);		// 頂点宣言
	//SAFE_RELEASE(pErrorBuff);	// シェーダ用コンパイルエラー
	//SAFE_RELEASE(pEffect);		// シェーダ
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Plane::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	/***** 頂点バッファ設定 *****/

	// 頂点バッファ生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PLANE) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,									// 頂点バッファの使用法　
		0,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&pVtxBuff,							// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_PLANE *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR4(-PLANE_SIZE_X + PLANE_MARGIN, 0.0f, PLANE_SIZE_Y - PLANE_MARGIN, 1.0f);
		pVtx[1].vtx = D3DXVECTOR4(PLANE_SIZE_X - PLANE_MARGIN, 0.0f, PLANE_SIZE_Y - PLANE_MARGIN, 1.0f);
		pVtx[2].vtx = D3DXVECTOR4(-PLANE_SIZE_X + PLANE_MARGIN, 0.0f, -PLANE_SIZE_Y + PLANE_MARGIN, 1.0f);
		pVtx[3].vtx = D3DXVECTOR4(PLANE_SIZE_X - PLANE_MARGIN, 0.0f, -PLANE_SIZE_Y + PLANE_MARGIN,	1.0f);

		// テクスチャ座標の設定
		int x = 0 % PLANE_TEXTURE_PATTERN_DIVIDE_X;
		int y = 0 / PLANE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / PLANE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / PLANE_TEXTURE_PATTERN_DIVIDE_Y;

		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		pVtxBuff->Unlock();
	}


	/***** インデックスバッファ設定 *****/

	WORD wIndex[6] = { 0, 1, 2, 2, 1, 3 };

	// 座標バッファ生成
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(wIndex),						// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,									// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&pIdxBuff,							// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{// 座標バッファの中身を埋める
		WORD *pIdx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		// 頂点座標の設定
		for (unsigned int i = 0; i < 6; i++, pIdx++)
		{
			*pIdx = wIndex[i];
		}

		// 頂点データをアンロックする
		pIdxBuff->Unlock();
	}


	/***** インスタンシング用の座標バッファ設定 *****/

	// 座標バッファ生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(INSTANCE_PLANE) * PLANE_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,									// 頂点バッファの使用法　
		0,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&pInstBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	{// インスタンシングバッファの中身を埋める
		INSTANCE_PLANE *pInst;


		// 座標データの範囲をロックし、頂点バッファへのポインタを取得
		pInstBuff->Lock(0, 0, (void**)&pInst, 0);

		// 座標の設定
		for (unsigned int i = 0; i < PLANE_Y_MAX; i++)
		{
			for (unsigned int j = 0; j < PLANE_X_MAX; j++)
			{
				pInst->pos = D3DXVECTOR3(
					j * PLANE_SIZE_X * 2 - ((PLANE_X_MAX - 1) * PLANE_SIZE_X),
					0.0f,
					i * PLANE_SIZE_Y * 2 - ((PLANE_Y_MAX - 1) * PLANE_SIZE_Y));
				//pInst->diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pInst->diffuse = SetColorPalletRandomGreen();
				pInst++;
			}
		}

		// 座標データをアンロックする
		pInstBuff->Unlock();
	}


	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// VTX
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// ワールド位置
		{ 1, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// 頂点カラー
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);

	return S_OK;
}


//=============================================================================
// 描画処理
//=============================================================================
void Plane::Update(void)
{
	if (bColor)
	{
		fColor += PLANE_COLOR_SPEED;
		if (fColor > PLANE_COLOR_MAX)
		{
			bColor = false;
		}
	}
	else
	{
		fColor -= PLANE_COLOR_SPEED;
		if (fColor < -PLANE_COLOR_MAX)
		{
			bColor = true;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Plane::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビュー・プロジェクション行列を取得
	D3DXMATRIX mtxWorld, mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	//// αテストを有効に
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, EFFECT_ALPHA);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//// 加算合成に設定
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//////pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

	//// ラインティングを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// インスタンス宣言
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | PLANE_MAX);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	// 頂点とインデックスを設定
	pDevice->SetVertexDeclaration(pDecl);
	pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_PLANE));		// 頂点バッファ
	pDevice->SetStreamSource(1, pInstBuff, 0, sizeof(INSTANCE_PLANE));	// インスタンスバッファ
	pDevice->SetIndices(pIdxBuff);										// インデックスバッファ

	// 使用するテクニックを定義
	if (FAILED(pEffect->SetTechnique("Tec01")))
	{
		// エラー
		MessageBox(NULL, "テクニックの定義に失敗しました", "Tec01", MB_OK);
		//return S_FALSE;
	}

	// シェーダーの開始、numPassには指定してあるテクニックに定義してあるpassの数が変える
	UINT numPass = 0;
	pEffect->Begin(&numPass, 0);

	// パスを指定して開始
	pEffect->BeginPass(0);

	// テクスチャをセット
	pEffect->SetTexture("tex", pTexture);

	// 必要な行列情報をセット
	pEffect->SetMatrix("proj", &mtxProjection);
	pEffect->SetMatrix("view", &mtxView);
	pEffect->SetMatrix("world", &mtxWorld);

	// カラーをセット
	pEffect->SetFloat("color", fColor);

	// 結果を確定させる
	pEffect->CommitChanges();

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	// シェーダーパスを終了
	pEffect->EndPass();
	// シェーダーを終了
	pEffect->End();

	// インスタンス宣言を標準に戻す
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);

	// 固定機能に戻す
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}