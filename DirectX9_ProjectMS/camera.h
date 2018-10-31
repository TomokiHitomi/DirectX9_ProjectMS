//=============================================================================
//
// �J�������� [camera.h]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM				(0.0f)										// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM				(25.0f)										// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM				(100.0f)										// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE				(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z				(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z				(5000.0f)										// �r���[���ʂ�FarZ�l

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
	D3DXVECTOR3		vEye;				// �J�����̎��_
	D3DXVECTOR3		vAt;				// �J�����̒����_
	D3DXVECTOR3		vUp;				// �J�����̏�����x�N�g��

	D3DXVECTOR3		vEyeNext;			// �J�����̎��_
	D3DXVECTOR3		vAtNext;			// �J�����̒����_
	D3DXVECTOR3		vUpNext;			// �J�����̏�����x�N�g��

	D3DXMATRIX		mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX		mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X

	float			fEyeIner;			// �J�����̎��_
	float			fAtIner;			// �J�����̒����_
	float			fUpIner;			// �J�����̏�����x�N�g��

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
// �v���g�^�C�v�錾
//*****************************************************************************

#endif