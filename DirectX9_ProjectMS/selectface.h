//=============================================================================
//
// �v���C���[���� [selectface.h]
// Author : GP12A295 09 ���V�L�V
//
//=============================================================================
#ifndef _SELECTFACE_H_
#define _SELECTFACE_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// �}�N����`
//
//=============================================================================
#define TEXTURE_GAME_SELECT00				"data/FACE/white000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT01				"data/FACE/white000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT02				"data/FACE/white000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT03				"data/FACE/white000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT04				"data/FACE/illust000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT05				"data/FACE/illust001.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT06				"data/FACE/illust002.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT07				"data/FACE/illust003.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT08				"data/FACE/white000.png"												// �T���v���p�摜 (*33)
#define TEXTURE_GAME_SELECT09				"data/FACE/white000.png"												// �T���v���p�摜 (*33)

#define TEXTURE_SELECT_OFFSET_SIZE_X	(SCREEN_WIDTH/(SCREEN_WIDTH/100))
#define TEXTURE_SELECT_OFFSET_SIZE_Y	(SCREEN_HEIGHT/(SCREEN_HEIGHT/100))													// ���� (*33)

#define TEXTURE_SELECT_SIZE_VERTEX_X	(0.55)
#define TEXTURE_SELECT_SIZE_VERTEX_BASE_X	(0.5)

#define TEXTURE_SELECT00_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X*1.1)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT00_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y*1.1)													// ���� (*33)
#define TEXTURE_SELECT01_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X*1.1)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT01_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y*1.1)													// ���� (*33)
#define TEXTURE_SELECT02_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X*1.1)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT02_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y*1.1)													// ���� (*33)
#define TEXTURE_SELECT03_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X*1.1)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT03_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y*1.1)													// ���� (*33)
#define TEXTURE_SELECT04_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT04_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y)													// ���� (*33)
#define TEXTURE_SELECT05_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT05_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y)													// ���� (*33)
#define TEXTURE_SELECT06_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT06_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y)													// ���� (*33)
#define TEXTURE_SELECT07_SIZE_X			(TEXTURE_SELECT_OFFSET_SIZE_X)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT07_SIZE_Y			(TEXTURE_SELECT_OFFSET_SIZE_Y)													// ���� (*33)
#define TEXTURE_SELECT08_SIZE_X			(SCREEN_WIDTH/(SCREEN_WIDTH/100)/5)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)/5)													// ���� (*33)
#define TEXTURE_SELECT09_SIZE_X			(SCREEN_WIDTH/(SCREEN_WIDTH/100)/5)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)/5)													// ���� (*33)

#define TEXTURE_SELECT08_SIZE_MOVE_X	((float)SCREEN_WIDTH/SCREEN_WIDTH/10)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)													// ���� (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)													// ���� (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_X	((float)SCREEN_WIDTH/SCREEN_WIDTH/10)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)													// ���� (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)													// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)													// ���� (*33)

#define TEXTURE_SELECT00_POSITION_OFFSET	(SCREEN_WIDTH/2+SCREEN_WIDTH/12.5)
#define TEXTURE_SELECT00_POSITION_DISTANCE	(SCREEN_WIDTH/6)

//#define TEXTURE_SELECT00_POSITION_X			(SCREEN_WIDTH/2.9)														// �e�N�X�`�����W
//#define TEXTURE_SELECT00_POSITION_Y			(SCREEN_HEIGHT/1.0675)													// ���� (*33)
#define TEXTURE_SELECT00_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT00_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT01_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT01_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT02_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// �e�N�X�`�����W
#define TEXTURE_SELECT02_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT03_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT03_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)

#define TEXTURE_SELECT04_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT04_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT05_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT05_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT06_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// �e�N�X�`�����W
#define TEXTURE_SELECT06_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT07_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT07_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)

#define TEXTURE_SELECT08_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// �e�N�X�`�����W
#define TEXTURE_SELECT08_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)
#define TEXTURE_SELECT09_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// �e�N�X�`�����W
#define TEXTURE_SELECT09_POSITION_Y			(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*9)													// ���� (*33)

#define TEXTURE_SELECT_MOVE_OFFSET_X		(TEXTURE_SELECT00_POSITION_OFFSET-(SCREEN_WIDTH/SCREEN_WIDTH)*40)													// ���� (*33)
#define TEXTURE_SELECT_MOVE_OFFSET_Y		(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*8.6)													// ���� (*33)

#define TEXTURE_SELECT_MOVE_DISTANCE_X		(TEXTURE_SELECT_MOVE_OFFSET_X/12.5)
#define TEXTURE_SELECT00_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT00_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT01_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT01_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT02_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X)														// �e�N�X�`�����W
#define TEXTURE_SELECT02_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT03_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X+TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT03_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT04_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT04_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_DEFAULT_R		(255)														// �e�N�X�`�����W
#define TEXTURE_SELECT_COLOR_DEFAULT_G		(255)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_DEFAULT_B		(255)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_DEFAULT_A		(255)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_CHANGE_R		(255)														// �e�N�X�`�����W
#define TEXTURE_SELECT_COLOR_CHANGE_G		(255)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_CHANGE_B		(0)													// ���� (*33)
#define TEXTURE_SELECT_COLOR_CHANGE_A		(255)													// ���� (*33)


#define TEXTURE_SELECT00_PATTERN_DIVIDE_X	(1)																		// �A�j���p�^�[���̃e�N�X�`�����������iX) (*34)
#define TEXTURE_SELECT00_PATTERN_DIVIDE_Y	(1)																		// �A�j���p�^�[���̃e�N�X�`�����������iY) (*34)
#define TEXTURE_SELECT00_PATTERN_DIVIDE_Y	(1)																		// �A�j���p�^�[���̃e�N�X�`�����������iY) (*34)
#define TEXTURE_SELECT00_COOLDOWN			(10)


#define ANIM_PATTERN_NUM_SELECT				(TEXTURE_SELECT00_PATTERN_DIVIDE_X*TEXTURE_SELECT00_PATTERN_DIVIDE_Y)		// �A�j���[�V�����p�^�[���� (*34)
#define TIME_ANIMATION_SELECT				(4)																		// �A�j���[�V�����̐؂�ւ��J�E���g (*34)
#define NUM_SELECT							(10)
//=============================================================================
//
//SELECT�\����
//
//=============================================================================
//typedef struct
//{
//	LPDIRECT3DTEXTURE9		Texture;
//	D3DXVECTOR3				posSelect;																					// �v���C���[�̈ړ���
//	VERTEX_2D				vertexSelectWk[NUM_VERTEX];																	// ���_���i�[���[�N
//	D3DXVECTOR2				TextureSelectSize;
//	int						count;
//	bool					UseSelect;																					// true:�g�p  false:���g�p
//
//}SELECT[NUM_SELECT];
class Selectface : public ObjectManager
{
public:
	struct SelectParts
	{
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				posSelect;																					// �v���C���[�̈ړ���
		VERTEX_2D				vertexSelectWk[NUM_VERTEX];																	// ���_���i�[���[�N
		D3DXVECTOR2				TextureSelectSize;
		int						count;
		bool					UseSelect;																					// true:�g�p  false:���g�p
	};

	SelectParts Select[NUM_SELECT];

	//LPDIRECT3DTEXTURE9		Texture;
	//D3DXVECTOR3				posSelect;																					// �v���C���[�̈ړ���
	//VERTEX_2D				vertexSelectWk[NUM_VERTEX];																	// ���_���i�[���[�N
	//D3DXVECTOR2				TextureSelectSize;
	//int						count;
	//bool					UseSelect;																					// true:�g�p  false:���g�p


	HRESULT MakeVertexSelect(int CreateSelectCount);
	HRESULT Init(void);
	Selectface *GetSelect(int Number);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVertexSelect(int CreateSelectCount);
	void SetTextureSelect(int CreateSelectCount);
	Selectface();
	~Selectface();
};
//=============================================================================
//
// �v���g�^�C�v�錾
//
//=============================================================================
//HRESULT MakeVertexSelect(int CreateSelectCount);
//HRESULT InitSelect(int type);
//void UninitSelect(void);
//void UpdateSelect(void);
//void DrawSelect(void);
//SELECT *GetSelect(int Number);
//void SetTextureSelect(int CreateSelectCount);


#endif
