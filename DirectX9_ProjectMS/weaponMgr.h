//=============================================================================
//
// ウェポンマネージャー処理 [weaponMgr.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _WEAPONMGR_H_
#define _WEAPONMGR_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "object.h"
#include "weapon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
////// モデル
//#define	WEAPON_MODEL_TEST	"data/MODEL/cube.x"	// 読み込むモデル名
//#define	WEAPON_TEXTURE_TEST	"data/TEXTURE/white_1x1.png"	// 読み込むモデル名
//
//#define	WEAPON_SCL			(1.0f)			// 読み込むモデル名
//#define	WEAPON_SCL_VEC3		(D3DXVECTOR3(WEAPON_SCL,WEAPON_SCL,WEAPON_SCL))			// 読み込むモデル名
//
//#define WEAPON_TIME_MAX		(120)
//
//#define WEAPON_MOVE_SPEED	(5)

#define	WEAPON_MODEL_BEATER	"data/MODEL/Weapon/泡立て器.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BOWL	"data/MODEL/Weapon/ボウル.x"	// 読み込むモデル名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class WeaponManager : public ObjectManager
{
public:
	enum WeaponType
	{
		BEATER,
		BOWL,
		MAX
	};
private:
	static Weapon*		pWeapon[4];
	static CXModel*		pXModel[WeaponType::MAX];			// モデル格納用
	//static Weapon* pWeapon[WeaponType::MAX * 2];
	//Weapon *pWeapon[1];
public:
	// コンストラクタ（初期化処理）
	WeaponManager(void);
	//デストラクタ（終了処理）
	~WeaponManager(void);

	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);

	//static Weapon *SetWeapon(int nPlayer, WeaponManager::WeaponType eType);
	static Weapon* SetWeapon(WeaponManager::WeaponType eType);

	//template <typename Type>
	//void SetStage(void)
	//{
	//	if (pWeapon != NULL)
	//	{
	//		delete pWeapon;
	//	}
	//	pWeapon = new Type;
	//}
	//void ReleaseStage(void)
	//{
	//	if (pWeapon != NULL)
	//	{
	//		delete pWeapon;
	//	}
	//}
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
