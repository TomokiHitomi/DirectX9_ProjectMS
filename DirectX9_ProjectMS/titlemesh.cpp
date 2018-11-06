////=============================================================================
////
//// �v���C���[���� [titlemesh.cpp]
//// Author : GP12A295 09 ���V�L�V
////
////=============================================================================
//#include "main.h"
//#include "input.h"
//#include "titlemesh.h"
//#include <math.h>
//// �f�o�b�O�p
//#ifdef _DEBUG
//#include "debugproc.h"
//#endif
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//
////*****************************************************************************
//// �v���g�^�C�v�錾
////*****************************************************************************
//
//
////*****************************************************************************
//// �O���[�o���ϐ�
////*****************************************************************************
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//Titlemesh::Titlemesh()
//{
//	// �I�u�W�F�N�gID�ƃv���C�I���e�B�̐ݒ菈��
//	SetIdAndPriority(ObjectID::TITLEMESH, Priority::Middle, Priority::Lowest);
//
//	Init();
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//Titlemesh::~Titlemesh()
//{
//	Uninit();
//}
//
////=============================================================================
//// ����������
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
//	// �|���S���\���ʒu�̒��S���W��ݒ�
//	TitleMesh->Pos=D3DXVECTOR3(TEXTURE_TITLEMESH_POSITION000_X, TEXTURE_TITLEMESH_POSITION000_Y, TEXTURE_TITLEMESH_POSITION000_Z);
//	TitleMesh->Rot= D3DXVECTOR3(TEXTURE_TITLEMESH_ROTATION000_X, TEXTURE_TITLEMESH_ROTATION000_Y, TEXTURE_TITLEMESH_ROTATION000_Z);
//	// �u���b�N���̐ݒ�
//	TitleMesh->NumBlockX=FIELD_NUM_X;
//	TitleMesh->NumBlockZ=FIELD_NUM_Z;
//
//	// �e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLEMESH_000,&TitleMesh->pD3DTexture);
//
//
//	// ���_���̐ݒ�
//	TitleMesh->NumVertex = (TitleMesh->NumBlockX + 1) * (TitleMesh->NumBlockZ + 1);
//
//	// �C���f�b�N�X���̐ݒ�
//	TitleMesh->NumVertexIndex = (TitleMesh->NumBlockX + 1) * 2 * TitleMesh->NumBlockZ + (TitleMesh->NumBlockZ - 1) * 2;
//
//	// �|���S�����̐ݒ�
//	TitleMesh->NumPolygon = TitleMesh->NumBlockX * TitleMesh->NumBlockZ * 2 + (TitleMesh->NumBlockZ - 1) * 4;
//
//	// �u���b�N�T�C�Y�̐ݒ�
//	TitleMesh->BlockSizeX = TitleMesh->BlockSizeX;
//	TitleMesh->BlockSizeZ = TitleMesh->BlockSizeZ;
//
//	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
//	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * TitleMesh->NumVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
//		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
//		FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
//		&TitleMesh->pD3DVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
//		NULL)))								// NULL�ɐݒ�
//	{
//		return E_FAIL;
//	}
//
//	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
//	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) *TitleMesh->NumVertexIndex,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
//		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
//		D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
//		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
//		&TitleMesh->pD3DIdxBuff,				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
//		NULL)))								// NULL�ɐݒ�
//	{
//		return E_FAIL;
//	}
//
//	{//���_�o�b�t�@�̒��g�𖄂߂�
//		VERTEX_3D *pVtx;
//#if 0
//		const float texSizeX = 1.0f / g_nNumBlockX;
//		const float texSizeZ = 1.0f / g_nNumBlockZ;
//#else
//		const float texSizeX = 1.0f;
//		const float texSizeZ = 1.0f;
//#endif
//
//		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		TitleMesh->pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//		for (int nCntVtxZ = 0; nCntVtxZ < (TitleMesh->NumBlockZ + 1); nCntVtxZ++)
//		{
//			for (int nCntVtxX = 0; nCntVtxX < (TitleMesh->NumBlockX + 1); nCntVtxX++)
//			{
//				// ���_���W�̐ݒ�
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.x = -(TitleMesh->NumBlockX / 2.0f) * TitleMesh->BlockSizeX + nCntVtxX * TitleMesh->BlockSizeX;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.y = 0.0f;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].vtx.z = (TitleMesh->NumBlockZ / 2.0f) * TitleMesh->BlockSizeZ - nCntVtxZ * TitleMesh->BlockSizeZ;
//
//				// �@���̐ݒ�
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);
//
//				// ���ˌ��̐ݒ�
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//				// �e�N�X�`�����W�̐ݒ�
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
//				pVtx[nCntVtxZ * (TitleMesh->NumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
//			}
//		}
//
//		// ���_�f�[�^���A�����b�N����
//		TitleMesh->pD3DVtxBuff->Unlock();
//	}
//
//	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
//		WORD *pIdx;
//
//		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
//		TitleMesh->pD3DIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
//
//		int nCntIdx = 0;
//		for (int nCntVtxZ = 0; nCntVtxZ < TitleMesh->NumBlockZ; nCntVtxZ++)
//		{
//			if (nCntVtxZ > 0)
//			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
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
//			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
//				pIdx[nCntIdx] = nCntVtxZ * (TitleMesh->NumBlockX + 1) + TitleMesh->NumBlockX;
//				nCntIdx++;
//			}
//		}
//
//		// �C���f�b�N�X�f�[�^���A�����b�N����
//		TitleMesh->pD3DIdxBuff->Unlock();
//	}
//
//	return S_OK;
//
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void Titlemesh::Uninit(void)
//{
//	for (int i = 0; i < NUM_TITLEMESH; i++)
//	{
//		if (TitleMesh.pD3DTexture != NULL)	// (*31)
//		{	// �e�N�X�`���̊J��
//			TitleMesh.pD3DTexture->Release();
//			TitleMesh.pD3DTexture = NULL;
//		}
//	}
//	
//}
//
////=============================================================================
//// �X�V����
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
//		//	���_�J���[�̐ݒ�
//		SetVertexTitlemesh(i);
//		// �e�N�X�`�����W��ݒ�
//		SetTextureTitlemesh(i);
//	}
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void Titlemesh::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int i = 0; i < NUM_TITLEMESH; i++)
//	{
//		if (TitleMesh.Use == true)
//		{
//			pDevice->SetTexture(0, TitleMesh.pD3DTexture);
//
//
//			// �|���S���̕`��
//			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, TitleMesh.vertexWk, sizeof(VERTEX_2D));
//		}
//	}
//}
////=============================================================================
//// set�֐�
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
//// �e�N�X�`�����W�̐ݒ� (*34)
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
//// ���_�̍쐬
////=============================================================================
//HRESULT Titlemesh::MakeVertexTitlemesh(int i)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//	// ���_���W�̐ݒ�
//	SetVertexTitlemesh(i);
//
//
//	// rhw�̐ݒ�
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
