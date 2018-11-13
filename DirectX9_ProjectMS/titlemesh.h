//=============================================================================
//
// �v���C���[���� [titlemesh.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _TITLEMESH_H_
#define _TITLEMESH_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_TITLEMESH_000					"data/TEXTURE/logo001.png"											// ���S

#define FIELD_NUM_X		(100)
#define FIELD_NUM_Z		(100)

#define FIELD_BLOCK_SIZE_X		(50.0f)
#define FIELD_BLOCK_SIZE_Z		(50.0f)

#define FIELD_RANGE_X		(FIELD_NUM_X*FIELD_BLOCK_SIZE_X)
#define FIELD_RANGE_Z		(FIELD_NUM_Z*FIELD_BLOCK_SIZE_Z)

#define TEXTURE_TITLEMESH_PIXEL000_X			(1167)																// �s�N�Z���T�C�Y
#define TEXTURE_TITLEMESH_PIXEL000_Y			(1152)																// �s�N�Z���T�C�Y

#define TEXTURE_TITLEMESH_SIZE000_LATE_X		(1.0)																// �g��{��
#define TEXTURE_TITLEMESH_SIZE000_LATE_Y		(0.6)																// �g��{��
#define TEXTURE_TITLEMESH_SIZE000_X				(TEXTURE_TITLEMESH_SIZE000_LATE_X*TEXTURE_TITLEMESH_PIXEL000_X)		// �T�C�Y
#define TEXTURE_TITLEMESH_SIZE000_Y				(TEXTURE_TITLEMESH_SIZE000_LATE_Y*TEXTURE_TITLEMESH_PIXEL000_Y)		// �T�C�Y
#define TEXTURE_TITLEMESH_POSITION000_X			(0)													// �|�W�V����
#define TEXTURE_TITLEMESH_POSITION000_Y			(0)												// �|�W�V����
#define TEXTURE_TITLEMESH_POSITION000_Z			(0)												// �|�W�V����
#define TEXTURE_TITLEMESH_ROTATION000_X			(0)													// �|�W�V����
#define TEXTURE_TITLEMESH_ROTATION000_Y			(0)												// �|�W�V����
#define TEXTURE_TITLEMESH_ROTATION000_Z			(0)												// �|�W�V����

#define TEXTURE_TITLEMESH_COLOR_DEFAULT_R		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_G		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_B		(255)																// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_TITLEMESH_COLOR_DEFAULT_A		(255)																// �e�N�X�`�����_�J���[�ω��O
#define NUM_TITLEMESH							(1)																	// �e�N�X�`���̐�
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Titlemesh : public ObjectManager
{
public:


	struct TitlemeshParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				Pos;									// �v���C���[�̈ړ���
		D3DXVECTOR3				Rot;									// �v���C���[�̈ړ���
		D3DXVECTOR3				Scale;									// �v���C���[�̈ړ���
		D3DXMATRIX				WorldMatrix;							// ���[���h�}�g���b�N�X
		LPD3DXMESH				pD3DXMesh;								// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER			pD3DXBuffMat;							// �}�e���A�����ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9	lpD3DVertexBuffer;
		LPDIRECT3DINDEXBUFFER9	lpD3DIndexBuffer;						// Direct3DIndexBuffer8 �I�u�W�F�N�g
		LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		LPDIRECT3DINDEXBUFFER9	pD3DIdxBuff;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		DWORD					nNumMatGround;							// �}�e���A�����̐�
		VERTEX_2D				vertexWk[NUM_VERTEX];					// ���_���i�[���[�N
		D3DXVECTOR2				TextureSize;
		int						NumVertex;								// �����_��
		int						NumVertexIndex;							// ���C���f�b�N�X��
		int						NumPolygon;								// ���|���S����
		int						NumBlockX;
		int						NumBlockZ;
		float					BlockSizeX;
		float					BlockSizeZ;
		int						Count;
		int						Alfa;
		bool					Flash;
		bool					Use;									// true:�g�p  false:���g�p
		LPDIRECT3DTEXTURE9		pD3DTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
	};
	TitlemeshParts TitleMesh[NUM_TITLEMESH];
	void SetVertexTitlemesh(int CreateCount);
	void SetTextureTitlemesh(int i);
	HRESULT MakeVertexTitlemesh(int i);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	Titlemesh();
	~Titlemesh();
};


#endif
