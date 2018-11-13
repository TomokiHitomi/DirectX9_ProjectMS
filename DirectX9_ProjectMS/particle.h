//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	TEXTURE_EFFECT	"data/TEXTURE/effect000.jpg"						// 読み込むテクスチャファイル名
#define	PARTICLE_TEXTURE				"data/TEXTURE/effect.png"						// 読み込むテクスチャファイル名
//#define PARTICLE_SHADER_FILE			"data/SHADER/sprite.fx"
//#define PARTICLE_SHADER_FILE			"data/SHADER/plane.fx"

// テクスチャ内分割数
#define PARTICLE_TEXTURE_PATTERN_DIVIDE_X	(1)
#define PARTICLE_TEXTURE_PATTERN_DIVIDE_Y	(1)
// テクスチャ分割パターン
#define  PARTICLE_TEXTURE_PATTERN_NU		(PARTICLE_TEXTURE_PATTERN_DIVIDE_X*PARTICLE_TEXTURE_PATTERN_DIVIDE_Y)

// サイズ
#define	PARTICLE_SIZE_X		(1.0f)
#define	PARTICLE_SIZE_Y		(1.0f)

// 最大数
#define PARTICLE_MAX		(300000)

// 移動スピード
#define PARTICLE_MOVE_SPEED		(0.1f)

// １フレームの生成量
#define PARTICLE_SET			(500)


//*****************************************************************************
// クラス定義
//*****************************************************************************
class Particle
{
private:
	LPDIRECT3DTEXTURE9				pTexture;	// テクスチャ
	LPDIRECT3DVERTEXBUFFER9			pVtxBuff;	// 頂点バッファ
	LPDIRECT3DVERTEXBUFFER9			pInstBuff;	// インスタンスバッファ
	LPDIRECT3DINDEXBUFFER9			pIdxBuff;	// インデックスバッファ
	LPDIRECT3DVERTEXDECLARATION9	pDecl;		// 頂点宣言

	// シェーダー関連
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
	// コンストラクタ
	Particle(void);
	//デストラクタ
	~Particle(void);
	// 初期化処理
	HRESULT	Init(void);
	// 解放処理
	void	Release(void);
	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);
	// 設置処理
	void	Set(int value, D3DXVECTOR3 pos, D3DXCOLOR color);
};

class ParticleManager : public ObjectManager
{
private:
	Particle* pParticle;
public:
	// コンストラクタ
	ParticleManager(void);
	//デストラクタ
	~ParticleManager(void);
	// 初期化処理
	HRESULT	Init(void);
	// 解放処理
	void	Release(void);
	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
