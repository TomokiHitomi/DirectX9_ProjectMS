//=============================================================================
//
// �v���[������ [plane.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "stage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PLANE_TEXTURE				"data/TEXTURE/white_1x1.png"						// �ǂݍ��ރe�N�X�`���t�@�C����

// �e�N�X�`����������
#define PLANE_TEXTURE_PATTERN_DIVIDE_X	(1)
#define PLANE_TEXTURE_PATTERN_DIVIDE_Y	(1)
// �e�N�X�`�������p�^�[��\
#define PLANE_TEXTURE_PATTERN_NU	(PLANE_TEXTURE_PATTERN_DIVIDE_X*PLANE_TEXTURE_PATTERN_DIVIDE_Y)

#define PLANE_MARGIN	(0.8f)

// �T�C�Y
#define	PLANE_SIZE_X		(10.0f / 2)
#define	PLANE_SIZE_Y		(10.0f / 2)

// �ő吔
#define PLANE_X_MAX		(25)
#define PLANE_Y_MAX		(25)

// �ő吔
#define PLANE_MAX			(PLANE_X_MAX * PLANE_Y_MAX)

#define PLANE_COLOR_SPEED	(0.003f)
#define PLANE_COLOR_MAX		(0.1f)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Plane
{
private:
	typedef struct
	{
		D3DXVECTOR4 vtx;
		D3DXVECTOR2 tex;
	}VERTEX_PLANE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DCOLOR	diffuse;
	}INSTANCE_PLANE;

	LPDIRECT3DTEXTURE9				pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// �C���X�^���X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// ���_�錾

	// �V�F�[�_�[�֘A
	LPD3DXEFFECT					pEffect;

	float							fColor;
	bool							bColor;


	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
public:

	Plane();
	~Plane();
	void Update(void);
	void Draw(void);
	void Release(void);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
