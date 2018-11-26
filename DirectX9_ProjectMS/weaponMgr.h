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
#define	WEAPON_MODEL_BEATER				"data/MODEL/Weapon/泡立て器.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BEATER_SCL			(25.0f)

#define	WEAPON_MODEL_BOWL				"data/MODEL/Weapon/ボウル.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BOWL_SCL			(20.0f)

#define	WEAPON_MODEL_MIC				"mic.x"	// 読み込むモデル名
#define	WEAPON_MODEL_MIC_SCL			(2.0f)

#define	WEAPON_MODEL_CDCASE				"CDCase.x"	// 読み込むモデル名
#define	WEAPON_MODEL_CDCASE_SCL			(18.0f)

#define	WEAPON_MODEL_EXTINGUISHER		"extinguisher.x"	// 読み込むモデル名
#define	WEAPON_MODEL_EXTINGUISHER_SCL	(2.0f)

#define	WEAPON_MODEL_HELMET				"helmet.X"	// 読み込むモデル名
#define	WEAPON_MODEL_HELMET_SCL			(14.0f)


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
		MIC,
		CDCASE,
		EXTINGUISHER,
		HELMET,
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
