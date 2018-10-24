#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include "ModelFrame.h"

// �X�L�����b�V���N���X
class CSkinMesh
{

public:
	//���b�V���N���X�̏�����
	// void InitBase(SMESH_DATA_FILE* _pSMeshData);

	//���b�V���̌��݂�Matrix�f�[�^�擾
	D3DXMATRIX GetMatrix();

	CSkinMesh();
	~CSkinMesh() {
		Release();
	}

	//�X�L�����b�V����������
	HRESULT Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	void RenderMeshContainer(LPDIRECT3DDEVICE9 lpD3DDevice, MYMESHCONTAINER*, MYFRAME*);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(PDIRECT3DDEVICE9 lpD3DDevice, LPD3DXFRAME);

	//�t���[�����
	void FreeAnim(LPD3DXFRAME pFrame);

	//�������
	void Release();

	//�X�V����
	void Update(void);
	//�`�揈��
	void Draw(LPDIRECT3DDEVICE9 lpD3DDevice, D3DXMATRIX _World);

	//�I�u�W�F�N�g�̃A�j���[�V�����ύX( ���b�V���I�u�W�F�N�g�̑���p�ԍ�, �ύX����A�j���[�V�����ԍ� )
	void ChangeAnim(DWORD NewAnimNum);

	//���݂̃A�j���[�V�����ԍ��擾
	DWORD GetAnimTrack() { return m_CurrentTrack; }
	//���݂̃A�j���[�V�����^�C��(�A�j���[�V�����J�n����̎���)���擾
	DWORD GetAnimTime() { return m_AnimeTime; }

	//�A�j���[�V�������x���擾
	FLOAT GetAnimSpeed() { return m_AnimSpeed; }
	//�A�j���[�V�������x��ݒ�
	void SetAnimSpeed(FLOAT _AnimSpeed) { m_AnimSpeed = _AnimSpeed; }

private:

	//�Ώۂ̃{�[��������
	MYFRAME* SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame);

public:

	//�{�[���̃}�g���b�N�X�擾( �{�[���̖��O )
	D3DXMATRIX GetBoneMatrix(LPSTR _BoneName);
	//�{�[���}���g���N�X�擾�֐�
	D3DXMATRIX GetBoneMatrixOffSet(LPSTR _BoneName, D3DXMATRIX* OffSet);
	//�{�[���̃}�g���b�N�X�|�C���^�擾( �{�[���̖��O )
	D3DXMATRIX* GetpBoneMatrix(LPSTR _BoneName);

private:

	//�ǉ�
	//���ׂẴt���[���|�C���^�i�[�����֐�
	void CreateFrameArray(LPD3DXFRAME _pFrame);

	// �t���[���Q�Ɨp�z��
	std::vector<MYFRAME*> m_FrameArray; // �S�t���[���Q�Ɣz��
	std::vector<MYFRAME*> m_IntoMeshFrameArray;// ���b�V���R���e�i����̃t���[���Q�Ɣz��

											   //�{�[�����
	LPD3DXFRAME m_pFrameRoot;
	//�A�j���[�V�����R���g���[��
	LPD3DXANIMATIONCONTROLLER m_pAnimController;
	//�q�G�����L�[�N���X�ϐ�
	MY_HIERARCHY m_cHierarchy;

	//�A�j���[�V�����f�[�^�i�[�p�ϐ�(�����͉ςɕύX�����ق�������)
	LPD3DXANIMATIONSET m_pAnimSet[20];

	//���݂̃A�j���[�V�������J�n����Ă���̎���(1/60�b)
	DWORD m_AnimeTime;
	//�A�j���[�V�����X�s�[�h
	FLOAT m_AnimSpeed;

	//���݂̃A�j���[�V�����g���b�N
	DWORD m_CurrentTrack;

	//���݂̃A�j���[�V�����f�[�^�g���b�N
	D3DXTRACK_DESC m_CurrentTrackDesc;

	//�i�s����
	D3DXMATRIX m_World;

	//���b�V���̃}�e���A���֌W

	//�}�e���A���ύX�t���O
	BOOL m_MaterialFlg;

	//�}�e���A���f�[�^
	D3DMATERIAL9 m_Material;

};
