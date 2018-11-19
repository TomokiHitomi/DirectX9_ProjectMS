//=============================================================================
//
// �{�b�N�X���� [box.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _BOX_H_
#define _BOX_H_

/*******************************************************************************
* �C���N���[�h
*******************************************************************************/
#include "stage.h"
#include "plane.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOX_TEXTURE				"data/TEXTURE/box3.png"						// �ǂݍ��ރe�N�X�`���t�@�C����

// �e�N�X�`����������
#define BOX_TEXTURE_PATTERN_DIVIDE_X	(1)
#define BOX_TEXTURE_PATTERN_DIVIDE_Y	(1)
// �e�N�X�`�������p�^�[��
#define BOX_TEXTURE_PATTERN_NU	(BOX_TEXTURE_PATTERN_DIVIDE_X*BOX_TEXTURE_PATTERN_DIVIDE_Y)



// �T�C�Y
#define	BOX_SIZE_X		(10.0f / 2)
#define	BOX_SIZE_Y		(10.0f / 2)
#define	BOX_SIZE		(8.0f / 2)

// �ő吔
#define BOX_X_MAX		(15)
#define BOX_Z_MAX		(15)
#define BOX_Y_MAX		(5)

#define BOX_MARGIN		(20.0f)
#define BOX_HEIGHT		(10.0f)

// �ő吔
//#define BOX_MAX		(((PLANE_X_MAX) * 2 + (PLANE_Y_MAX) * 2) * BOX_Y_MAX)
#define BOX_MAX		((BOX_X_MAX * 2 + BOX_Z_MAX * 2) * BOX_Y_MAX + BOX_X_MAX * BOX_Z_MAX)


#define BOX_ROT_SPEED	(0.03f)

#define BOX_ALPHA		(30)
#define BOX_COLOR_SPEED	(PLANE_COLOR_SPEED)
#define BOX_COLOR_MAX	(PLANE_COLOR_MAX)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Box
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
		float		angle;
		D3DCOLOR	diffuse;
	}INSTANCE_PLANE;

	LPDIRECT3DTEXTURE9				pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// �C���X�^���X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// ���_�錾

	// �V�F�[�_�[�֘A
	LPD3DXEFFECT					pEffect;

	// 
	float							fRot;
	float							fColor;
	bool							bColor;


	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
public:

	Box();
	~Box();
	void Update(void);
	void Draw(void);
	void Release(void);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
