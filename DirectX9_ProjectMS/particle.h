//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	TEXTURE_EFFECT	"data/TEXTURE/effect000.jpg"						// 読み込むテクスチャファイル名
#define	PARTICLE_TEXTURE	"data/TEXTURE/effect.png"						// 読み込むテクスチャファイル名
#define PARTICLE_SHADER_FILE			"data/TEXTURE/SHADER/sprite.fx"

// テクスチャ内分割数
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT	(1)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT	(1)
// テクスチャ分割パターン
#define TEXTURE_PATTERN_NU_EFFECT		(TEXTURE_PATTERN_DIVIDE_X_EFFECT*TEXTURE_PATTERN_DIVIDE_Y_EFFECT)

// サイズ
#define	PARTICLE_SIZE_X		(1.0f)
#define	PARTICLE_SIZE_Y		(1.0f)

// 最大数
#define PARTICLE_MAX		(300000)

// 移動スピード
#define PARTICLE_MOVE_SPEED		(0.1f)

// １フレームの生成量
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
	D3DXVECTOR3				posEffect;				// 地面の位置
	D3DXVECTOR3				rotEffect;				// 地面の向き(回転)
	D3DXVECTOR3				sclEffect;				// 地面の大きさ(スケール)

	D3DXVECTOR2				vec2Size;

	D3DXCOLOR				colorEffect;

	int						nUseCount;				// 消滅カウント
	int						nTex;

	float					fSizeChange;
	float					fAlphaChange;
	FLOAT					fSize;

	bool					bUse;					// 使用フラグ
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(int nType);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(int nTex, D3DXVECTOR2 vec2Size, D3DXCOLOR color, D3DXVECTOR3 vecPos, float fSizeChange, float fAlphaChange);

#endif
