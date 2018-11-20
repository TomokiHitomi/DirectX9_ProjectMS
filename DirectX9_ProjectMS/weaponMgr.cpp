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
int			WeaponManager::nCount;
Weapon*		WeaponManager::pWeapon[(int)MAX * (int)PlayerManager::PLAYER_MAX];

//=============================================================================
// コンストラクタ（初期化処理）
//=============================================================================
WeaponManager::WeaponManager(void)
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::WEAPON, Priority::Middle, Priority::Middle);

	// オブジェクトタイプの設定
	SetObjectType(ObjectManager::ObjectType::NORMAL);

	nCount = (int)MAX * (int)PlayerManager::PLAYER_MAX;

	for (unsigned int i = 0; i < nCount; i++)
	{
		pWeapon[i] = NULL;
	}
}

//=============================================================================
// デストラクタ（終了処理）
//=============================================================================
WeaponManager::~WeaponManager(void)
{
	for (unsigned int i = 0; i < nCount; i++)
	{
		SAFE_DELETE(pWeapon[i]);
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
	for (unsigned int i = 0; i < nCount; i++)
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
	for (unsigned int i = 0; i < nCount; i++)
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
Weapon *WeaponManager::SetWeapon(int nPlayer, WeaponManager::WeaponType eType)
{
	pWeapon[nPlayer * 2 + (int)eType] = new Weapon;
	return pWeapon[nPlayer * 2 + (int)eType];
}