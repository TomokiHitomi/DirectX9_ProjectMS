//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	TEXTURE_EFFECT	"data/TEXTURE/effect000.jpg"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PARTICLE_TEXTURE				"data/TEXTURE/effect.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
//#define PARTICLE_SHADER_FILE			"data/SHADER/sprite.fx"
//#define PARTICLE_SHADER_FILE			"data/SHADER/plane.fx"

// �e�N�X�`����������
#define PARTICLE_TEXTURE_PATTERN_DIVIDE_X	(1)
#define PARTICLE_TEXTURE_PATTERN_DIVIDE_Y	(1)
// �e�N�X�`�������p�^�[��
#define  PARTICLE_TEXTURE_PATTERN_NU		(PARTICLE_TEXTURE_PATTERN_DIVIDE_X*PARTICLE_TEXTURE_PATTERN_DIVIDE_Y)

// �T�C�Y
#define	PARTICLE_SIZE_X		(1.0f)
#define	PARTICLE_SIZE_Y		(1.0f)

// �ő吔
#define PARTICLE_MAX		(300000)

// �ړ��X�s�[�h
#define PARTICLE_MOVE_SPEED		(0.1f)

// �P�t���[���̐�����
#define PARTICLE_SET			(500)


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Particle
{
private:
	LPDIRECT3DTEXTURE9				pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// �C���X�^���X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// ���_�錾

	// �V�F�[�_�[�֘A
	LPD3DXEFFECT					pEffect;

	int								nCount;
	int								nColor;
	float							fMove;

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
	}INSTANCE_PLANE;

	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
public:
	// �R���X�g���N�^
	Particle(void);
	//�f�X�g���N�^
	~Particle(void);
	// ����������
	HRESULT	Init(void);
	// �������
	void	Release(void);
	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);
	// �ݒu����
	void	Set(int value, D3DXVECTOR3 pos, D3DXCOLOR color);
};

class ParticleManager : public ObjectManager
{
private:
	Particle* pParticle;
public:
	// �R���X�g���N�^
	ParticleManager(void);
	//�f�X�g���N�^
	~ParticleManager(void);
	// ����������
	HRESULT	Init(void);
	// �������
	void	Release(void);
	// �X�V����
	void	Update(void);
	// �`�揈��
	void	Draw(void);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
