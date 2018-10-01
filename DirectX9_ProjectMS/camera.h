//=============================================================================
//
// カメラ処理 [camera.h]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM				(0.0f)										// カメラの初期位置(X座標)
#define	POS_Y_CAM				(25.0f)										// カメラの初期位置(Y座標)
#define	POS_Z_CAM				(100.0f)										// カメラの初期位置(Z座標)

#define	VIEW_ANGLE				(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z				(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(5000.0f)										// ビュー平面のFarZ値

class Camera
{
private:
	static D3DXVECTOR3	s_vEye[3];				// カメラの視点
	static D3DXVECTOR3	s_vAt[3];				// カメラの注視点
	static D3DXVECTOR3	s_vUp[3];				// カメラの上方向ベクトル

	static D3DXVECTOR3	s_vEyeNext[3];			// カメラの視点
	static D3DXVECTOR3	s_vAtNext[3];			// カメラの注視点
	static D3DXVECTOR3	s_vUpNext[3];			// カメラの上方向ベクトル

	static D3DXMATRIX	s_mtxView;			// ビューマトリックス
	static D3DXMATRIX	s_mtxProjection;	// プロジェクションマトリックス
	static D3DXMATRIX	s_mtxWorld;			// ワールドマトリックス

	static float		s_fEyeIner;			// カメラの視点
	static float		s_fAtIner;			// カメラの注視点
	static float		s_fUpIner;			// カメラの上方向ベクトル
	static D3DVIEWPORT9	dvPort[3];
	static float		fAspect[3];
public:
	static void Init(void);
	static void Uninit(void);
	static void Update(void);

	static void SetAt(D3DXVECTOR3 vAt, int nNum);
	static void SetEye(D3DXVECTOR3 vEye, int nNum);
	static void SetUp(D3DXVECTOR3 vUp, int nNum);

	static void SetAtIner(float fIner);
	static void SetEyeIner(float fIner);
	static void SetUpIner(float fIner);

	static void AddAtIner(float fIner);
	static void AddEyeIner(float fIner);
	static void AddUpIner(float fIner);

	static float GetAtIner(void) { return s_fAtIner; }
	static float GetEyeIner(void) { return s_fEyeIner; }
	static float GetUpIner(void) { return s_fUpIner; }

	//static void SetEye(D3DXVECTOR3 vEye);
	//static void SetUp(D3DXVECTOR3 vUp);
	static void Set(int nMulti);
	//D3DXMATRIX GetInvRotateMat(D3DXVECTOR3 pos);
	static D3DXMATRIX GetMtxView(void);
	static D3DXMATRIX GetMtxProjection(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#endif