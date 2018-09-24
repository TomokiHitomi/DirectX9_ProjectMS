//=============================================================================
//
// ステージ処理 [stage.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

/*******************************************************************************
* インクルード
*******************************************************************************/
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// モデル
#define	STAGE_MODEL		"data/MODEL/Stage/Chinese/Chinese PVP Stage.x"	// 読み込むモデル名
#define	STAGE_TEXTURE		"data/MODEL/Stage/Chinese/s.tga"	// 読み込むモデル名

// モデルの最大数
#define MODEL_STAGE_MAX			(1)

// モデルスケール
#define MODEL_STAGE_SCL			(30.0f)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Stage
{
public:
	Object *pObj;
	//Stage();
	~Stage()
	{
		if (pObj != NULL)
		{
			delete pObj;
		}
	}
};


class StageManager : public ObjectManager
{
private:
	Stage *m_pStage = NULL;
public:
	// コンストラクタ（初期化処理）
	StageManager(void);
	//デストラクタ（終了処理）
	~StageManager(void);

	// 更新処理
	void	Update(void);
	// 描画処理
	void	Draw(void);

	template <typename Type>
	void SetStage(void)
	{
		if (m_pStage != NULL)
		{
			delete m_pStage;
		}
		m_pStage = new Type;
	}
	void ReleaseStage(void)
	{
		if (m_pStage != NULL)
		{
			delete m_pStage;
		}
	}
};

class StageChinese : public Stage
{
	enum
	{
		MAIN,
		MAX
	};
public:
	StageChinese()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		pObj = new Object(MAX);
		// 各プロパティの初期化
		pObj->prop[MAIN].vScl = D3DXVECTOR3(MODEL_STAGE_SCL, MODEL_STAGE_SCL, MODEL_STAGE_SCL);
		pObj->prop[MAIN].CXModel->Init(pDevice, STAGE_MODEL, STAGE_TEXTURE);
	}
	//~StageChinese()
	//{

	//}
	// 更新処理
	void	Update(void) { ; }
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
