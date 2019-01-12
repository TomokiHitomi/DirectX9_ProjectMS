//=============================================================================
//
// キャラクター処理 [character.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "SkinMeshX.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHARACTER_FIREMAN			("data/MODEL/Fireman/Fireman.X")
#define CHARACTER_FIREMAN_SCL		(12.0f)

#define CHARACTER_PASTRY			("data/MODEL/Pastry/Pastry.X")
#define CHARACTER_PASTRY_SCL		(10.25f)

#define CHARACTER_IDOL				("data/MODEL/Idol/Idol.X")
#define CHARACTER_IDOL_SCL			(10.25f)

#define CHARACTER_DOCTOR			("Idol.X")
#define CHARACTER_DOCTOR_SCL		(0.25f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CharacterManager
{
public:
	enum TYPE
	{	// プレイヤー管理
		FIREMAN,
		PASTRY,
		IDOL,
		DOCTOR,
		TYPE_MAX
	};
	CSkinMesh	*m_CSkinMesh[TYPE_MAX];	// スキンメッシュ格納用

public:
	// コンストラクタ（初期化処理）
	CharacterManager(void);
	//デストラクタ（終了処理）
	~CharacterManager(void);
	CSkinMesh *GetCharData(CharacterManager::TYPE);
	static bool m_bUse;

private:
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
