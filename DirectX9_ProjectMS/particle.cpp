//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "particle.h"
#include "input.h"
#include "calculate.h"
#include "camera.h"

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
ParticleManager::ParticleManager()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::PARTICLE, Priority::Middle, Priority::Middle);

	// パーティクルの初期化
	pParticle = NULL;

	// 初期化処理
	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
ParticleManager::~ParticleManager()
{
	// 解放処理
	Release();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT ParticleManager::Init(void)
{
	pParticle = new Particle;
	return S_OK;
}

//=============================================================================
// 解放処理
//=============================================================================
void ParticleManager::Release(void)
{
	// 解放処理
	SAFE_DELETE(pParticle);
}

//=============================================================================
// 更新処理
//=============================================================================
void ParticleManager::Update(void)
{
	SAFE_UPDATE(pParticle);
}

//=============================================================================
// 描画処理
//=============================================================================
void ParticleManager::Draw(void)
{
	SAFE_DRAW(pParticle);
}



//=============================================================================
// コンストラクタ
//=============================================================================
Particle::Particle()
{
	// 各ポインタの初期化
	pTexture = NULL;	// テクスチャ
	pVtxBuff = NULL;	// 頂点バッファ
	pInstBuff = NULL;	// インスタンシングバッファ
	pIdxBuff = NULL;	// インデックスバッファ
	pDecl = NULL;		// 頂点宣言

	// シェーダ関連の初期化
	pErrorBuff = NULL;	// シェーダ用コンパイルエラー
	pEffect = NULL;		// シェーダ
	numPass = 0;

	// カウンタの初期化
	nCount = 0;

	// カラー指定の初期化
	nColor = 0;

	// 移動量の初期化
	fMove = 0.0f;

	// 初期化処理
	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Particle::~Particle()
{
	// 解放処理
	Release();
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Particle::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* path = PARTICLE_SHADER_FILE;
	// ファイル( const char* path )からシェーダーファイルを読み込み読み込み
	if (FAILED(D3DXCreateEffectFromFile(
		pDevice, path, 0, 0, 0, 0, &pEffect, &pErrorBuff)))
	{
		// エラー
		MessageBox(NULL, "シェーダファイルの読み込みに失敗しました", path, MB_OK);
		return S_FALSE;
	}

	// 使用するテクニックを定義
	if (FAILED(pEffect->SetTechnique("Tec01")))
	{
		// エラー
		MessageBox(NULL, "テクニックの定義に失敗しました", "Tec01", MB_OK);
		return S_FALSE;
	}

	// テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice,
		PARTICLE_TEXTURE,
		&pTexture)))
	{
		// エラー
		MessageBox(NULL, "テクスチャの読み込みに失敗しました", PARTICLE_TEXTURE, MB_OK);
		return S_FALSE;
	}

	// 頂点情報の作成（ローカル座標の設定）
	MakeVertex(pDevice);
	return S_OK;
}

//=============================================================================
// 解放処理
//=============================================================================
void Particle::Release(void)
{
	// 解放処理
	SAFE_RELEASE(pTexture);		// テクスチャ
	SAFE_RELEASE(pVtxBuff);		// 頂点バッファ
	SAFE_RELEASE(pInstBuff);	// インスタンシングバッファ
	SAFE_RELEASE(pIdxBuff);		// インデックスバッファ
	SAFE_RELEASE(pDecl);		// 頂点宣言
	SAFE_RELEASE(pErrorBuff);	// シェーダ用コンパイルエラー
	SAFE_RELEASE(pEffect);		// シェーダ
}

//=============================================================================
// 更新処理
//=============================================================================
void Particle::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("【 PARTICLE 】\n");
#endif
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 移動量を加算
	fMove += PARTICLE_MOVE_SPEED;

	// マウスホイールでパーティクルカラーを変更
	long ModUseZ = GetMobUseZ();
	if (ModUseZ != 0)
	{
		if (ModUseZ > 0)
		{
			nColor++;
			if (nColor >= COLOR_PALLET_MAX)
			{
				nColor = 0;
			}
		}
		else
		{
			nColor--;
			if (nColor < 0)
			{
				nColor = COLOR_PALLET_MAX - 1;
			}
		}
	}

	// 左クリックでエフェクト設置
	if (IsMobUseLeftPressed())
	{
		Set(PARTICLE_SET,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			SetColorPallet(nColor));
	}

#ifdef _DEBUG
	PrintDebugProc("ParticleMax:%d\n", nCount);
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void Particle::Draw(void)
{
	if (nCount >= 0)
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

		// 加算合成に設定
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// αデスティネーションカラーの指定
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//////pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z比較なし

		//// ラインティングを無効にする
		//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ワールドマトリクスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// ビュー行列の逆行列を格納（ビルボード化）
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;

		// インスタンス宣言
		pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | nCount);
		pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

		// 頂点とインデックスを設定
		pDevice->SetVertexDeclaration(pDecl);
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_PLANE));		// 頂点バッファ
		pDevice->SetStreamSource(1, pInstBuff, 0, sizeof(INSTANCE_PLANE));	// インスタンスバッファ
		pDevice->SetIndices(pIdxBuff);										// インデックスバッファ

		// テクニックを設定
		pEffect->SetTechnique("Tec01");

		// シェーダーの開始、passNumには指定してあるテクニックに定義してあるpassの数が変える
		pEffect->Begin(&numPass, 0);

		// パスを指定して開始
		pEffect->BeginPass(0);

		// テクスチャをセット
		pEffect->SetTexture("tex", pTexture);

		// 必要な行列情報をセット
		pEffect->SetMatrix("proj", &mtxProjection);
		pEffect->SetMatrix("view", &mtxView);
		pEffect->SetMatrix("world", &mtxWorld);

		// 移動量をセット
		pEffect->SetFloat("moveTime", fMove);

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

		// 通常ブレンドに戻す
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//// αテストを無効に
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//// ラインティングを有効にする
		//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Particle::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
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
		pVtx[0].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[1].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[2].vtx = D3DXVECTOR4(-PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);
		pVtx[3].vtx = D3DXVECTOR4(PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f, 1.0f);

		// テクスチャ座標の設定
		int x = 0 % PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		int y = 0 / PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / PARTICLE_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / PARTICLE_TEXTURE_PATTERN_DIVIDE_Y;

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
		sizeof(INSTANCE_PLANE) * PARTICLE_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
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
		for (unsigned int i = 0; i < PARTICLE_MAX; i++, pInst++)
		{
			pInst->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pInst->diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pInst->vec = RandVector();
			pInst->move = 0.0f;
		}

		// 座標データをアンロックする
		pInstBuff->Unlock();
	}


	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// VTX
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// UV
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// ワールド位置
		{ 1, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },		// 頂点カラー
		{ 1, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		// 移動ベクトル
		{ 1, 28, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	// カウンター
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);

	return S_OK;
}

//=============================================================================
// 設置処理
//=============================================================================
void Particle::Set(int value, D3DXVECTOR3 pos, D3DXCOLOR color)
{
	if (nCount + value > PARTICLE_MAX)
	{
		value = PARTICLE_MAX - nCount;
	}

	{// 座標バッファの中身を埋める
		INSTANCE_PLANE *pInst;

		// 座標データの範囲をロックし、頂点バッファへのポインタを取得
		pInstBuff->Lock(0, 0, (void**)&pInst, 0);

		pInst += nCount;

		for (unsigned int i = 0; i < value; i++, pInst++)
		{
			// 座標の設定
			pInst->pos = pos;
			//pInst->diffuse = color;
			pInst->diffuse = SetColorPalletRandom();
			//pInst->vec = RandVector();
			pInst->move = fMove;
		}
		// 座標データをアンロックする
		pInstBuff->Unlock();

		nCount += value;
	}
}