//=============================================================================
//
// プレイヤー処理 [selectface.h]
// Author : GP12A295 09 樺澤広之
//
//=============================================================================
#ifndef _SELECTFACE_H_
#define _SELECTFACE_H_

#include "main.h"
#include "object.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================
#define TEXTURE_GAME_SELECT00				"data/FACE/white000.png"												// 背景大丸
#define TEXTURE_GAME_SELECT01				"data/FACE/white000.png"												// 背景大丸
#define TEXTURE_GAME_SELECT02				"data/FACE/white000.png"												// 背景大丸
#define TEXTURE_GAME_SELECT03				"data/FACE/white000.png"												// 背景大丸
#define TEXTURE_GAME_SELECT04				"data/FACE/illust030.png"												// イラスト
#define TEXTURE_GAME_SELECT05				"data/FACE/illust031.png"												// イラスト
#define TEXTURE_GAME_SELECT06				"data/FACE/illust032.png"												// イラスト
#define TEXTURE_GAME_SELECT07				"data/FACE/illust033.png"												// イラスト
#define TEXTURE_GAME_SELECT08				"data/FACE/player000.png"												// 変化丸
#define TEXTURE_GAME_SELECT09				"data/FACE/player001.png"												// 変化丸


#define TEXTURE_SELECT_SIZE_MIDDLE_X	(2.0*SCREEN_WIDTH/(SCREEN_WIDTH/100))										// 顔
#define TEXTURE_SELECT_SIZE_MIDDLE_Y	(2.0*SCREEN_HEIGHT/(SCREEN_HEIGHT/100))										// 顔
#define TEXTURE_SELECT_SIZE_BIG_X		(1.1*TEXTURE_SELECT_SIZE_MIDDLE_X)											// 背景側大きい丸
#define TEXTURE_SELECT_SIZE_BIG_Y		(1.1*TEXTURE_SELECT_SIZE_MIDDLE_Y)											// 背景側大きい丸
#define TEXTURE_SELECT_SIZE_SMALL_X		(2.5*SCREEN_WIDTH/(SCREEN_WIDTH/100)/5)										// 背景側小さい丸
#define TEXTURE_SELECT_SIZE_SMALL_Y		(2.5*SCREEN_HEIGHT/(SCREEN_HEIGHT/100)/5)									// 背景側小さい丸


#define TEXTURE_SELECT_SIZE_VERTEX_X	(0.55)
#define TEXTURE_SELECT_SIZE_VERTEX_BASE_X	(0.5)

#define TEXTURE_SELECT00_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// テクスチャサイズ (*33)
#define TEXTURE_SELECT00_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// 同上 (*33)
#define TEXTURE_SELECT01_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// テクスチャサイズ (*33)
#define TEXTURE_SELECT01_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// 同上 (*33)
#define TEXTURE_SELECT02_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// テクスチャサイズ (*33)
#define TEXTURE_SELECT02_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// 同上 (*33)
#define TEXTURE_SELECT03_SIZE_X				(TEXTURE_SELECT_SIZE_BIG_X/2*SCREEN_SCALE)												// テクスチャサイズ (*33)
#define TEXTURE_SELECT03_SIZE_Y				(TEXTURE_SELECT_SIZE_BIG_Y/2*SCREEN_SCALE)												// 同上 (*33)
#define TEXTURE_SELECT04_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT04_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// 同上 (*33)
#define TEXTURE_SELECT05_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT05_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// 同上 (*33)
#define TEXTURE_SELECT06_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT06_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// 同上 (*33)
#define TEXTURE_SELECT07_SIZE_X				(TEXTURE_SELECT_SIZE_MIDDLE_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT07_SIZE_Y				(TEXTURE_SELECT_SIZE_MIDDLE_Y/2*SCREEN_SCALE)											// 同上 (*33)
#define TEXTURE_SELECT08_SIZE_X				(TEXTURE_SELECT_SIZE_SMALL_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT08_SIZE_Y				(TEXTURE_SELECT_SIZE_SMALL_Y/2*SCREEN_SCALE)											// 同上 (*33)
#define TEXTURE_SELECT09_SIZE_X				(TEXTURE_SELECT_SIZE_SMALL_X/2*SCREEN_SCALE)											// テクスチャサイズ (*33)
#define TEXTURE_SELECT09_SIZE_Y				(TEXTURE_SELECT_SIZE_SMALL_Y/2*SCREEN_SCALE)											// 同上 (*33)

#define TEXTURE_SELECT08_SIZE_MOVE_X		((float)SCREEN_WIDTH/SCREEN_WIDTH/10)									// テクスチャサイズ (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_Y		((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)									// 同上 (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)									// テクスチャサイズ (*33)
#define TEXTURE_SELECT08_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)									// 同上 (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_X		((float)SCREEN_WIDTH/SCREEN_WIDTH/10)									// テクスチャサイズ (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_Y		((float)SCREEN_HEIGHT/SCREEN_HEIGHT/10)									// 同上 (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_X	((float)SCREEN_WIDTH/SCREEN_WIDTH*2)									// テクスチャサイズ (*33)
#define TEXTURE_SELECT09_SIZE_MOVE_OFFSET_Y	((float)SCREEN_HEIGHT/SCREEN_HEIGHT*2)									// 同上 (*33)

#define TEXTURE_SELECT00_POSITION_OFFSET	(SCREEN_WIDTH/2+SCREEN_WIDTH/12.5)
#define TEXTURE_SELECT00_POSITION_DISTANCE	(SCREEN_WIDTH/6)
#define TEXTURE_SELECT_POSITION_OFFSET_Y	(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*11/2*SCREEN_SCALE)

#define TEXTURE_SELECT00_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// テクスチャ座標
#define TEXTURE_SELECT00_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT01_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// テクスチャ座標
#define TEXTURE_SELECT01_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT02_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// テクスチャ座標
#define TEXTURE_SELECT02_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT03_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// テクスチャ座標
#define TEXTURE_SELECT03_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)

#define TEXTURE_SELECT04_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE*2)														// テクスチャ座標
#define TEXTURE_SELECT04_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT05_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET-TEXTURE_SELECT00_POSITION_DISTANCE)														// テクスチャ座標
#define TEXTURE_SELECT05_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT06_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET)														// テクスチャ座標
#define TEXTURE_SELECT06_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT07_POSITION_X			(TEXTURE_SELECT00_POSITION_OFFSET+TEXTURE_SELECT00_POSITION_DISTANCE)														// テクスチャ座標
#define TEXTURE_SELECT07_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)

#define TEXTURE_SELECT08_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// テクスチャ座標
#define TEXTURE_SELECT08_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT09_POSITION_X			(TEXTURE_SELECT00_POSITION_X)														// テクスチャ座標
#define TEXTURE_SELECT09_POSITION_Y			(TEXTURE_SELECT_POSITION_OFFSET_Y)													// 同上 (*33)



#define TEXTURE_SELECT_MOVE_OFFSET_X		(TEXTURE_SELECT00_POSITION_OFFSET-(SCREEN_WIDTH/SCREEN_WIDTH)*65)					// 同上 (*33)
#define TEXTURE_SELECT_MOVE_OFFSET_Y		(SCREEN_HEIGHT/(SCREEN_HEIGHT/100)*10/2*SCREEN_SCALE)												// 同上 (*33)

#define TEXTURE_SELECT_MOVE_DISTANCE_X		(SCREEN_HEIGHT/SCREEN_HEIGHT*150)
#define TEXTURE_SELECT00_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)				// テクスチャ座標
#define TEXTURE_SELECT00_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT01_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE)				// テクスチャ座標
#define TEXTURE_SELECT01_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT02_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X)													// テクスチャ座標
#define TEXTURE_SELECT02_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT03_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X+TEXTURE_SELECT00_POSITION_DISTANCE)				// テクスチャ座標
#define TEXTURE_SELECT03_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// 同上 (*33)
#define TEXTURE_SELECT04_MOVE_X				(TEXTURE_SELECT_MOVE_OFFSET_X-TEXTURE_SELECT00_POSITION_DISTANCE*2)				// テクスチャ座標
#define TEXTURE_SELECT04_MOVE_Y				(TEXTURE_SELECT_MOVE_OFFSET_Y)													// 同上 (*33)

#define TEXTURE_SELECT_COLOR_DEFAULT_R		(255)													// テクスチャ頂点カラー変化前
#define TEXTURE_SELECT_COLOR_DEFAULT_G		(255)													// テクスチャ頂点カラー変化前
#define TEXTURE_SELECT_COLOR_DEFAULT_B		(255)													// テクスチャ頂点カラー変化前
#define TEXTURE_SELECT_COLOR_DEFAULT_A		(255)													// テクスチャ頂点カラー変化前
#define TEXTURE_SELECT_COLOR_CHANGE_R		(255)													// テクスチャ頂点カラー変化後
#define TEXTURE_SELECT_COLOR_CHANGE_G		(255)													// テクスチャ頂点カラー変化後
#define TEXTURE_SELECT_COLOR_CHANGE_B		(0)														// テクスチャ頂点カラー変化後
#define TEXTURE_SELECT_COLOR_CHANGE_A		(255)													// テクスチャ頂点カラー変化後




#define ANIM_PATTERN_NUM_SELECT				(TEXTURE_SELECT00_PATTERN_DIVIDE_X*TEXTURE_SELECT00_PATTERN_DIVIDE_Y)		// アニメーションパターン数 (*34)
#define TIME_ANIMATION_SELECT				(4)																		// アニメーションの切り替わるカウント (*34)
#define NUM_SELECT							(10)
#define NUM_SELECT_MAX						(4)

//=============================================================================
//
//SELECT構造体
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
	// 決定フラグ
	bool bSelect[SELECT_MAX];

public:
	struct SelectParts
	{
		LPDIRECT3DTEXTURE9		pTexture;							// テクスチャへのポリゴン (*33)
		LPDIRECT3DTEXTURE9		Texture;
		D3DXVECTOR3				posSelect;																					// プレイヤーの移動量
		VERTEX_2D				vertexSelectWk[NUM_VERTEX];																	// 頂点情報格納ワーク
		D3DXVECTOR2				TextureSelectSize;
		int						count;
		bool					UseSelect;																					// true:使用  false:未使用
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
