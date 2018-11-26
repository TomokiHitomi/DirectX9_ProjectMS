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
#define	WEAPON_SCL					(10.0f)
#define	WEAPON_SCL_VEC3				(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// 読み込むモデル名

// 残存時間
#define WEAPON_TIME_MAX				(300)

// 移動スピード
#define WEAPON_MOVE_SPEED			(2.5f)

// 回転スピード
#define WEAPON_ROT_SPEED			(0.2f)

// リモート
#define WEAPON_REMOTE_TIME			(5)		// リモート開始時間
#define WEAPON_REMOTE_CORRECTION	(0.005f)		// 加速度補正
#define WEAPON_REMOTE_ADD_MAX		(0.03f)		// １フレームの最大加算値
#define WEAPON_REMOTE_MAX			(0.35f)		// 最大加算値


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
	float			fRemote;
	float			fSize;
	float			fDamage;
	bool			bRot;
	bool			bUse;				// 使用フラグ

public:
	Weapon(CXModel* XModel);
	virtual ~Weapon();
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetStatus(float size, float damage,float scl,bool rot);


	virtual void SetSize(float size) { fSize = size; }
	virtual float GetSize(void) { return fSize; }

	virtual void SetDamage(float damage) { fDamage = damage; }
	virtual float GetDamage(void) { return fDamage; }

	virtual void SetScl(float fScl);
	virtual void SetRot(bool bUse);
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
