#include "SkinPmx.h"
#include "shader.h"

#include "camera.h"
#include "box.h"

CSkinPmx::CSkinPmx(void)
{
	// 各ポインタの初期化
	pTexture = NULL;	// テクスチャ
	pVtxBuff = NULL;	// 頂点バッファ
	pIdxBuff = NULL;	// インデックスバッファ
	pDecl = NULL;		// 頂点宣言

	// シェーダ関連の初期化
	pEffect = NULL;		// シェーダ

	pVtxCount = NULL;
	pFaceCount = NULL;

	nMeshCount = 0;
}

CSkinPmx::~CSkinPmx(void)
{
	Release();
}

HRESULT CSkinPmx::Init(void)
{
	// 頂点データ
	D3DXVECTOR4 CubePosition[] = {
							D3DXVECTOR4(-BOX_SIZE, BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE,  BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE,  -BOX_SIZE, -BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE, -BOX_SIZE, -BOX_SIZE, 0.0f),

							D3DXVECTOR4(BOX_SIZE, BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE,  BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(BOX_SIZE, -BOX_SIZE,  BOX_SIZE, 0.0f),
							D3DXVECTOR4(-BOX_SIZE, -BOX_SIZE,  BOX_SIZE, 0.0f),
	};
	// インデックスデータ
	//	前(z=-1)  左(x=-1)  後(z=+1)  右(x=+1)  上(y=+1)  下(y=-1)
	WORD CubeVertList[] = { 0,1,2,3,  5,0,7,2,  4,5,6,7,  1,4,3,6,  5,4,0,1,  6,7,3,2 };

	// UVデータ
	D3DXVECTOR2 CubeUV[] = { D3DXVECTOR2(0.0f, 0.0f),
								D3DXVECTOR2(1.0f, 0.0f),
								D3DXVECTOR2(0.0f, 1.0f),
								D3DXVECTOR2(1.0f, 1.0f),
	};


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// シェーダのアドレスを取得
	pEffect = ShaderManager::GetEffect(ShaderManager::SKINPMX);

	nMeshCount = 1;
	// 各バッファを確保
	pTexture = new LPDIRECT3DTEXTURE9[nMeshCount];
	pVtxBuff = new LPDIRECT3DVERTEXBUFFER9[nMeshCount];
	pIdxBuff = new LPDIRECT3DINDEXBUFFER9[nMeshCount];
	pVtxCount = new unsigned int[nMeshCount];
	pFaceCount = new unsigned int[nMeshCount];

	// 確保したバッファをNULL、カウンタを 0 で初期化
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		pTexture[i] = NULL;
		pVtxBuff[i] = NULL;
		pIdxBuff[i] = NULL;
		pVtxCount[i] = 0;
		pFaceCount[i] = 0;
	}

	// 頂点バッファ生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_PMX) * NUM_VERTEX * 6,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,										// 頂点バッファの使用法　
		0,										// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&pVtxBuff[0],								// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	pVtxCount[0] = NUM_VERTEX * 6;

	{//頂点バッファの中身を埋める
		VERTEX_PMX *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pVtxBuff[0]->Lock(0, 0, (void**)&pVtx, 0);

		WORD k = 0;
		for (DWORD i = 0; i < 6; i++)
		{
			for (DWORD j = 0; j < NUM_VERTEX; j++)
			{
				D3DXVECTOR3 temp4 = CubePosition[CubeVertList[k++]];
				D3DXVECTOR3 temp3 = D3DXVECTOR3(temp4.x, temp4.y, temp4.z);
				// 頂点座標の設定
				pVtx->pos = temp3;
				//pVtx->normal = D3DXVECTOR3
				// テクスチャ座標の設定
				pVtx->uv = CubeUV[j];
				pVtx++;
			}
		}

		// 頂点データをアンロックする
		pVtxBuff[0]->Unlock();
	}


	/***** インデックスバッファ設定 *****/


	// 座標バッファ生成
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36,						// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,									// 頂点バッファの使用法　
		D3DFMT_INDEX16,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&pIdxBuff[0],							// 頂点バッファインターフェースへのポインタ
		NULL)))								// NULLに設定
	{
		return E_FAIL;
	}

	pFaceCount[0] = 36;


	{// 座標バッファの中身を埋める
		WORD *pIdx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pIdxBuff[0]->Lock(0, 0, (void**)&pIdx, 0);

		// 頂点座標の設定
		for (WORD m = 0; m < 6; m++)
		{
			*pIdx++ = 0 + 4 * m;
			*pIdx++ = 1 + 4 * m;
			*pIdx++ = 2 + 4 * m;
			*pIdx++ = 2 + 4 * m;
			*pIdx++ = 1 + 4 * m;
			*pIdx++ = 3 + 4 * m;
		}

		// 頂点データをアンロックする
		pIdxBuff[0]->Unlock();
	}


	// 頂点情報の宣言
	D3DVERTEXELEMENT9 declElems[] = {
	{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		// pos
	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },		// normal
	{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },		// uv
	//{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },		// boneId
	//{ 0, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },		// boneWeight
	D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(declElems, &pDecl);
}

void CSkinPmx::Update(void)
{

}

void CSkinPmx::Draw(D3DXMATRIX mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 pMatDef;

	// ビュー・プロジェクション行列を取得
	D3DXMATRIX mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	//// マテリアル情報に対するポインタの取得
	//pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();


	//// 両面描画する
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (unsigned int i = 0; i < nMeshCount; i++)
	{

		//// インスタンス宣言
		//pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | 1);

		// 頂点宣言
		pDevice->SetVertexDeclaration(pDecl);

		// 頂点とインデックスを設定
		pDevice->SetStreamSource(0, pVtxBuff[i], 0, sizeof(VERTEX_PMX));		// 頂点バッファ
		pDevice->SetIndices(pIdxBuff[i]);										// インデックスバッファ

	// 使用するテクニックを定義
		if (0)
		{	// ライトON
			if (FAILED(pEffect->SetTechnique("LIGHT_ON")))
			{
				// エラー
				MessageBox(NULL, "テクニックの定義に失敗しました", "LIGHT_ON", MB_OK);
				//return S_FALSE;
			}
		}
		else
		{	// ライトOFF
			if (FAILED(pEffect->SetTechnique("LIGHT_OFF")))
			{
				// エラー
				MessageBox(NULL, "テクニックの定義に失敗しました", "LIGHT_OFF", MB_OK);
				//return S_FALSE;
			}
		}

		// シェーダーの開始、numPassには指定してあるテクニックに定義してあるpassの数が変える
		UINT numPass = 0;
		pEffect->Begin(&numPass, 0);

		// パスを指定して開始
		pEffect->BeginPass(0);

		// 必要な行列情報をセット
		pEffect->SetMatrix("proj", &mtxProjection);
		pEffect->SetMatrix("view", &mtxView);
		pEffect->SetMatrix("world", &mtxWorld);

		//if (bLight)
		//{	// ライトON
		//	Camera* pCamera = CameraManager::GetCameraNow();
		//	D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
		//	if (FAILED(pEffect->SetVector("eye", &eyeTmp)))
		//	{
		//		// エラー
		//		MessageBox(NULL, "カメラEye情報のセットに失敗しました。", "eye", MB_OK);
		//	}
		//	// ライト情報を取得
		//	Light* pLight = LightManager::GetLightAdr(LightManager::Main);
		//	// ライト情報をセット
		//	if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
		//	{
		//		// エラー
		//		MessageBox(NULL, "ライト情報のセットに失敗しました。", "lt", MB_OK);
		//	}
		//	//SetShaderLight(pEffect, GetLight(0));
		//}

		//メッシュの描画
		//for (int i = 0; i < (int)dwNumMat; i++)
		//{
			//if (bLight)
			//{	// ライトON
			//	// マテリアルをセット
			//	pEffect->SetValue("mat", &pMat[i].MatD3D, sizeof(D3DMATERIAL9));
			//	//SetShaderMat(pEffect, pMat[i].MatD3D);
			//}

		// テクスチャをセット
		pEffect->SetTexture("tex", pTexture[i]);

		// 結果を確定させる
		pEffect->CommitChanges();

		//pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pFaceCount[i]);

		// ポリゴンの描画
		if (FAILED(pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxCount[i], 0, pFaceCount[i])))
		{
			// エラー
			MessageBox(NULL, "描画に失敗", "Draw", MB_OK);
		}
		//}

		// シェーダーパスを終了
		pEffect->EndPass();
		// シェーダーを終了
		pEffect->End();
	}

	//// インスタンス宣言を標準に戻す
	//pDevice->SetStreamSourceFreq(0, 1);

	//// 裏面をカリングに戻す
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 固定機能に戻す
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}


void CSkinPmx::Release(void)
{
	// 解放処理
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		SAFE_RELEASE(pTexture[i]);		// テクスチャ
		SAFE_RELEASE(pVtxBuff[i]);		// 頂点バッファ
		SAFE_RELEASE(pIdxBuff[i]);		// インデックスバッファ
	}

	SAFE_DELETE_ARRAY(pTexture);
	SAFE_DELETE_ARRAY(pVtxBuff);
	SAFE_DELETE_ARRAY(pIdxBuff);
	SAFE_DELETE_ARRAY(pVtxCount);
	SAFE_DELETE_ARRAY(pFaceCount);

	SAFE_RELEASE(pDecl);		// 頂点宣言
}