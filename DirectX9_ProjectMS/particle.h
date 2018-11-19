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
#include "plane.h"

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
#define	PARTICLE_SIZE_X		(0.1f)
#define	PARTICLE_SIZE_Y		(0.1f)

// 最大数
#define PARTICLE_MAX		(300000)

// 移動スピード
#define PARTICLE_MOVE_SPEED		(0.01f)
#define PARTICLE_MOVE_MAX		(10.0f)

// １フレームの生成量
#define PARTICLE_SET			(500)

#define PARTICLE_COLOR_SPEED	(PLANE_COLOR_SPEED)
#define PARTICLE_COLOR_MAX	(PLANE_COLOR_MAX)

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
	float							fSin;

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
		float		angle;
	}INSTANCE_PLANE;

	float							fColor;
	bool							bColor;

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
	void	Set(int value, D3DXVECTOR3 pos);
};

class ParticleManager : public ObjectManager
{
private:
	static Particle* pParticle;
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

	static void Set(int value, D3DXVECTOR3 pos)
	{
		pParticle->Set(value, pos);
	}
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
