//=============================================================================
//
// プレイヤー処理 [skydome.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _SKYDOME_H_
#define _SKYDOME_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "object.h"
#include "XModel.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// モデル
#define	SKYDOME_MODEL		"data/MODEL/Skydome/skydome.x"	// 読み込むモデル名
#define	SKYDOME_TEXTURE		"data/MODEL/Skydome/incskies_014_8k.png"	// 読み込むモデル名

// モデルの最大数
#define MODEL_SKYDOME_MAX			(1)

// モデルスケール
#define MODEL_SKYDOME_SCL			(30.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************

class Skydome : public ObjectManager
{
private:
	CXModel			*m_CXModel;			// モデル格納用
	D3DXVECTOR3		m_vPos;				// 座標情報
	D3DXVECTOR3		m_vRot;				// 回転情報
	D3DXVECTOR3		m_vScl;				// 拡縮情報
	D3DXMATRIX		m_mtxWorld;			// ワールドマトリクス
	bool			m_bUse;				// 使用フラグ
public:
	enum SKYDOME
	{	// プレイヤー管理
		SKYDOME_MAIN,
		SKYDOME_MAX
	};

	// コンストラクタ（初期化処理）
	Skydome(void);
	//デストラクタ（終了処理）
	~Skydome(void);

	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);
private:

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
