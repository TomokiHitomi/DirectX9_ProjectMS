//=============================================================================
//
// ウェポン処理 [weapon.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _WEAPON_H_
#define _WEAPON_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "XModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//// モデル
#define	WEAPON_MODEL_TEST	"data/MODEL/Weapon/泡立て器.x"	// 読み込むモデル名
//#define	WEAPON_MODEL_TEST	"data/MODEL/cube.x"	// 読み込むモデル名

//#define	WEAPON_TEXTURE_TEST	"data/TEXTURE/white_1x1.png"	// 読み込むモデル名

#define	WEAPON_SCL			(18.0f)			// 読み込むモデル名
#define	WEAPON_SCL_VEC3		(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// 読み込むモデル名

#define WEAPON_TIME_MAX		(120)

#define WEAPON_MOVE_SPEED	(3.0f)
#define WEAPON_HEIGHT		(7.0f)


//// モデルの最大数
//#define MODEL_STAGE_MAX			(1)
//
//// モデルスケール
//#define MODEL_STAGE_SCL			(30.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Weapon
{
private:
	CXModel*		pXModel;			// モデル格納用
	D3DXVECTOR3		vPos;				// 座標情報
	D3DXVECTOR3		vRot;				// 回転情報
	D3DXVECTOR3		vScl;				// 拡縮情報
	D3DXVECTOR3		vMove;				// 移動情報
	D3DXVECTOR3		vShot;
	D3DXVECTOR3		vRemote;
	D3DXMATRIX		mtxWorld;			// ワールドマトリクス
	int				nTime;				// 生存カウント
	bool			bUse;				// 使用フラグ

public:
	Weapon(CXModel* XModel);
	virtual ~Weapon();
	virtual void Update(void);
	virtual void Draw(void);
	virtual bool Set(D3DXVECTOR3 pos, D3DXVECTOR3 shot);
	virtual void SetUse(bool use) { bUse = use; }
	virtual bool GetUse(void) { return bUse; }
	virtual void Remote(float remote);
	virtual D3DXVECTOR3 GetPos(void) { return vPos; }
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
