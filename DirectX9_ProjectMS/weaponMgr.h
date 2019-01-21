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

// パティシエ
#define	WEAPON_MODEL_BEATER				"data/MODEL/Weapon/泡立て器.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BEATER_SCL			(28.0f)

#define	WEAPON_MODEL_BOWL				"data/MODEL/Weapon/ボウル.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BOWL_SCL			(25.0f)

#define	WEAPON_MODEL_CAKE				"cake.x"	// 読み込むモデル名
#define	WEAPON_MODEL_CAKE_SCL			(15.0f)

// アイドル
#define	WEAPON_MODEL_MIC				"mic.x"	// 読み込むモデル名
#define	WEAPON_MODEL_MIC_SCL			(2.7f)

#define	WEAPON_MODEL_CDCASE				"CDCase.x"	// 読み込むモデル名
#define	WEAPON_MODEL_CDCASE_SCL			(21.0f)

#define	WEAPON_MODEL_KARAAGE			"Karaage_Lemon.x"	// 読み込むモデル名
#define	WEAPON_MODEL_KARAAGE_SCL		(12.0f)

// ショウボウシ
#define	WEAPON_MODEL_EXTINGUISHER		"extinguisher.x"	// 読み込むモデル名
#define	WEAPON_MODEL_EXTINGUISHER_SCL	(2.0f)

#define	WEAPON_MODEL_HELMET				"helmet.X"	// 読み込むモデル名
#define	WEAPON_MODEL_HELMET_SCL			(14.0f)

#define	WEAPON_MODEL_FIREENGIN			"Fireengin.x"	// 読み込むモデル名
#define	WEAPON_MODEL_FIREENGIN_SCL		(7.0f)

// ドクター
#define	WEAPON_MODEL_MESU				"mesu.x"	// 読み込むモデル名
#define	WEAPON_MODEL_MESU_SCL			(30.0f)

#define	WEAPON_MODEL_SYRINGE			"Syringe.x"	// 読み込むモデル名
#define	WEAPON_MODEL_SYRINGE_SCL		(38.0f)

#define	WEAPON_MODEL_BED				"bed.x"	// 読み込むモデル名
#define	WEAPON_MODEL_BED_SCL			(10.0f)


#define WEAPON_MAX						(6)

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
		// パティシエ
		BEATER,
		BOWL,
		CAKE,

		// アイドル
		MIC,
		CDCASE,
		KARAAGE,

		// ショウボウシ
		EXTINGUISHER,
		HELMET,
		FIREENGIN,

		// ドクター
		MESU,
		SYRINGE,
		BED,

		MAX
	};

private:
	static Weapon*		pWeapon[6];
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
