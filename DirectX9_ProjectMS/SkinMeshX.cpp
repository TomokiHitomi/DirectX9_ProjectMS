//=============================================================================
//
// �A�j���[�V�������f������ [SkinMeshX.cpp]
// Author : GP12A295 25 �l���F��
//
// �Q�l�FGES�u���O
// http://ges.blog.shinobi.jp/directx/directx%209%E3%80%80%E3%82%B9%E3%82%AD%E3%83%B3%E3%83%A1%E3%83%83%E3%82%B7%E3%83%A5%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "SkinMeshX.h"
#include "camera.h"
#include "light.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif


HRESULT GenerateSkinnedMesh(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer);

enum METHOD
{
	D3DNONINDEXED,
	D3DINDEXED,
	SOFTWARE,
	D3DINDEXEDVS,
	D3DINDEXEDHLSLVS,
	NONE
};

METHOD		g_SkinningMethod = D3DINDEXEDHLSLVS; // Current skinning method

UINT                        g_NumBoneMatricesMax = 0;
D3DXMATRIXA16*              g_pBoneMatrices = NULL;
DWORD                       g_dwBehaviorFlags;      // Behavior flags of the 3D device


bool		g_bUseSoftwareVP;	// Flag to indicate whether software vp is

CHAR* HeapCopy(CHAR* sName)
{
	DWORD dwLen = (DWORD)strlen(sName) + 1;
	CHAR* sNewName = new CHAR[dwLen];
	if (sNewName)
		strcpy_s(sNewName, dwLen, sName);
	return sNewName;
}

//--------------------------------------------------------------------------------------
// Name: AllocateName()
// Desc: Allocates memory for a string to hold the name of a frame or mesh
//--------------------------------------------------------------------------------------
HRESULT AllocateName(LPCSTR Name, LPSTR* pNewName)
{
	UINT cbLength;

	if (Name != NULL)
	{
		cbLength = (UINT)strlen(Name) + 1;
		*pNewName = new CHAR[cbLength];
		if (*pNewName == NULL)
			return E_OUTOFMEMORY;
		memcpy(*pNewName, Name, cbLength * sizeof(CHAR));
	}
	else
	{
		*pNewName = NULL;
	}

	return S_OK;
}


//=============================================================================
// �t���[���i�[�֐�
//=============================================================================
HRESULT MY_HIERARCHY::CreateFrame(LPCTSTR Name, LPD3DXFRAME *ppNewFrame)
{
	HRESULT hr = S_OK;
	D3DXFRAME_DERIVED *pFrame;
	//�V�����t���[���A�h���X�i�[�p�ϐ���������
	*ppNewFrame = NULL;
	//�t���[���̗̈�m��
	pFrame = new D3DXFRAME_DERIVED;
	//�̈�m�ۂ̎��s���̏���
	if (pFrame == NULL)
	{
		return E_OUTOFMEMORY;
	}
	ZeroMemory(pFrame, sizeof(D3DXFRAME_DERIVED));


	//�t���[�����i�[�p�̈�m��
	if (Name)
		pFrame->Name = (CHAR *)HeapCopy((CHAR *)Name);
	else
	{
		// TODO: Add a counter to append to the string below
		//       so that we are using a different name for
		//       each bone.
		pFrame->Name = NULL;
	}

	////�t���[�����i�[�p�̈�m��
	//pFrame->Name = new TCHAR[lstrlen(Name) + 1];
	////�̈�m�ۂ̎��s���̏���
	//if (!pFrame->Name)
	//{
	//	return E_FAIL;
	//}
	// //strcpy(pFrame->Name,Name);
	////�t���[�����i�[
	//strcpy_s(pFrame->Name, lstrlen(Name) + 1, Name);

	//�s��̏�����
	D3DXMatrixIdentity(&pFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pFrame->CombinedTransformationMatrix);
	//�ǉ��F�I�t�Z�b�g�֌W������
	//pFrame->OffsetID = 0xFFFFFFFF;
	D3DXMatrixIdentity(&(pFrame->CombinedTransformationMatrix));
	//�V�K�t���[���̃��b�V���R���e�i������
	pFrame->pMeshContainer = NULL;
	//�V�K�t���[���̌Z��t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameSibling = NULL;
	//�V�K�t���[���̎q�t���[���A�h���X�i�[�p�ϐ�������
	pFrame->pFrameFirstChild = NULL;
	//�O���̐V�K�t���[���A�h���X�i�[�p�ϐ��ɁA�쐬�����t���[���̃A�h���X���i�[
	*ppNewFrame = pFrame;
	return S_OK;
}

//=============================================================================
// ���b�V���R���e�i�[�쐬�֐�
//=============================================================================
//HRESULT MY_HIERARCHY::CreateMeshContainer
//���b�V���R���e�i�[���쐬����
HRESULT MY_HIERARCHY::CreateMeshContainer(
	LPCSTR Name,
	CONST D3DXMESHDATA* pMeshData,
	CONST D3DXMATERIAL* pMaterials,
	CONST D3DXEFFECTINSTANCE* pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppMeshContainer)
{
	HRESULT hr;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = NULL;
	UINT NumFaces;
	UINT iMaterial;
	UINT iBone, cBones;
	LPDIRECT3DDEVICE9 pDevice = NULL;

	LPD3DXMESH pMesh = NULL;

	*ppMeshContainer = NULL;

	// this sample does not handle patch meshes, so fail when one is found
	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// get the pMesh interface pointer out of the mesh data structure
	pMesh = pMeshData->pMesh;

	// this sample does not FVF compatible meshes, so fail when one is found
	if (pMesh->GetFVF() == 0)
	{
		hr = E_FAIL;
		goto e_Exit;
	}

	// allocate the overloaded structure to return as a D3DXMESHCONTAINER
	pMeshContainer = new D3DXMESHCONTAINER_DERIVED;
	if (pMeshContainer == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	memset(pMeshContainer, 0, sizeof(D3DXMESHCONTAINER_DERIVED));

	// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
	hr = AllocateName(Name, &pMeshContainer->Name);
	if (FAILED(hr))
		goto e_Exit;

	pMesh->GetDevice(&pDevice);
	NumFaces = pMesh->GetNumFaces();

	// if no normals are in the mesh, add them
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		// clone the mesh to make room for the normals
		hr = pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL,
			pDevice, &pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;

		// get the new pMesh pointer back out of the mesh container to use
		// NOTE: we do not release pMesh because we do not have a reference to it yet
		pMesh = pMeshContainer->MeshData.pMesh;

		// now generate the normals for the pmesh
		D3DXComputeNormals(pMesh, NULL);
	}
	else  // if no normals, just add a reference to the mesh for the mesh container
	{
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

		pMesh->AddRef();
	}

	// allocate memory to contain the material information.  This sample uses
	//   the D3D9 materials and texture names instead of the EffectInstance style materials
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[NumFaces * 3];
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}

	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces * 3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);

	// if materials provided, copy them
	if (NumMaterials > 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				//�e�N�X�`���̃t�@�C���p�X�ۑ��p�ϐ�
				TCHAR strTexturePath[MAX_PATH];
				//�e�N�X�`���̃t�@�C���p�X��ۑ�(�ēǂݍ��ݎ��ɕK�v)
				strcpy_s(strTexturePath, lstrlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename) + 1, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				//�e�N�X�`�����̓ǂݍ���
				if (FAILED(hr = D3DXCreateTextureFromFile(
					pDevice,
					strTexturePath,
					&pMeshContainer->ppTextures[iMaterial])))
				{
					////���s���̏���
					////�e�N�X�`���t�@�C�����i�[�p
					//CHAR TexMeshPass[255];
					////�ǋL
					////�����Ȃ���΁AGraph�t�H���_�𒲂ׂ�
					////���j�t�@�C�����̌������ɁA�K�������Ƀt�@�C���������鎖���m�F���Ă���
					////  strcpy_s��strcat_s���g���悤�ɂ���(���̏ꍇ�́A��ɂ��� 
					////    �e�N�X�`���̃t�@�C��������A����ɂ��̃t�@�C�����̒�����0�łȂ���� �̏���if��)�B
					////  TexMeshPass�ɁAX�t�@�C��������ꏊ�Ɠ����f�B���N�g���ƁA�e�N�X�`���̃t�@�C������
					////  �����������̂��i�[
					//// strcpy_s( TexMeshPass, sizeof( TexMeshPass ) , "./../Source/Graph/" );
					//strcpy_s(TexMeshPass, sizeof(TexMeshPass), "./Graph/");
					//strcat_s(TexMeshPass, sizeof(TexMeshPass) - strlen(TexMeshPass) - strlen(strTexturePath) - 1, strTexturePath);
					////�e�N�X�`�����̓ǂݍ���
					//if (FAILED(D3DXCreateTextureFromFile(pDevice, TexMeshPass,
					//	&pMeshContainer->ppTextures[iMaterial])))
					//{
					//	//MessageBox(NULL, "�A�j���[�V����X�t�@�C���̃e�N�X�`���ǂݍ��݂Ɏ��s���܂���", TexMeshPass, MB_OK);
					//	pMeshContainer->ppTextures[iMaterial] = NULL;
					//}
					//�e�N�X�`���̃t�@�C���p�X��NULL�ɂ���
					pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
				}
			}
			pMeshContainer->pMaterials[iMaterial].MatD3D.Diffuse.r = 1.0f;
			pMeshContainer->pMaterials[iMaterial].MatD3D.Diffuse.g = 1.0f;
			pMeshContainer->pMaterials[iMaterial].MatD3D.Diffuse.b = 1.0f;
			pMeshContainer->pMaterials[iMaterial].MatD3D.Ambient.r = 0.9f;
			pMeshContainer->pMaterials[iMaterial].MatD3D.Ambient.g = 0.9f;
			pMeshContainer->pMaterials[iMaterial].MatD3D.Ambient.b = 0.9f;
		}
	}
	else // if no materials provided, use a default one
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	// if there is skinning information, save off the required data and then setup for HW skinning
	if (pSkinInfo != NULL)
	{
		// first save off the SkinInfo and original mesh data
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pMeshContainer->pOrigMesh = pMesh;
		pMesh->AddRef();

		// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
		cBones = pSkinInfo->GetNumBones();
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
		if (pMeshContainer->pBoneOffsetMatrices == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// get each of the bone offset matrices so that we don't need to get them later
		for (iBone = 0; iBone < cBones; iBone++)
		{
			pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}

		// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
		hr = GenerateSkinnedMesh(pDevice, pMeshContainer);
		if (FAILED(hr))
			goto e_Exit;
	}

	*ppMeshContainer = pMeshContainer;
	pMeshContainer = NULL;

e_Exit:
	SAFE_RELEASE(pDevice);

	// call Destroy function to properly clean up the memory allocated 
	if (pMeshContainer != NULL)
	{
		DestroyMeshContainer(pMeshContainer);
	}

	return hr;
}

//=============================================================================
// �t���[���j���֐�
//=============================================================================
//HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
//�t���[����j������
HRESULT MY_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	// 2�d����h�~
	// if (pFrameToFree == NULL)return S_FALSE;
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	if (pFrameToFree->pFrameFirstChild)
	{
		DestroyFrame(pFrameToFree->pFrameFirstChild);
	}
	if (pFrameToFree->pFrameSibling)
	{
		DestroyFrame(pFrameToFree->pFrameSibling);
	}
	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

//=============================================================================
// ���b�V���R���e�i�[�j���֐�
//=============================================================================
//HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
//���b�V���R���e�i�[��j������
HRESULT MY_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	int iMaterial;
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	SAFE_DELETE_ARRAY(pMeshContainer->Name);
	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_DELETE_ARRAY(pMeshContainer->pAdjacency);
	SAFE_DELETE_ARRAY(pMeshContainer->pMaterials);
	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; (DWORD)iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			//�e�N�X�`�����
			SAFE_RELEASE(pMeshContainer->ppTextures[iMaterial]);
		}
	}
	SAFE_DELETE_ARRAY(pMeshContainer->ppTextures);
	SAFE_RELEASE(pMeshContainer->pSkinInfo);


	SAFE_DELETE_ARRAY(pMeshContainer->ppBoneMatrixPtrs);



	SAFE_RELEASE(pMeshContainer->pOrigMesh);
	if (pMeshContainer->pBoneCombinationBuf != NULL)
	{
		SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);
		SAFE_DELETE_ARRAY(pMeshContainer->pBoneOffsetMatrices);
	}
	SAFE_DELETE(pMeshContainer);
	pMeshContainerBase = NULL;
	return S_OK;
}

//=============================================================================
// �������֐�
//=============================================================================
CSkinMesh::CSkinMesh()
{
	//�}�e���A���ύX�t���O
	m_MaterialFlg = FALSE;
	//�}�e���A���f�[�^
	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));
	//�P�ʍs��
	D3DXMatrixIdentity(&(this->m_World));
	//�A�j���[�V�������ԏ�����
	m_AnimeTime = 0;
	//�A�j���[�V�����X�s�[�h������
	m_AnimSpeed = SKIN_ANIME_SPEED; //�Œ�
	//���݂̃A�j���[�V�����g���b�N������
	m_CurrentTrack = 0;
	//�A�j���[�V�����f�[�^�g���b�N������
	//�L���ɂ���
	m_CurrentTrackDesc.Enable = TRUE;
	//�e���x100%
	m_CurrentTrackDesc.Weight = 1;
	//�J�n�ʒu������
	m_CurrentTrackDesc.Position = 0;
	//���x
	m_CurrentTrackDesc.Speed = 1;
	// ���̃A�j���[�V�����փV�t�g����̂ɂ����鎞��
	m_fShiftTime = SKIN_ANIME_WEIGHT;

	// �V�F�[�_��������
	pEffect = NULL;
}

//=============================================================================
// �{�[������֐�
//=============================================================================
VOID CSkinMesh::Release()
{
	if (m_pFrameRoot != NULL) {
		//�{�[���t���[���֌W���
		FreeAnim(m_pFrameRoot);
		//���̑����(�e�N�X�`���̎Q�ƃf�[�^�Ȃ�)�̉��
		m_cHierarchy.DestroyFrame(m_pFrameRoot);
		m_pFrameRoot = NULL;
	}
	for (DWORD i = 0; i<m_pAnimController->GetNumAnimationSets(); i++)
	{
		//�A�j���[�V�����Z�b�g�̉��
		SAFE_RELEASE(m_pAnimSet[i]);
	}
	//�A�j���[�V�����R���g���[���[���
	SAFE_RELEASE(m_pAnimController);
	//���ׂẴt���[���Q�ƕϐ��̗v�f���폜
	m_FrameArray.clear();
	//���b�V���R���e�i����̃t���[���Q�ƕϐ��̗v�f���폜
	m_IntoMeshFrameArray.clear();

	// �V�F�[�_�̉��
	SAFE_RELEASE(pEffect);
}
	
//=============================================================================
// �{�[���s��擾�֐�
//=============================================================================
HRESULT CSkinMesh::AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	D3DXFRAME_DERIVED *pFrame = NULL;
	DWORD dwBoneNum = 0;
	//���b�V���R���e�i�̌^���I���W�i���̌^�Ƃ��Ĉ���
	//(���b�V���R���e�i�������ɃI���W�i���̌^�Ƃ��č���Ă���̂Ŗ��͂Ȃ����A
	//��{�_�E���L���X�g�͊댯�Ȃ̂ő��p�͔�����ׂ�)
	D3DXMESHCONTAINER_DERIVED *pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	//�X�L�����b�V���łȂ����
	if (pMeshContainer->pSkinInfo == NULL)
	{
		return S_OK;
	}
	//�{�[���̐��擾
	dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	//�e�{�[���̃��[���h�s��i�[�p�̈���m��
	SAFE_DELETE(pMeshContainer->ppBoneMatrixPtrs);
	pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[dwBoneNum];
	//�{�[���̐��������[�v
	for (DWORD i = 0; i<dwBoneNum; i++)
	{
		//�q�t���[��(�{�[��)�̃A�h���X����������pFrame�Ɋi�[
		pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(i));
		//�q�t���[�����Ȃ���Ώ������I������
		if (pFrame == NULL)
		{
			return E_FAIL;
		}
		//�e�{�[���̃��[���h�s��i�[�p�ϐ��ɍŏI�s����i�[
		pMeshContainer->ppBoneMatrixPtrs[i] = &pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

//=============================================================================
// �{�[���s�񏉊����֐�
//=============================================================================
//HRESULT AllocateAllBoneMatrices( THING* pThing,LPD3DXFRAME pFrame )
HRESULT CSkinMesh::AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
	//�K�w�̑���(���������m�ۂ������b�V���R���e�i�̈��T������)
	if (pFrame->pMeshContainer != NULL)
	{
		//�{�[���s��̏���������
		if (FAILED(AllocateBoneMatrix(pFrameRoot, pFrame->pMeshContainer)))
		{
			return E_FAIL;
		}
	}
	//�ċN���f����
	if (pFrame->pFrameSibling != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameSibling)))
		{
			return E_FAIL;
		}
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		if (FAILED(AllocateAllBoneMatrices(pFrameRoot, pFrame->pFrameFirstChild)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//=============================================================================
// ���b�V�������_�����O�֐�
//=============================================================================
//VOID RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice,MYMESHCONTAINER* pMeshContainer, MYFRAME* pFrame)
//�t���[�����̂��ꂼ��̃��b�V���������_�����O����
VOID CSkinMesh::RenderMeshContainer(LPDIRECT3DDEVICE9 pDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrameBase)
{
	//DWORD i, k;
	//DWORD dwBlendMatrixNum;
	//DWORD dwPrevBoneID;
	//LPD3DXBONECOMBINATION pBoneCombination;
	//UINT iMatrixIndex;
	//D3DXMATRIX mStack;

	HRESULT hr;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iMaterial;
	UINT NumBlend;
	UINT iAttrib;
	DWORD AttribIdPrev;
	LPD3DXBONECOMBINATION pBoneComb;

	UINT iMatrixIndex;
	UINT iPaletteEntry;
	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pDevice->GetDeviceCaps(&d3dCaps);

	D3DDEVICE_CREATION_PARAMETERS cp;
	pDevice->GetCreationParameters(&cp);
	g_dwBehaviorFlags = cp.BehaviorFlags;

	D3DXMATRIX  mtxView, mtxProjection;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);


	//�X�L�����b�V���̕`��
	if (pMeshContainer->pSkinInfo != NULL)
	{
		if (pMeshContainer->UseSoftwareVP)
		{
			// If hw or pure hw vertex processing is forced, we can't render the
			// mesh, so just exit out.  Typical applications should create
			// a device with appropriate vertex processing capability for this
			// skinning method.
			if (g_dwBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
				return;

			pDevice->SetSoftwareVertexProcessing(TRUE);
		}

		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer
		());
		for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			// first calculate all the world matrices
			for (iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
			{
				iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
				if (iMatrixIndex != UINT_MAX)
				{
					//D3DXMatrixMultiply(&matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
					//	pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
					//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &mtxView);
					D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
						pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
				}
			}

			// �e�N�X�`������ꍇ
			if (pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId])
			{
				// �e�N�j�b�N t0 ���g�p
				pEffect->SetTechnique("t0");
				// �e�N�X�`�����Z�b�g
				pEffect->SetTexture("tex", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);
			}
			else
			{
				// �e�N�j�b�N t1 ���g�p
				pEffect->SetTechnique("t1");
			}

			{	// ���C�gON
				Camera* pCamera = CameraManager::GetCameraNow();
				D3DXVECTOR4 eyeTmp = D3DXVECTOR4(pCamera->GetEye(), 0.0f);
				if (FAILED(pEffect->SetVector("eye", &eyeTmp)))
				{
					// �G���[
					MessageBox(NULL, "�J����Eye���̃Z�b�g�Ɏ��s���܂����B", "eye", MB_OK);
				}
				// ���C�g�����擾
				Light* pLight = LightManager::GetLightAdr(LightManager::Main);
				// ���C�g�����Z�b�g
				if (FAILED(pEffect->SetValue("lt", &pLight->value, sizeof(Light::LIGHTVALUE))))
				{
					// �G���[
					MessageBox(NULL, "���C�g���̃Z�b�g�Ɏ��s���܂����B", "lt", MB_OK);
				}
			}

			pEffect->SetMatrixArray("mWorldMatrixArray", g_pBoneMatrices,
				pMeshContainer->NumPaletteEntries);

			// Sum of all ambient and emissive contribution
			//D3DXCOLOR color1(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Ambient);
			//D3DXCOLOR color2(.25, .25, .25, 1.0);
			//D3DXCOLOR ambEmm;
			//D3DXColorModulate(&ambEmm, &color1, &color2);
			//ambEmm += D3DXCOLOR(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Emissive);

			//// set material color properties 
			//pEffect->SetVector("MaterialDiffuse",
			//	(D3DXVECTOR4*)&(
			//		pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Diffuse));
			//pEffect->SetVector("MaterialAmbient", (D3DXVECTOR4*)&ambEmm);

			pEffect->SetValue("mat", &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D, sizeof(D3DMATERIAL9));


			// setup the material of the mesh subset - REMEMBER to use the original pre-skinning attribute id to get the correct material id
			//pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

			// Set CurNumBones to select the correct vertex shader for the number of bones
			pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);

			pEffect->SetMatrix("mViewProj", &mtxProjection);
			pEffect->SetMatrix("mView", &mtxView);

			// ���ʂ��m�肳����
			pEffect->CommitChanges();

			// Start the effect now all parameters have been updated
			UINT numPasses;
			pEffect->Begin(&numPasses, D3DXFX_DONOTSAVESTATE);
			for (UINT iPass = 0; iPass < numPasses; iPass++)
			{
				pEffect->BeginPass(iPass);

				// draw the subset with the current world matrix palette and material state
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);

				pEffect->EndPass();
			}

			pEffect->End();

			//pDevice->SetVertexShader(NULL);
		}

		// remember to reset back to hw vertex processing if software was required
		if (pMeshContainer->UseSoftwareVP)
		{
			pDevice->SetSoftwareVertexProcessing(FALSE);
		}
	}


////#ifdef _DEBUG
////		PrintDebugProc("Container  [%d]\n", m_dwContainerCount);
////#endif
//		//�{�[���e�[�u������o�b�t�@�̐擪�A�h���X���擾
//		pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
//		//dwPrevBoneID��UINT_MAX�̒l(0xffffffff)���i�[
//		dwPrevBoneID = UINT_MAX;
//		//�X�L�j���O�v�Z
//		for (i = 0; i < pMeshContainer->NumAttributeGroups; i++)
//		{
//			dwBlendMatrixNum = 0;
//			//�e�����Ă���s�񐔎擾
//			for (k = 0; k< pMeshContainer->NumInfl; k++)
//			{
//				//UINT_MAX(-1)
//				if (pBoneCombination[i].BoneId[k] != UINT_MAX)
//				{
//					//���݉e�����󂯂Ă���{�[���̐�
//					dwBlendMatrixNum = k;
//				}
//			}
//			//�W�I���g���u�����f�B���O���g�p���邽�߂ɍs��̌����w��
//			pDevice->SetRenderState(D3DRS_VERTEXBLEND, dwBlendMatrixNum);
//			//�e�����Ă���s��̌���
//			for (k = 0; k < pMeshContainer->NumInfl; k++)
//			{
//				//iMatrixIndex��1�x�̌Ăяo���ŕ`��o����e�{�[�������ʂ���l���i�[
//				//( ����BoneID�z��̒����̓��b�V���̎�ނɂ���ĈقȂ�
//				//( �C���f�b�N�X�Ȃ��ł���΁@=�@���_���Ƃ̏d�� �ł���
//				// �C���f�b�N�X����ł���΁@=�@�{�[���s��p���b�g�̃G���g����)
//				//���݂̃{�[��(i�Ԗ�)����݂�k�Ԗڂ̃{�[��id
//				iMatrixIndex = pBoneCombination[i].BoneId[k];
//				//�s��̏�񂪂����
//				if (iMatrixIndex != UINT_MAX)
//				{
//					//mStack�ɃI�t�Z�b�g�s��*�{�[���s����i�[
//					mStack = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);
//					//�s��X�^�b�N�Ɋi�[
//					pDevice->SetTransform(D3DTS_WORLDMATRIX(k), &mStack);
//				}
//			}
//
//
//
//			D3DMATERIAL9 TmpMat = pMeshContainer->pMaterials[pBoneCombination[i].AttribId].MatD3D;
//			TmpMat.Emissive.a = TmpMat.Diffuse.a = TmpMat.Ambient.a = 1.0f;
//			pDevice->SetMaterial(&TmpMat);
//			pDevice->SetTexture(0, pMeshContainer->ppTextures[pBoneCombination[i].AttribId]);
//			//dwPrevBoneID�ɑ����e�[�u���̎��ʎq���i�[
//			dwPrevBoneID = pBoneCombination[i].AttribId;
//			//���b�V���̕`��
//			//pMeshContainer->MeshData.pMesh->DrawSubset(i);
//			if (FAILED(pMeshContainer->MeshData.pMesh->DrawSubset(i)))
//			{
//				MessageBox(NULL, "�`��Ɏ��s���܂����B", "SkinMeshX", MB_OK);
//			}
//
////#ifdef _DEBUG
//			//PrintDebugProc("Bone  [Con:%d  ID:%d  Name:%s]\n", 
//			//	m_dwContainerCount,
//			//	m_dwBoneCount,
//			//	pMeshContainer->pSkinInfo->GetBoneName(i));
////#endif
//			m_dwBoneCount++;
//		}
////#ifdef _DEBUG
////		PrintDebugProc("BoneMax  [%d]\n", m_dwBoneCount);
////#endif
	//}
	//�ʏ탁�b�V���̏ꍇ
	else
	{
		MessageBox(NULL, "�X�L�����b�V��X�t�@�C���̕`��Ɏ��s���܂����B", NULL, MB_OK);
		exit(EOF);
	}
}

////���b�V���̌��݂�Matrix�f�[�^�擾
//bool CSkinMesh::GetMatrix(D3DXMATRIX* out,int dwCon, int dwBone)
//{
//	MYFRAME* pFrame = (MYFRAME*)m_pFrameRoot;
//	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pFrame->pMeshContainer;
//
//	for (unsigned int i = 0; i < dwCon; i++)
//	{
//		if (pMeshContainer != NULL)
//		{
//			//���̃��b�V���R���e�i�փA�N�e�B�u���ڂ�
//			pMeshContainer = (MYMESHCONTAINER*)pMeshContainer->pNextMeshContainer;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	if (dwBone <= pMeshContainer->dwBoneNum)
//	{
//		UINT iMatrixIndex;
//		LPD3DXBONECOMBINATION pBoneCombination;
//		//�{�[���e�[�u������o�b�t�@�̐擪�A�h���X���擾
//		pBoneCombination = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneBuffer->GetBufferPointer());
//		iMatrixIndex = pBoneCombination[dwBone].BoneId[0];
//
//		//�s��̏�񂪂����
//		if (iMatrixIndex != UINT_MAX)
//		{
//			//mStack�ɃI�t�Z�b�g�s��*�{�[���s����i�[
//			*out = pMeshContainer->pBoneOffsetMatrices[iMatrixIndex] * (*pMeshContainer->ppBoneMatrix[iMatrixIndex]);
//		}
//		return true;
//	}
//	return false;
//}

//=============================================================================
// �t���[�������_�����O�֐�
//=============================================================================
//VOID DrawFrame(LPDIRECT3DDEVICE9 pDevice,LPD3DXFRAME pFrameBase)
//�t���[���������_�����O����B
VOID CSkinMesh::DrawFrame(LPDIRECT3DDEVICE9 pDevice, LPD3DXFRAME pFrameBase)
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		//SHADER_KIND a = GetpShader()->GetShaderKind();
		////�V�F�[�_���g�p���Ă���̂Ȃ��p�̕`��֐��ɔ�΂�
		//if( GetpShader() != NULL && GetpShader()->GetShaderKind() == SHADER_KIND_LAMBERT ){
		// ShaderDraw( pDevice, ControlNum, pMeshContainer, pFrame ); 
		//}else{
		RenderMeshContainer(pDevice, pMeshContainer, pFrame);
		// }
		//���̃��b�V���R���e�i�փA�N�e�B�u���ڂ�
		pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainer->pNextMeshContainer;
		m_dwContainerCount++;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pDevice, pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pDevice, pFrame->pFrameFirstChild);
	}
}

//=============================================================================
// ���[���h�X�V�֐�
//=============================================================================
//VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
//�t���[�����̃��b�V�����Ƀ��[���h�ϊ��s����X�V����
VOID CSkinMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	D3DXFRAME_DERIVED *pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	if (pParentMatrix != NULL)
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		D3DXMatrixMultiply(&pFrame->CombinedTransformationMatrix, &pFrame->TransformationMatrix, pParentMatrix);
	}
	else
	{
		//CombinedTransformationMatrix�ɍŏI�s����i�[
		pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	}
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);
	}
}

//=============================================================================
// �t���[������֐�
//=============================================================================
//�S�Ă̊K�w�t���[�����������
VOID CSkinMesh::FreeAnim(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL) {
		m_cHierarchy.DestroyMeshContainer(pFrame->pMeshContainer);
		pFrame->pMeshContainer = NULL;
	}
	if (pFrame->pFrameSibling != NULL)
		FreeAnim(pFrame->pFrameSibling);
	if (pFrame->pFrameFirstChild != NULL)
		FreeAnim(pFrame->pFrameFirstChild);
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSkinMesh::Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass) {
	CHAR TmpMeshPass[255];
	strcpy_s(TmpMeshPass, sizeof(TmpMeshPass) - 1, pMeshPass);
	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
	if (FAILED(
		D3DXLoadMeshHierarchyFromX(
			TmpMeshPass, 
			D3DXMESH_MANAGED, 
			lpD3DDevice, 
			&m_cHierarchy,
			NULL,
			&m_pFrameRoot,
			&m_pAnimController)))
	{
		MessageBox(NULL, "�A�j���[�V����X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", TmpMeshPass, MB_OK);
		return E_FAIL;
	}

	//// �V�F�[�_�̃A�h���X���擾
	//pEffect = ShaderManager::GetEffect(ShaderManager::SKINMESH);

	// �V�F�[�_�̃A�h���X���擾
	ShaderManager::CreateEffect(&pEffect, ShaderManager::SKINMESH);


	//�{�[���s�񏉊���
	AllocateAllBoneMatrices(m_pFrameRoot, m_pFrameRoot);
	//�A�j���[�V�����g���b�N�̎擾
	for (DWORD i = 0; i<m_pAnimController->GetNumAnimationSets(); i++)
	{
		//�A�j���[�V�����擾
		m_pAnimController->GetAnimationSet(i, &(m_pAnimSet[i]));
	}
	//���ׂẴt���[���Q�ƕϐ��̐���
	m_FrameArray.clear();
	m_IntoMeshFrameArray.clear();
	CreateFrameArray(m_pFrameRoot);

	D3DXFRAME_DERIVED *pFrame = NULL;


	//�t���[���z��ɃI�t�Z�b�g���쐬
	for (DWORD i = 0; i<m_IntoMeshFrameArray.size(); i++) {
		D3DXMESHCONTAINER_DERIVED* pMyMeshContainer = (D3DXMESHCONTAINER_DERIVED*)m_IntoMeshFrameArray[i]->pMeshContainer;
		while (pMyMeshContainer) {
			//�X�L�����
			if (pMyMeshContainer->pSkinInfo) {
				DWORD cBones = pMyMeshContainer->pSkinInfo->GetNumBones();
				for (DWORD iBone = 0; iBone<cBones; iBone++) 
				{
					pFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pFrameRoot, pMyMeshContainer->pSkinInfo->GetBoneName(iBone));
					if (pFrame == NULL)
					{
						return E_FAIL;
					}
					pMyMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformationMatrix;


					////�t���[�������瓯�����O�̃t���[��������
					//for (DWORD Idx = 0; Idx<m_FrameArray.size(); Idx++) {
					//	if (strcmp(pMyMeshContainer->pSkinInfo->GetBoneName(iBone), m_FrameArray[Idx]->Name) == 0) {
					//		pMyMeshContainer->BoneFrameArray.push_back(m_FrameArray[Idx]);
					//		//Offset�s��
					//		m_FrameArray[Idx]->OffsetMat = *(pMyMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
					//		m_FrameArray[Idx]->OffsetID = Idx;
					//		break;
					//	}
					//}
				}
			}
			//����
			pMyMeshContainer = (D3DXMESHCONTAINER_DERIVED *)pMyMeshContainer->pNextMeshContainer;
		}
	}
	return S_OK;
}

//=============================================================================
// �t���[���|�C���^�i�[�����֐�
//=============================================================================
VOID CSkinMesh::CreateFrameArray(LPD3DXFRAME _pFrame) {
	if (_pFrame == NULL) { return; }
	//�t���[���A�h���X�i�[
	D3DXFRAME_DERIVED* pMyFrame = (D3DXFRAME_DERIVED*)_pFrame;
	m_FrameArray.push_back(pMyFrame);
	//���b�V���R���e�i������ꍇ��IntoMeshFrameArray�ɃA�h���X���i�[
	if (pMyFrame->pMeshContainer != NULL) {
		m_IntoMeshFrameArray.push_back(pMyFrame);
	}
	//�q�t���[������
	if (pMyFrame->pFrameFirstChild != NULL) {
		CreateFrameArray(pMyFrame->pFrameFirstChild);
	}
	//�Z��t���[������
	if (pMyFrame->pFrameSibling != NULL) {
		CreateFrameArray(pMyFrame->pFrameSibling);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
VOID CSkinMesh::Update(void) {
	//�������ςȂ��ɂ��A���؂�ւ��h�~
	//static bool PushFlg = false; //�����ł͉��Ńt���O���g�p���邪�A�{���̓����o�ϐ��Ȃǂɂ���
	//							 //�A�j���[�V�����ύX�`�F�b�N
	//if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
	//	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//		if (PushFlg == false) {
	//			int Num = GetAnimTrack() - 1;
	//			if (Num < 0)Num = 0;
	//			
	//			(Num, m_fShiftTime);
	//		}
	//	}
	//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//		if (PushFlg == false) {
	//			int Num = GetAnimTrack() + 1;
	//			if ((DWORD)Num > m_pAnimController->GetNumAnimationSets())Num = m_pAnimController->GetNumAnimationSets();
	//			ChangeAnim(Num, m_fShiftTime);
	//		}
	//	}
	//	PushFlg = true;
	//}
	//else {
	//	PushFlg = false;
	//}

	// ���[�V�����u�����h�m�F
	m_fCurWeight += m_fShiftTime;
	if (m_fCurWeight <= 1.0f)
	{
		// �u�����h��
		m_pAnimController->SetTrackWeight(0, m_fCurWeight);			// ���݂̃A�j���[�V����
		m_pAnimController->SetTrackWeight(1, 1.0f - m_fCurWeight);	// �O�̃A�j���[�V����
	}
	else
	{
		// �u�����h�I���B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l�ɌŒ�
		m_pAnimController->SetTrackWeight(0, 1.0f);					// ���݂̃A�j���[�V����
		m_pAnimController->SetTrackEnable(1, false);				// �O�̃A�j���[�V�����𖳌��ɂ���
	}

	//���݂̃A�j���[�V�����ԍ���K��
	m_pAnimController->SetTrackAnimationSet(0, m_pAnimSet[m_CurrentTrack]);
	//0(�Đ�����)�g���b�N����g���b�N�f�X�N���Z�b�g����
	m_pAnimController->SetTrackDesc(0, &(m_CurrentTrackDesc));
	//�A�j���[�V�������ԃf�[�^�̍X�V
	m_pAnimController->AdvanceTime(m_AnimSpeed, NULL);

	//�A�j���[�V�������Ԃ��X�V
	m_AnimeTime++;
}

//=============================================================================
// �X�L�����b�V���`��֐�
//=============================================================================
VOID CSkinMesh::Draw(LPDIRECT3DDEVICE9 lpD3DDevice, D3DXMATRIX _World)
{
//#ifdef _DEBUG
//	PrintDebugProc("�y SkinMesh �z\n");
//#endif
	//�}�g���b�N�X�s�񔽉f
	m_World = _World;
	// ���b�V���R���e�i�J�E���^��������
	m_dwContainerCount = 0;

	//�A�j���[�V�����f�[�^���X�V
	UpdateFrameMatrices(m_pFrameRoot, &m_World);
	//�A�j���[�V�����`��
	DrawFrame(lpD3DDevice, m_pFrameRoot);
	//0(�Đ�����)�g���b�N����X�V�����g���b�N�f�X�N���擾����
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
}

//=============================================================================
// �A�j���[�V�����ύX�֐�
//=============================================================================
//�I�u�W�F�N�g�̃A�j���[�V�����ύX( �ύX����A�j���[�V�����ԍ� )
VOID CSkinMesh::ChangeAnim(DWORD _NewAnimNum, FLOAT fShift)
{
	if (m_CurrentTrack == _NewAnimNum)
	{	// �قȂ�A�j���[�V�����ł��邩�`�F�b�N
		return;
	}

	// ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
	D3DXTRACK_DESC TD;   // �g���b�N�̔\��
	m_pAnimController->GetTrackDesc(0, &TD);
	// ���݂̃A�j���[�V�������g���b�N1�ֈڍs
	m_pAnimController->SetTrackAnimationSet(1, m_pAnimSet[m_CurrentTrack]);
	m_pAnimController->SetTrackDesc(1, &TD);


	// ���݂̃A�j���[�V������ۊ�
	m_OldTrack = m_CurrentTrack;
	// �V�K�A�j���[�V�����ɕύX
	m_CurrentTrack = _NewAnimNum;

	//�A�j���[�V�����^�C����������
	m_AnimeTime = 0;
	// �A�j���[�V�������ŏ��̈ʒu����Đ�������
	m_pAnimController->GetTrackDesc(0, &m_CurrentTrackDesc);
	m_CurrentTrackDesc.Position = 0;
	m_pAnimController->SetTrackDesc(0, &m_CurrentTrackDesc);

	// �E�F�C�g�^�C����������
	m_fCurWeight = 0.0f;
	// ���̃A�j���[�V�����փV�t�g����̂ɂ����鎞�Ԃ�ݒ�
	m_fShiftTime = fShift;

	// �g���b�N�̍���������
	m_pAnimController->SetTrackEnable(0, true);
	m_pAnimController->SetTrackEnable(1, true);
}

//=============================================================================
// �Ώۃ{�[�������֐�
//=============================================================================
D3DXFRAME_DERIVED* CSkinMesh::SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame) {
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)_pFrame;
	if (pFrame->Name != NULL)
	{
		if (strcmp(pFrame->Name, _BoneName) == 0) {
			return pFrame;
		}
	}
	if (_pFrame->pFrameSibling != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameSibling);
		if (pFrame != NULL) {
			return pFrame;
		}
	}
	if (_pFrame->pFrameFirstChild != NULL)
	{
		pFrame = SearchBoneFrame(_BoneName, _pFrame->pFrameFirstChild);
		if (pFrame != NULL) {
			return pFrame;
		}
	}
	return NULL;
}

//=============================================================================
// �{�[���̃}�g���N�X�擾�֐�
//=============================================================================
D3DXMATRIX CSkinMesh::GetBoneMatrix(LPSTR _BoneName) {
	D3DXFRAME_DERIVED* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL) {
		//�{�[���s���Ԃ�
		return pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else {
		//�P�ʍs���Ԃ�
		D3DXMATRIX TmpMatrix;
		D3DXMatrixIdentity(&TmpMatrix);
		return TmpMatrix;
	}
}

//=============================================================================
// �{�[���̃}�g���N�X�|�C���^�擾�֐�
//=============================================================================
D3DXMATRIX* CSkinMesh::GetpBoneMatrix(LPSTR _BoneName) {
	/////////////////////////////////////
	//���ӁjRokDeBone�p�ɐݒ�(�Ώۃ{�[���̈��̍s����Ƃ��Ă���)
	D3DXFRAME_DERIVED* pFrame = SearchBoneFrame(_BoneName, m_pFrameRoot);
	//�{�[�����������
	if (pFrame != NULL) {
		return &pFrame->CombinedTransformationMatrix;
	}
	//�{�[����������Ȃ����
	else {
		//NULL��Ԃ�
		return NULL;
	}
}

//--------------------------------------------------------------------------------------
// Called either by CreateMeshContainer when loading a skin mesh, or when 
// changing methods.  This function uses the pSkinInfo of the mesh 
// container to generate the desired drawable mesh and bone combination 
// table.
//--------------------------------------------------------------------------------------
HRESULT GenerateSkinnedMesh(IDirect3DDevice9* pd3dDevice, D3DXMESHCONTAINER_DERIVED* pMeshContainer)
{
	HRESULT hr = S_OK;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);

	if (pMeshContainer->pSkinInfo == NULL)
		return hr;

	g_bUseSoftwareVP = false;

	SAFE_RELEASE(pMeshContainer->MeshData.pMesh);
	SAFE_RELEASE(pMeshContainer->pBoneCombinationBuf);

	// if non-indexed skinning mode selected, use ConvertToBlendedMesh to generate drawable mesh
	if (g_SkinningMethod == D3DNONINDEXED)
	{

		hr = pMeshContainer->pSkinInfo->ConvertToBlendedMesh
		(
			pMeshContainer->pOrigMesh,
			D3DXMESH_MANAGED | D3DXMESHOPT_VERTEXCACHE,
			pMeshContainer->pAdjacency,
			NULL, NULL, NULL,
			&pMeshContainer->NumInfl,
			&pMeshContainer->NumAttributeGroups,
			&pMeshContainer->pBoneCombinationBuf,
			&pMeshContainer->MeshData.pMesh
		);
		if (FAILED(hr))
			goto e_Exit;


		// If the device can only do 2 matrix blends, ConvertToBlendedMesh cannot approximate all meshes to it
		// Thus we split the mesh in two parts: The part that uses at most 2 matrices and the rest. The first is
		// drawn using the device's HW vertex processing and the rest is drawn using SW vertex processing.
		LPD3DXBONECOMBINATION rgBoneCombinations = reinterpret_cast<LPD3DXBONECOMBINATION>(
			pMeshContainer->pBoneCombinationBuf->GetBufferPointer());

		// look for any set of bone combinations that do not fit the caps
		for (pMeshContainer->iAttributeSW = 0; pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups;
			pMeshContainer->iAttributeSW++)
		{
			DWORD cInfl = 0;

			for (DWORD iInfl = 0; iInfl < pMeshContainer->NumInfl; iInfl++)
			{
				if (rgBoneCombinations[pMeshContainer->iAttributeSW].BoneId[iInfl] != UINT_MAX)
				{
					++cInfl;
				}
			}

			if (cInfl > d3dCaps.MaxVertexBlendMatrices)
			{
				break;
			}
		}

		// if there is both HW and SW, add the Software Processing flag
		if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
		{
			LPD3DXMESH pMeshTmp;

			hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_SOFTWAREPROCESSING |
				pMeshContainer->MeshData.pMesh->GetOptions(),
				pMeshContainer->MeshData.pMesh->GetFVF(),
				pd3dDevice, &pMeshTmp);
			if (FAILED(hr))
			{
				goto e_Exit;
			}

			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pMeshTmp;
			pMeshTmp = NULL;
		}
	}
	// if indexed skinning mode selected, use ConvertToIndexedsBlendedMesh to generate drawable mesh
	else if (g_SkinningMethod == D3DINDEXED)
	{
		DWORD NumMaxFaceInfl;
		DWORD Flags = D3DXMESHOPT_VERTEXCACHE;

		LPDIRECT3DINDEXBUFFER9 pIB;
		hr = pMeshContainer->pOrigMesh->GetIndexBuffer(&pIB);
		if (FAILED(hr))
			goto e_Exit;

		hr = pMeshContainer->pSkinInfo->GetMaxFaceInfluences(pIB,
			pMeshContainer->pOrigMesh->GetNumFaces(),
			&NumMaxFaceInfl);
		pIB->Release();
		if (FAILED(hr))
			goto e_Exit;

		// 12 entry palette guarantees that any triangle (4 independent influences per vertex of a tri)
		// can be handled
		NumMaxFaceInfl = min(NumMaxFaceInfl, 12);

		if (d3dCaps.MaxVertexBlendMatrixIndex + 1 < NumMaxFaceInfl)
		{
			// HW does not support indexed vertex blending. Use SW instead
			pMeshContainer->NumPaletteEntries = min(256, pMeshContainer->pSkinInfo->GetNumBones());
			pMeshContainer->UseSoftwareVP = true;
			g_bUseSoftwareVP = true;
			Flags |= D3DXMESH_SYSTEMMEM;
		}
		else
		{
			// using hardware - determine palette size from caps and number of bones
			// If normals are present in the vertex data that needs to be blended for lighting, then 
			// the number of matrices is half the number specified by MaxVertexBlendMatrixIndex.
			pMeshContainer->NumPaletteEntries = min((d3dCaps.MaxVertexBlendMatrixIndex + 1) / 2,
				pMeshContainer->pSkinInfo->GetNumBones());
			pMeshContainer->UseSoftwareVP = false;
			Flags |= D3DXMESH_MANAGED;
		}

		pMeshContainer->NumPaletteEntries = NumMaxFaceInfl;

		hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
		(
			pMeshContainer->pOrigMesh,
			Flags,
			pMeshContainer->NumPaletteEntries,
			pMeshContainer->pAdjacency,
			NULL, NULL, NULL,
			&pMeshContainer->NumInfl,
			&pMeshContainer->NumAttributeGroups,
			&pMeshContainer->pBoneCombinationBuf,
			&pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;
	}
	// if vertex shader indexed skinning mode selected, use ConvertToIndexedsBlendedMesh to generate drawable mesh
	else if ((g_SkinningMethod == D3DINDEXEDVS) || (g_SkinningMethod == D3DINDEXEDHLSLVS))
	{
		// Get palette size
		// First 9 constants are used for other data.  Each 4x3 matrix takes up 3 constants.
		// (96 - 9) /3 i.e. Maximum constant count - used constants 
		UINT MaxMatrices = 26;
		pMeshContainer->NumPaletteEntries = min(MaxMatrices, pMeshContainer->pSkinInfo->GetNumBones());

		DWORD Flags = D3DXMESHOPT_VERTEXCACHE;
		if (d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
		{
			pMeshContainer->UseSoftwareVP = false;
			Flags |= D3DXMESH_MANAGED;
		}
		else
		{
			pMeshContainer->UseSoftwareVP = true;
			g_bUseSoftwareVP = true;
			Flags |= D3DXMESH_SYSTEMMEM;
		}

		SAFE_RELEASE(pMeshContainer->MeshData.pMesh);

		hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
		(
			pMeshContainer->pOrigMesh,
			Flags,
			pMeshContainer->NumPaletteEntries,
			pMeshContainer->pAdjacency,
			NULL, NULL, NULL,
			&pMeshContainer->NumInfl,
			&pMeshContainer->NumAttributeGroups,
			&pMeshContainer->pBoneCombinationBuf,
			&pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;


		// FVF has to match our declarator. Vertex shaders are not as forgiving as FF pipeline
		DWORD NewFVF = (pMeshContainer->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL |
			D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
		if (NewFVF != pMeshContainer->MeshData.pMesh->GetFVF())
		{
			LPD3DXMESH pMesh;
			hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), NewFVF,
				pd3dDevice, &pMesh);
			if (!FAILED(hr))
			{
				pMeshContainer->MeshData.pMesh->Release();
				pMeshContainer->MeshData.pMesh = pMesh;
				pMesh = NULL;
			}
		}

		D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
		LPD3DVERTEXELEMENT9 pDeclCur;
		hr = pMeshContainer->MeshData.pMesh->GetDeclaration(pDecl);
		if (FAILED(hr))
			goto e_Exit;

		// the vertex shader is expecting to interpret the UBYTE4 as a D3DCOLOR, so update the type 
		//   NOTE: this cannot be done with CloneMesh, that would convert the UBYTE4 data to float and then to D3DCOLOR
		//          this is more of a "cast" operation
		pDeclCur = pDecl;
		while (pDeclCur->Stream != 0xff)
		{
			if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0))
				pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
			pDeclCur++;
		}

		hr = pMeshContainer->MeshData.pMesh->UpdateSemantics(pDecl);
		if (FAILED(hr))
			goto e_Exit;

		// allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
		if (g_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones())
		{
			g_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

			// Allocate space for blend matrices
			delete[] g_pBoneMatrices;
			g_pBoneMatrices = new D3DXMATRIXA16[g_NumBoneMatricesMax];
			if (g_pBoneMatrices == NULL)
			{
				hr = E_OUTOFMEMORY;
				goto e_Exit;
			}
		}

	}
	// if software skinning selected, use GenerateSkinnedMesh to create a mesh that can be used with UpdateSkinnedMesh
	else if (g_SkinningMethod == SOFTWARE)
	{
		hr = pMeshContainer->pOrigMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshContainer->pOrigMesh->GetFVF(),
			pd3dDevice, &pMeshContainer->MeshData.pMesh);
		if (FAILED(hr))
			goto e_Exit;

		hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(NULL, &pMeshContainer->NumAttributeGroups);
		if (FAILED(hr))
			goto e_Exit;

		delete[] pMeshContainer->pAttributeTable;
		pMeshContainer->pAttributeTable = new D3DXATTRIBUTERANGE[pMeshContainer->NumAttributeGroups];
		if (pMeshContainer->pAttributeTable == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}

		hr = pMeshContainer->MeshData.pMesh->GetAttributeTable(pMeshContainer->pAttributeTable, NULL);
		if (FAILED(hr))
			goto e_Exit;

		// allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
		if (g_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones())
		{
			g_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

			// Allocate space for blend matrices
			delete[] g_pBoneMatrices;
			g_pBoneMatrices = new D3DXMATRIXA16[g_NumBoneMatricesMax];
			if (g_pBoneMatrices == NULL)
			{
				hr = E_OUTOFMEMORY;
				goto e_Exit;
			}
		}
	}
	else  // invalid g_SkinningMethod value
	{
		// return failure due to invalid skinning method value
		hr = E_INVALIDARG;
		goto e_Exit;
	}

e_Exit:
	return hr;
}
