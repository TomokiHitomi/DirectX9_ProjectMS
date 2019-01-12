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
#define TEXTURE_GAME_SELECT00				"data/FACE/white000.png"												// �w�i���
#define TEXTURE_GAME_SELECT01				"data/FACE/white000.png"												// �w�i���
#define TEXTURE_GAME_SELECT02				"data/FACE/white000.png"												// �w�i���
#define TEXTURE_GAME_SELECT03				"data/FACE/white000.png"												// �w�i���
#define TEXTURE_GAME_SELECT04				"data/FACE/illust030.png"												// �C���X�g
#define TEXTURE_GAME_SELECT05				"data/FACE/illust031.png"												// �C���X�g
#define TEXTURE_GAME_SELECT06				"data/FACE/illust032.png"												// �C���X�g
#define TEXTURE_GAME_SELECT07				"data/FACE/illust033.png"												// �C���X�g
#define TEXTURE_GAME_SELECT08				"data/FACE/player000.png"												// �ω���
#define TEXTURE_GAME_SELECT09				"data/FACE/player001.png"												// �ω���


#define TEXTURE_SELECT_SIZE_MIDDLE_X	(2.0*SCREEN_WIDTH/(SCREEN_WIDTH/100))										// ��
#define TEXTURE_SELECT_SIZE_MIDDLE_Y	(2.0*SCREEN_HEIGHT/(SCREEN_HEIGHT/100))										// ��
#define TEXTURE_SELECT_SIZE_BIG_X		(1.1*TEXTURE_SELECT_SIZE_MIDDLE_X)											// �w�i���傫����
#define TEXTURE_SELECT_SIZE_BIG_Y		(1.1*TEXTURE_SELECT_SIZE_MIDDLE_Y)											// �w�i���傫����
#define TEXTURE_SELECT_SIZE_SMALL_X		(2.5*SCREEN_WIDTH/(SCREEN_WIDTH/100)/5)										// �w�i����������
#define TEXTURE_SELECT_SIZE_SMALL_Y		(2.5*SCREEN_HEIGHT/(SCREEN_HEIGHT/100)/5)									// �w�i����������


#define TEXTURE_SELECT_SIZE_VERTEX_X	(0.55)
#define TEXTURE_SELECT_SIZE_VERTEX_BASE_X	(0.5)

#define TEXTURE_SELECT00_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT00_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// ���� (*33)
#define TEXTURE_SELECT01_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT01_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// ���� (*33)
#define TEXTURE_SELECT02_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT02_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// ���� (*33)
#define TEXTURE_SELECT03_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT03_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// ���� (*33)
#define TEXTURE_SELECT04_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT04_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// ���� (*33)
#define TEXTURE_SELECT05_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT05_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// ���� (*33)
#define TEXTURE_SELECT06_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT06_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// ���� (*33)
#define TEXTURE_SELECT07_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT07_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// ���� (*33)
#define TEXTURE_SELECT08_SIZE_X				(TEXTURE_SELECT_SIZE_SMALL_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_Y				(TEXTURE_SELECT_SIZE_SMALL_Y/2*SCREEN_SCALE)											// ���� (*33)
#define TEXTURE_SELECT09_SIZE_X				(TEXTURE_SELECT_SIZE_SMALL_X/2*SCREEN_SCALE)											// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_Y				(TEXTURE_SELECT_SIZE_SMALL_Y/2*SCREEN_SCALE)											// ���� (*33)

#define TEXTURE_SELECT08_SIZE_MOVE_X		((float)SCREEN_WIDTH/SCREEN_WIDTH/10)									// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_Y		((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)									// ���� (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)									// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)									// ���� (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_X		((float)SCREEN_WIDTH/SCREEN_WIDTH/10)									// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_Y		((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)									// ���� (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)									// �e�N�X�`���T�C�Y (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)									// ���� (*33)

#define TEXTURE_SELECT00_POSITION_OFFSET	(SCREEN_WIDTH/2+SCREEN_WIDTH/12.5)
#define TEXTURE_SELECT00_POSITION_DISTANCE	(SCREEN_WIDTH/6)
#define TEXTURE_SELECT_POSITION_OFFSET_Y	(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*11/2*SCREEN_SCALE)

#define TEXTURE_SELECT00_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT00_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT01_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT01_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT02_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// �e�N�X�`�����W
#define TEXTURE_SELECT02_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT03_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT03_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)

#define TEXTURE_SELECT04_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// �e�N�X�`�����W
#define TEXTURE_SELECT04_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT05_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT05_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT06_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// �e�N�X�`�����W
#define TEXTURE_SELECT06_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT07_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// �e�N�X�`�����W
#define TEXTURE_SELECT07_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)

#define TEXTURE_SELECT08_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// �e�N�X�`�����W
#define TEXTURE_SELECT08_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT09_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// �e�N�X�`�����W
#define TEXTURE_SELECT09_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// ���� (*33)



#define TEXTURE_SELECT_MOVE_OFFSET_X		(TEXTURE_SELECT00_POSITION_OFFSET-(SCREEN_WIDTH/SCREEN_WIDTH)*65)					// ���� (*33)
#define TEXTURE_SELECT_MOVE_OFFSET_Y		(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*10/2*SCREEN_SCALE)												// ���� (*33)

#define TEXTURE_SELECT_MOVE_DISTANCE_X		(SCREEN_HEIGHT/SCREEN_HEIGHT*150)
#define TEXTURE_SELECT00_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)				// �e�N�X�`�����W
#define TEXTURE_SELECT00_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT01_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE)				// �e�N�X�`�����W
#define TEXTURE_SELECT01_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT02_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X)													// �e�N�X�`�����W
#define TEXTURE_SELECT02_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT03_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X+TEXTURE_SELECT00_POSITION_DISTANCE)				// �e�N�X�`�����W
#define TEXTURE_SELECT03_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)
#define TEXTURE_SELECT04_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)				// �e�N�X�`�����W
#define TEXTURE_SELECT04_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// ���� (*33)

#define TEXTURE_SELECT_COLOR_DEFAULT_R		(255)													// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_SELECT_COLOR_DEFAULT_G		(255)													// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_SELECT_COLOR_DEFAULT_B		(255)													// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_SELECT_COLOR_DEFAULT_A		(255)													// �e�N�X�`�����_�J���[�ω��O
#define TEXTURE_SELECT_COLOR_CHANGE_R		(255)													// �e�N�X�`�����_�J���[�ω���
#define TEXTURE_SELECT_COLOR_CHANGE_G		(255)													// �e�N�X�`�����_�J���[�ω���
#define TEXTURE_SELECT_COLOR_CHANGE_B		(0)														// �e�N�X�`�����_�J���[�ω���
#define TEXTURE_SELECT_COLOR_CHANGE_A		(255)													// �e�N�X�`�����_�J���[�ω���




#define ANIM_PATTERN_NUM_SELECT				(TEXTURE_SELECT00_PATTERN_DIVIDE_X*TEXTURE_SELECT00_PATTERN_DIVIDE_Y)		// �A�j���[�V�����p�^�[���� (*34)
#define TIME_ANIMATION_SELECT				(4)																		// �A�j���[�V�����̐؂�ւ��J�E���g (*34)
#define NUM_SELECT							(10)
#define NUM_SELECT_MAX						(4)

//=============================================================================
//
//SELECT�\����
//
//=============================================================================
class Selectface : public ObjectManager
{
private:
	enum SELECT_PLAYER
	{
		SELECT_1P,
		SELECT_2P,
		SELECT_MAX
	};
	// ����t���O
	bool bSelect[SELECT_MAX];

public:
	struct SelectParts
	{
		LPDIRECT3DTEXTURE9		pTexture;							// �e�N�X�`���ւ̃|���S�� (*33)
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				posSelect;																					// �v���C���[�̈ړ���
		VERTEX_2D				vertexSelectWk[NUM_VERTEX];																	// ���_���i�[���[�N
		D3DXVECTOR2				TextureSelectSize;
		int						count;
		bool					UseSelect;																					// true:�g�p  false:���g�p
	};

	SelectParts Select[NUM_SELECT];

	HRESULT MakeVertexSelect(int CreateSelectCount);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVertexSelect(int CreateSelectCount);
	void SetTextureSelect(int CreateSelectCount);
	Selectface();
	~Selectface();

private:
	void SetChar(void);
	int SearchChar(int* nSMP);
};

int SearchCharSelect(int nNum);

#endif
