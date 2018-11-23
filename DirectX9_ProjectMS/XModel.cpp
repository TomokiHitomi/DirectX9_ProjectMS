//=============================================================================
//
// モデル処理 [XModel.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "XModel.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
CXModel::CXModel(void)
{
	// モデル関係の初期化
	pTexture = NULL;
	pMesh = NULL;
	pBuffMat = NULL;
	dwNumMat = 0;
	bLight = true;

	pEffect = NULL;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CXModel::Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pMeshPass, LPSTR pTexPass)
{
	// モデルデータ読み込み
	if (FAILED(D3DXLoadMeshFromX(
		pMeshPass,				// モデルデータ
		D3DXMESH_SYSTEMMEM,		// 使用するメモリのオプション
		pDevice,				// デバイス
		NULL,					// 未使用
		&pBuffMat,				// マテリアルデータ
		NULL,					// 未使用
		&dwNumMat,				// D3DXMATERIAL構造体の数
		&pMesh)))				// メッシュデータへのポインタ
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", pMeshPass, MB_OK);
		return E_FAIL;
	}
	if (pTexPass)
	{
		// テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,				// デバイス
			pTexPass,				// ファイル名
			&pTexture)))			// 読み込むメモリ（複数なら配列に）
		{
			MessageBox(NULL, "Xファイルのテクスチャ読み込みに失敗しました", pTexPass, MB_OK);
			return E_FAIL;
		}
	}
}

//=============================================================================
// 解放処理
//=============================================================================
void CXModel::Release(void)
{
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pBuffMat);
}

//=============================================================================
// 更新処理
//=============================================================================
void CXModel::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CXModel::Draw(D3DXMATRIX mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 pMatDef;
	HRESULT hr;

	// ビュー・プロジェクション行列を取得
	D3DXMATRIX mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	if (pEffect == NULL)
	{
		// シェーダのアドレスを取得
		pEffect = ShaderManager::GetEffect(ShaderManager::XMODEL);
	}

	// マテリアル情報に対するポインタの取得
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();


	// 使用するテクニックを定義
	if (bLight)
	{	// ライトON
		if (pTexture)
		{
			hr = pEffect->SetTechnique("LIGHT_ON_TEX");
		}
		else
		{
			hr = pEffect->SetTechnique("LIGHT_ON");
		}
	}
	else
	{	// ライトOFF
		if (pTexture)
		{
			hr = pEffect->SetTechnique("LIGHT_OFF_TEX");
		}
		else
		{
			hr = pEffect->SetTechnique("LIGHT_OFF");
		}
	}

	if (FAILED(hr))
	{
		// エラー
		MessageBox(NULL, "テクニックの定義に失敗しました。", "XMODEL", MB_OK);
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

	if (bLight)
	{	// ライトON
		Camera* pCamera = CameraManager::GetCameraNow();
		D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
		if (FAILED(pEffect->SetVector("eye",&eyeTmp)))
		{
			// エラー
			MessageBox(NULL, "カメラEye情報のセットに失敗しました。", "eye", MB_OK);
		}
		// ライト情報を取得
		Light* pLight = LightManager::GetLightAdr(LightManager::Main);
		// ライト情報をセット
		if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
		{
			// エラー
			MessageBox(NULL, "ライト情報のセットに失敗しました。", "lt", MB_OK);
		}
		//SetShaderLight(pEffect, GetLight(0));
	}

	//メッシュの描画
	D3DXVECTOR4  temp;
	for (int i = 0; i < (int)dwNumMat; i++)
	{
		// マテリアルをセット
		pEffect->SetValue("mat", &pMat[i].MatD3D, sizeof(D3DMATERIAL9));

		// テクスチャをセット
		pEffect->SetTexture("tex", pTexture);

		// 結果を確定させる
		pEffect->CommitChanges();

		// 描画
		pMesh->DrawSubset(i);
	}

	// シェーダーパスを終了
	pEffect->EndPass();
	// シェーダーを終了
	pEffect->End();
}