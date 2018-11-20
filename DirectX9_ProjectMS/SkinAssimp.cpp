#include "SkinAssimp.h"
#include "shader.h"

#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#pragma comment(lib, "assimp-vc140-mt.lib")

CSkinAssimp::CSkinAssimp(void)
{
	// �e�|�C���^�̏�����
	pTexture = NULL;	// �e�N�X�`��
	pVtxBuff = NULL;	// ���_�o�b�t�@
	pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@
	pDecl = NULL;		// ���_�錾

	// �V�F�[�_�֘A�̏�����
	pEffect = NULL;		// �V�F�[�_

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

	// �V�F�[�_�̃A�h���X���擾
	pEffect = ShaderManager::GetEffect(ShaderManager::SKINASSIMP);

	Assimp::Importer importer;
	std::string file_path = "Lat_Pastry.fbx";

	const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (scene == nullptr)
	{
		// �G���[
		MessageBox(NULL, importer.GetErrorString(), file_path.c_str(), MB_OK);
		return S_FALSE;
	}

	//auto mesh = scene->mNumMeshes;

	// �m�[�h��T�����ĕK�v�o�b�t�@�����J�E���g
	SearchNode(scene->mRootNode, scene);

	// �e�o�b�t�@���m��
	pTexture = new LPDIRECT3DTEXTURE9[nMeshCount];
	pVtxBuff = new LPDIRECT3DVERTEXBUFFER9[nMeshCount];
	pIdxBuff = new LPDIRECT3DINDEXBUFFER9[nMeshCount];
	pVtxCount = new unsigned int[nMeshCount];
	pFaceCount = new unsigned int[nMeshCount];

	// �m�ۂ����o�b�t�@��NULL�A�J�E���^�� 0 �ŏ�����
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		pTexture[i] = NULL;
		pVtxBuff[i] = NULL;
		pIdxBuff[i] = NULL;
		pVtxCount[i] = 0;
		pFaceCount[i] = 0;
	}

	// �J�E���^�[��������
	nMeshCount = 0;

	// �m�[�h��T�����ă��b�V�������擾
	ProcessNode(scene->mRootNode, scene);

	// ���_���̐錾
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

	// �r���[�E�v���W�F�N�V�����s����擾
	D3DXMATRIX mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);

	//// �}�e���A�����ɑ΂���|�C���^�̎擾
	//pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();


	// ���ʕ`�悷��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// �g�p����e�N�j�b�N���`
	if (0)
	{	// ���C�gON
		if (FAILED(pEffect->SetTechnique("LIGHT_ON")))
		{
			// �G���[
			MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "LIGHT_ON", MB_OK);
			//return S_FALSE;
		}
	}
	else
	{	// ���C�gOFF
		if (FAILED(pEffect->SetTechnique("LIGHT_OFF")))
		{
			// �G���[
			MessageBox(NULL, "�e�N�j�b�N�̒�`�Ɏ��s���܂���", "LIGHT_OFF", MB_OK);
			//return S_FALSE;
		}
	}

	//for (unsigned int i = 0; i < nMeshCount; i++)
	//{
		// ���_�ƃC���f�b�N�X��ݒ�
		pDevice->SetVertexDeclaration(pDecl);
		pDevice->SetStreamSource(0, pVtxBuff[1], 0, sizeof(VERTEX_ASSIMP));		// ���_�o�b�t�@
		pDevice->SetIndices(pIdxBuff[1]);										// �C���f�b�N�X�o�b�t�@

		// �V�F�[�_�[�̊J�n�AnumPass�ɂ͎w�肵�Ă���e�N�j�b�N�ɒ�`���Ă���pass�̐����ς���
		UINT numPass = 0;
		pEffect->Begin(&numPass, 0);

		// �p�X���w�肵�ĊJ�n
		pEffect->BeginPass(0);

		// �K�v�ȍs������Z�b�g
		pEffect->SetMatrix("proj", &mtxProjection);
		pEffect->SetMatrix("view", &mtxView);
		pEffect->SetMatrix("world", &mtxWorld);

		//if (bLight)
		//{	// ���C�gON
		//	Camera* pCamera = CameraManager::GetCameraNow();
		//	D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
		//	if (FAILED(pEffect->SetVector("eye", &eyeTmp)))
		//	{
		//		// �G���[
		//		MessageBox(NULL, "�J����Eye���̃Z�b�g�Ɏ��s���܂����B", "eye", MB_OK);
		//	}
		//	// ���C�g�����擾
		//	Light* pLight = LightManager::GetLightAdr(LightManager::Main);
		//	// ���C�g�����Z�b�g
		//	if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
		//	{
		//		// �G���[
		//		MessageBox(NULL, "���C�g���̃Z�b�g�Ɏ��s���܂����B", "lt", MB_OK);
		//	}
		//	//SetShaderLight(pEffect, GetLight(0));
		//}

		//���b�V���̕`��
		//for (int i = 0; i < (int)dwNumMat; i++)
		//{
			//if (bLight)
			//{	// ���C�gON
			//	// �}�e���A�����Z�b�g
			//	pEffect->SetValue("mat", &pMat[i].MatD3D, sizeof(D3DMATERIAL9));
			//	//SetShaderMat(pEffect, pMat[i].MatD3D);
			//}

			// �e�N�X�`�����Z�b�g
		pEffect->SetTexture("tex", pTexture[1]);

		// ���ʂ��m�肳����
		pEffect->CommitChanges();

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pVtxCount[1], 0, pFaceCount[1]);
		//}

		// �V�F�[�_�[�p�X���I��
		pEffect->EndPass();
		// �V�F�[�_�[���I��
		pEffect->End();
	//}

	// ���ʂ��J�����O�ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}


void CSkinAssimp::Release(void)
{
	// �������
	for (unsigned int i = 0; i < nMeshCount; i++)
	{
		SAFE_RELEASE(pTexture[i]);		// �e�N�X�`��
		SAFE_RELEASE(pVtxBuff[i]);		// ���_�o�b�t�@
		SAFE_RELEASE(pIdxBuff[i]);		// �C���f�b�N�X�o�b�t�@
	}

	SAFE_DELETE_ARRAY(pTexture);
	SAFE_DELETE_ARRAY(pVtxBuff);
	SAFE_DELETE_ARRAY(pIdxBuff);
	SAFE_DELETE_ARRAY(pVtxCount);
	SAFE_DELETE_ARRAY(pFaceCount);

	SAFE_RELEASE(pDecl);		// ���_�錾
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

	// ���_�o�b�t�@����
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_ASSIMP) * mesh->mNumVertices,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,											// ���_�o�b�t�@�̎g�p�@�@
		0,											// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pVtxBuff[nMeshCount],						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		//return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_ASSIMP *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
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

		// ���_�f�[�^���A�����b�N����
		pVtxBuff[nMeshCount]->Unlock();
	}

	// �ʂ��`�����钸�_�C���f�b�N�X���J�E���g�F�ʁ����_�i�R�j�̎O�p�`����{
	int nIdxCount = 0;
	for (unsigned int n = 0; n < mesh->mNumFaces; ++n)
	{
		aiFace face = mesh->mFaces[n];

		for (unsigned int i = 0; i < face.mNumIndices; ++i)
			nIdxCount++;
	}

	// �C���f�b�N�X�o�b�t�@����
	if (FAILED(pDevice->CreateIndexBuffer(
		sizeof(WORD) * nIdxCount,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		0,											// ���_�o�b�t�@�̎g�p�@�@
		D3DFMT_INDEX16,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pIdxBuff[nMeshCount],						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		//return E_FAIL;
	}

	{// ���W�o�b�t�@�̒��g�𖄂߂�
		WORD *pIdx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pIdxBuff[nMeshCount]->Lock(0, 0, (void**)&pIdx, 0);

		for (unsigned int n = 0; n < mesh->mNumFaces; ++n)
		{
			aiFace face = mesh->mFaces[n];

			for (unsigned int i = 0; i < face.mNumIndices; ++i)
				*pIdx++ = face.mIndices[i];
		}

		// ���_�f�[�^���A�����b�N����
		pIdxBuff[nMeshCount]->Unlock();
	}

	// �e�N�X�`���ǂݍ���
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial * mat = scene->mMaterials[mesh->mMaterialIndex];
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);

		// �e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,							// �f�o�C�X
			//str.C_Str(),						// �t�@�C����
			"data/TEXTURE/white_1x1.png",		// �t�@�C����
			&pTexture[nMeshCount])))			// �ǂݍ��ރ������i�����Ȃ�z��Ɂj
		{
			MessageBox(NULL, "�e�N�X�`���ǂݍ��݂Ɏ��s", str.C_Str(), MB_OK);
			//return E_FAIL;
		}
	}

	//Mesh ret;

	//ret.vertices_ = vertices;
	//ret.indices_ = indices;
	//ret.texture_ = texture;

	//return ret;

	// ���_�Ɩʂ̐���ۊ�
	pVtxCount[nMeshCount] = mesh->mNumVertices;
	pFaceCount[nMeshCount] = mesh->mNumFaces;
}
