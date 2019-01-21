//=============================================================================
//
// ウェポンマネージャー処理 [weaponMgr.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "main.h"
#include "weapon.h"
#include "weaponMgr.h"
#include "calculate.h"


// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Weapon*		WeaponManager::pWeapon[WEAPON_MAX];
CXModel*	WeaponManager::pXModel[WeaponType::MAX];

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
WeaponManager::WeaponManager(void)
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::WEAPON, Priority::Middle, Priority::Middle);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		pWeapon[i] = NULL;
	}

	for (unsigned int i = 0; i < WeaponType::MAX; i++)
	{
		pXModel[i] = NULL;
		// モデルデータをインスタンス化
		pXModel[i] = new CXModel;
		pXModel[i]->SetLight(true);
	}

	// モデルデータを初期化

	// パティシエ
	pXModel[BEATER]->Init(pDevice, WEAPON_MODEL_BEATER, NULL);
	pXModel[BOWL]->Init(pDevice, WEAPON_MODEL_BOWL, NULL);
	pXModel[CAKE]->Init(pDevice, WEAPON_MODEL_CAKE, NULL);
	// アイドル
	pXModel[MIC]->Init(pDevice, WEAPON_MODEL_MIC, NULL);
	pXModel[CDCASE]->Init(pDevice, WEAPON_MODEL_CDCASE, NULL);
	pXModel[KARAAGE]->Init(pDevice, WEAPON_MODEL_KARAAGE, NULL);
	// ショウボウシ
	pXModel[EXTINGUISHER]->Init(pDevice, WEAPON_MODEL_EXTINGUISHER, NULL);
	pXModel[HELMET]->Init(pDevice, WEAPON_MODEL_HELMET, NULL);
	pXModel[FIREENGIN]->Init(pDevice, WEAPON_MODEL_FIREENGIN, NULL);
	// ドクター
	pXModel[MESU]->Init(pDevice, WEAPON_MODEL_MESU, NULL);
	pXModel[SYRINGE]->Init(pDevice, WEAPON_MODEL_SYRINGE, NULL);
	pXModel[BED]->Init(pDevice, WEAPON_MODEL_BED, NULL);
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
WeaponManager::~WeaponManager(void)
{
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		SAFE_DELETE(pWeapon[i]);
	}

	for (unsigned int i = 0; i < WeaponType::MAX; i++)
	{
		SAFE_DELETE(pXModel[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void WeaponManager::Update(void)
{
#ifdef _DEBUG
	PrintDebugProc("【 Weapon 】\n");
#endif
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		//SAFE_UPDATE(pWeapon[i]);
		if (pWeapon[i] != NULL)
		{
			pWeapon[i]->Update();
		}
	}
#ifdef _DEBUG
	PrintDebugProc("\n");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void WeaponManager::Draw(void)
{
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		//SAFE_DRAW(pWeapon[i]);
		if (pWeapon[i] != NULL)
		{
			pWeapon[i]->Draw();
		}
	}
}

//=============================================================================
// 設定処理
//=============================================================================
//Weapon *WeaponManager::SetWeapon(int nPlayer, WeaponManager::WeaponType eType)
//{
//	pWeapon[nPlayer * 2 + (int)eType] = new Weapon;
//	return pWeapon[nPlayer * 2 + (int)eType];
//}

Weapon *WeaponManager::SetWeapon(WeaponManager::WeaponType eType)
{
	for (unsigned int i = 0; i < WEAPON_MAX; i++)
	{
		if (pWeapon[i] == NULL)
		{
			pWeapon[i] = new Weapon(pXModel[eType]);
			return pWeapon[i];
		}
	}
}