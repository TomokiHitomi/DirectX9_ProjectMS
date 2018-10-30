//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	TEXTURE_EFFECT	"data/TEXTURE/effect000.jpg"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PARTICLE_TEXTURE	"data/TEXTURE/effect.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define PARTICLE_SHADER_FILE			"data/TEXTURE/SHADER/sprite.fx"

// �e�N�X�`����������
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(1)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)
// �e�N�X�`�������p�^�[��
#define TEXTURE_PATTERN_NU_EFFECT		(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)

// �T�C�Y
#define	PARTICLE_SIZE_X		(1.0f)
#define	PARTICLE_SIZE_Y		(1.0f)

// �ő吔
#define PARTICLE_MAX		(300000)

// �ړ��X�s�[�h
#define PARTICLE_MOVE_SPEED		(0.1f)

// �P�t���[���̐�����
#define PARTICLE_SET			(50)

class Particle
{
public:
	Particle();
	~Particle();
	void Init();
	void Uninit();
	void Updata();
	void Draw();
};

class ParticleManager
{
};

typedef struct
{
	D3DXVECTOR3				posEffect;				// �n�ʂ̈ʒu
	D3DXVECTOR3				rotEffect;				// �n�ʂ̌���(��])
	D3DXVECTOR3				sclEffect;				// �n�ʂ̑傫��(�X�P�[��)

	D3DXVECTOR2				vec2Size;

	D3DXCOLOR				colorEffect;

	int						nUseCount;				// ���ŃJ�E���g
	int						nTex;

	float					fSizeChange;
	float					fAlphaChange;
	FLOAT					fSize;

	bool					bUse;					// �g�p�t���O
}EFFECT;

typedef struct
{
	D3DXVECTOR4 vtx;
	D3DXVECTOR2 tex;
}VERTEX_PLANE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DCOLOR	diffuse;
	D3DXVECTOR3 vec;
	float		move;
}INSTANCING_PLANE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(int nType);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(int nTex, D3DXVECTOR2 vec2Size, D3DXCOLOR color, D3DXVECTOR3 vecPos, float fSizeChange, float fAlphaChange);

#endif
