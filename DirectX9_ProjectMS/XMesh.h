//=============================================================================
//
// �X�L�����b�V������ [XMesh.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _SKINMESHX_H_
#define _SKINMESHX_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include <vector>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SKIN_ANIME_SPEED	(60.0f / 4800.0f)
//#define SKIN_ANIME_SPEED	(60.0f / 1500.0f)
#define SKIN_ANIME_WEIGHT	(0.05f)

#define ANIMATION_SET_MAX	(25)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
}PRS;// Pos Rot Scl

struct MYFRAME : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
	// �I�t�Z�b�g�s��(�C���f�b�N�X�t�`��p)
	D3DXMATRIX OffsetMat;
	// �s��e�[�u���̃C���f�b�N�X�ԍ�(�C���f�b�N�X�t�p)
	DWORD OffsetID;
};

//�h�����b�V���R���e�i�[�\����(
//�R���e�i�[���e�N�X�`���𕡐����Ă�悤�Ƀ|�C���^�[�̃|�C���^�[��ǉ�����j
struct MYMESHCONTAINER : public D3DXMESHCONTAINER
{
	LPDIRECT3DTEXTURE9*  ppTextures;
	DWORD dwWeight; //�d�݂̌��i�d�݂Ƃ͒��_�ւ̉e���B�j
	DWORD dwBoneNum; //�{�[���̐�
	LPD3DXBUFFER pBoneBuffer; //�{�[���E�e�[�u��
	D3DXMATRIX** ppBoneMatrix; //�S�Ẵ{�[���̃��[���h�s��̐擪�|�C���^�[
	D3DXMATRIX* pBoneOffsetMatrices; //�t���[���Ƃ��Ẵ{�[���̃��[���h�s��̃|�C���^�[
	LPD3DXMESH pOriMesh; //�I���W�i�����b�V���p
	DWORD NumPaletteEntries; //�p���b�g�T�C�Y
	// Work�p
	//std::vector<D3DXMATRIX> m_WorkBoneMatArray;
	// �e������t���[���ւ̎Q�Ɣz��B�`�掞�ɂ��̃t���[���̍s����g���B
	//std::vector<MYFRAME*> BoneFrameArray;
	MYMESHCONTAINER() {
		ppBoneMatrix = NULL;
		pBoneOffsetMatrices = NULL;
	}
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
// X�t�@�C�����̃A�j���[�V�����K�w��ǂ݉����Ă����N���X��h��������B
// ID3DXAllocateHierarchy�͔h�����邱�Ƒz�肵�Đ݌v����Ă���B
class MY_HIERARCHY : public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY() {}
	STDMETHOD(CreateFrame)(THIS_ LPCSTR, LPD3DXFRAME *);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR, CONST D3DXMESHDATA*, CONST D3DXMATERIAL*,
		CONST D3DXEFFECTINSTANCE*, DWORD, CONST DWORD *, LPD3DXSKININFO, LPD3DXMESHCONTAINER *);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER);
private:
};

// �X�L�����b�V���N���X
class XMesh
{
public:
	//���b�V���N���X�̏�����
	// VOID InitBase(SMESH_DATA_FILE* _pSMeshData);
	//���b�V���̌��݂�Matrix�f�[�^�擾
	bool GetMatrix(D3DXMATRIX* out, int dwCon, int dwBone);

	XMesh();
	~XMesh() {
		Release();
	}
	//�X�L�����b�V����������
	HRESULT Init(LPDIRECT3DDEVICE9 lpD3DDevice, LPSTR pMeshPass);
	HRESULT AllocateBoneMatrix(LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocateAllBoneMatrices(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrameBase);
	VOID RenderMeshContainer(LPDIRECT3DDEVICE9 lpD3DDevice, MYMESHCONTAINER*, MYFRAME*);
	VOID UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	VOID DrawFrame(PDIRECT3DDEVICE9 lpD3DDevice, LPD3DXFRAME pFrameBase);
	//�t���[�����
	VOID FreeAnim(LPD3DXFRAME pFrame);
	//�������
	VOID Release();
	//�X�V����
	VOID Update(void);
	//�`�揈��
	VOID Draw(LPDIRECT3DDEVICE9 lpD3DDevice, D3DXMATRIX _World);
	//�I�u�W�F�N�g�̃A�j���[�V�����ύX( ���b�V���I�u�W�F�N�g�̑���p�ԍ�, �ύX����A�j���[�V�����ԍ� )
	VOID XMesh::ChangeAnim(DWORD _NewAnimNum, FLOAT fShift);
	//���݂̃A�j���[�V�����ԍ��擾
	DWORD GetAnimTrack() { return m_CurrentTrack; }
	//���݂̃A�j���[�V�����^�C��(�A�j���[�V�����J�n����̎���)���擾
	DWORD GetAnimTime() { return m_AnimeTime; }
	//�A�j���[�V�������x���擾
	FLOAT GetAnimSpeed() { return m_AnimSpeed; }
	//�A�j���[�V�������x��ݒ�
	VOID SetAnimSpeed(FLOAT _AnimSpeed) { m_AnimSpeed = _AnimSpeed; }
	//�A�j���[�V�����^�C����ݒ�
	VOID SetAnimTime(DWORD _AnimeTime) { m_AnimeTime = _AnimeTime; }
private:
	//�Ώۂ̃{�[��������
	MYFRAME* SearchBoneFrame(LPSTR _BoneName, D3DXFRAME* _pFrame);
public:
	//�{�[���̃}�g���b�N�X�擾( �{�[���̖��O )
	D3DXMATRIX GetBoneMatrix(LPSTR _BoneName);
	//�{�[���̃}�g���b�N�X�|�C���^�擾( �{�[���̖��O )
	D3DXMATRIX* GetpBoneMatrix(LPSTR _BoneName);

	DWORD	m_dwContainerCount;			// �{�[�����J�E���g
	DWORD	m_dwBoneCount;			// �{�[�����J�E���g
private:
	//�ǉ�
	//���ׂẴt���[���|�C���^�i�[�����֐�
	VOID CreateFrameArray(LPD3DXFRAME _pFrame);
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
	LPD3DXANIMATIONSET m_pAnimSet[ANIMATION_SET_MAX];
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

	// ���[�V�����u�����h�p�ǉ��v���p�e�B
	FLOAT	m_fShiftTime;			// �V�t�g����̂ɂ����鎞��
	FLOAT	m_fCurWeight;			// ���݂̃E�F�C�g����
	DWORD	m_OldTrack;				// �ύX�O�A�j���[�V�����g���b�N
};
#endif