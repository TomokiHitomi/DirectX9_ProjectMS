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

#define CAMERA_MULTI_MARGIN		(2)
#define CAMERA_MULTI_WIDTH		(SCREEN_WIDTH / 2 - CAMERA_MULTI_MARGIN)
#define CAMERA_MULTI_HEIGHT		(SCREEN_HEIGHT)
#define CAMERA_MULTI_2_X		(SCREEN_WIDTH / 2 + CAMERA_MULTI_MARGIN)

#define CAMERA_EXTENSION_SPEED	(40)

class Camera;

class CameraManager
{
public:
	enum CameraType
	{
		MULTI1,
		MULTI2,
		MULTI_MAX,
		SINGLE = 2,
		TYPE_MAX
	};
	enum CameraPort
	{
		CENTER,
		EXTENSION_L,
		EXTENSION_R,
		PORT_MAX
	};

	static Camera *pCamera[TYPE_MAX];
	static CameraPort eCameraPort;
	static CameraType eCameraType;


	CameraManager();
	~CameraManager();
	static void Init(void);
	static void Update(void);
	static void Set(CameraType);
	static CameraType GetType(void) { return eCameraType; }
	static void SetExtension(CameraPort eCP);
	static void Extension(void);
};

class Camera
{
private:
	D3DXVECTOR3		vEye;				// カメラの視点
	D3DXVECTOR3		vAt;				// カメラの注視点
	D3DXVECTOR3		vUp;				// カメラの上方向ベクトル

	D3DXVECTOR3		vEyeNext;			// カメラの視点
	D3DXVECTOR3		vAtNext;			// カメラの注視点
	D3DXVECTOR3		vUpNext;			// カメラの上方向ベクトル

	D3DXMATRIX		mtxView;			// ビューマトリックス
	D3DXMATRIX		mtxProjection;		// プロジェクションマトリックス

	float			fEyeIner;			// カメラの視点
	float			fAtIner;			// カメラの注視点
	float			fUpIner;			// カメラの上方向ベクトル

public:
	D3DVIEWPORT9	dvPort;
	float			fAspect;
	bool			bExtension;

	Camera(CameraManager::CameraType eCameraType);
	~Camera();
	void Init(CameraManager::CameraType eCameraType);
	void Uninit(void);
	void Update(void);

	void SetAt(D3DXVECTOR3 vAt);
	void SetEye(D3DXVECTOR3 vEye);
	void SetUp(D3DXVECTOR3 vUp);

	void SetAtIner(float fIner);
	void SetEyeIner(float fIner);
	void SetUpIner(float fIner);

	void AddAtIner(float fIner);
	void AddEyeIner(float fIner);
	void AddUpIner(float fIner);

	float GetAtIner(void) { return fAtIner; }
	float GetEyeIner(void) { return fEyeIner; }
	float GetUpIner(void) { return fUpIner; }

	//static void SetEye(D3DXVECTOR3 vEye);
	//static void SetUp(D3DXVECTOR3 vUp);
	void Set();
	//D3DXMATRIX GetInvRotateMat(D3DXVECTOR3 pos);
	D3DXMATRIX GetMtxView(void);
	D3DXMATRIX GetMtxProjection(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif