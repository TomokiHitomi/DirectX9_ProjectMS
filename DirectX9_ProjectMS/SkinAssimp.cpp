#include "SkinAssimp.h"
#include "shader.h"

#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#pragma comment(lib, "assimp-vc140-mt.lib")

CSkinAssimp::CSkinAssimp(void)
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

CSkinAssimp::~CSkinAssimp(void)
{
	Release();
}

HRESULT CSkinAssimp::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// シェーダのアドレスを取得
	pEffect = ShaderManager::GetEffect(ShaderManager::SKINASSIMP);

	Assimp::Importer importer;
	std::string file_path = "Lat_Pastry.fbx";

	const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (scene == nullptr)
	{
		// エラー
		MessageBox(NULL, importer.GetErrorString(), file_path.c_str(), MB_OK);
		return S_FALSE;
	}

	//auto mesh = scene->mNumMeshes;

	// ノードを探査して必要バッファ数をカウント
	SearchNode(scene->mRootNode, scene);

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

	// カウンターを初期化
	nMeshCount = 0;

	// ノードを探査してメッシュ情報を取得
	ProcessNode(scene->mRootNode, scene);

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

void CSkinAssimp::Update(void)
{

}

void CSkinAssimp::Draw(D3DXMATRIX mtxWorld)
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


	// 両面描画する
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


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

	//for (unsigned int i = 0; i < nMeshCount; i++)
	//{
		// 頂点とインデックスを設定
		pDevice->SetVertexDeclaration(pDecl);
		pDevice->SetStreamSource(0, pVtxBuff[1], 0, sizeof(VERTEX_ASSIMP));		// 頂点バッファ
		pDevice->SetIndices(pIdxBuff[1]);										// インデックスバッファ

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
		pEffect->SetTexture("tex", pTexture[1]);

		// 結果を確定させる
		pEffect->CommitChanges();

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxCount[1], 0, pFaceCount[1]);
		//}

		// シェーダーパスを終了
		pEffect->EndPass();
		// シェーダーを終了
		pEffect->End();
	//}

	// 裏面をカリングに戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}


void CSkinAssimp::Release(void)
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

void CSkinAssimp::SearchNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int n = 0; n < node->mNumMeshes; ++n)
	{
		nMeshCount++;
	}

	for (unsigned int n = 0; n < node->mNumChildren; ++n)
	{
		this->SearchNode(node->mChildren[n], scene);
	}
}

void CSkinAssimp::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int n = 0; n < node->mNumMeshes; ++n)
	{
		ProcessMesh(scene->mMeshes[node->mMeshes[n]], scene);
		nMeshCount++;
	}

	for (unsigned int n = 0; n < node->mNumChildren; ++n)
		this->ProcessNode(node->mChildren[n], scene);
}

void CSkinAssimp::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファ生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_ASSIMP) * mesh->mNumVertices,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,											// 頂点バッファの使用法　
		0,											// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&pVtxBuff[nMeshCount],						// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		//return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_ASSIMP *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pVtxBuff[nMeshCount]->Lock(0, 0, (void**)&pVtx, 0);

		for (unsigned int n = 0; n < mesh->mNumVertices; ++n)
		{
			pVtx->pos.x = mesh->mVertices[n].x;
			pVtx->pos.y = mesh->mVertices[n].y;
			pVtx->pos.z = mesh->mVertices[n].z;

			if (mesh->mNormals)
			{
				pVtx->normal.x = (float)mesh->mNormals[n].x;
				pVtx->normal.y = (float)mesh->mNormals[n].y;
				pVtx->normal.z = (float)mesh->mNormals[n].z;
			}

			if (mesh->mTextureCoords[0])
			{
				pVtx->uv.x = (float)mesh->mTextureCoords[0][n].x;
				pVtx->uv.y = (float)mesh->mTextureCoords[0][n].y;
			}
		}

		// 頂点データをアンロックする
		pVtxBuff[nMeshCount]->Unlock();
	}

	// 面を形成する頂点インデックスをカウント：面＊頂点（３）の三角形が基本
	int nIdxCount = 0;
	for (unsigned int n = 0; n < mesh->mNumFaces; ++n)
	{
		aiFace face = mesh->mFaces[n];

		for (unsigned int i = 0; i < face.mNumIndices; ++i)
			nIdxCount++;
	}

	// インデックスバッファ生成
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * nIdxCount,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		0,											// 頂点バッファの使用法　
		D3DFMT_INDEX16,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&pIdxBuff[nMeshCount],						// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		//return E_FAIL;
	}

	{// 座標バッファの中身を埋める
		WORD *pIdx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pIdxBuff[nMeshCount]->Lock(0, 0, (void**)&pIdx, 0);

		for (unsigned int n = 0; n < mesh->mNumFaces; ++n)
		{
			aiFace face = mesh->mFaces[n];

			for (unsigned int i = 0; i < face.mNumIndices; ++i)
				*pIdx++ = face.mIndices[i];
		}

		// 頂点データをアンロックする
		pIdxBuff[nMeshCount]->Unlock();
	}

	// テクスチャ読み込み
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial * mat = scene->mMaterials[mesh->mMaterialIndex];
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);

		// テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,							// デバイス
			//str.C_Str(),						// ファイル名
			"data/TEXTURE/white_1x1.png",		// ファイル名
			&pTexture[nMeshCount])))			// 読み込むメモリ（複数なら配列に）
		{
			MessageBox(NULL, "テクスチャ読み込みに失敗", str.C_Str(), MB_OK);
			//return E_FAIL;
		}
	}

	//Mesh ret;

	//ret.vertices_ = vertices;
	//ret.indices_ = indices;
	//ret.texture_ = texture;

	//return ret;

	// 頂点と面の数を保管
	pVtxCount[nMeshCount] = mesh->mNumVertices;
	pFaceCount[nMeshCount] = mesh->mNumFaces;
}
