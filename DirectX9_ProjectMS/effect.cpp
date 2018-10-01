//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : GP12A295 25 人見友基
//
//=============================================================================
#include "effect.h"

/* 全体で必要なインクルード */
#include "input.h"
#include "camera.h"
#include "calculate.h"


#include <Effekseer\Effekseer.h>
#include <Effekseer\EffekseerRendererDX9.h>
#include <Effekseer\EffekseerSoundXAudio2.h>

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
::Effekseer::Matrix44 ConvertMtx44(D3DXMATRIX mtx);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ::Effekseer::Manager*				g_manager = NULL;
static ::EffekseerRendererDX9::Renderer*	g_renderer = NULL;
static ::EffekseerSound::Sound*				g_sound = NULL;
static ::Effekseer::Effect*					g_effect = NULL;
static ::Effekseer::Handle					g_handle = -1;
static ::Effekseer::Vector3D				g_position;
static ::Effekseer::Vector3D				g_rotation;
static ::Effekseer::Matrix44 mtx44View, mtx44Pro, mtx44World;

// サウンド
//static IXAudio2*						g_xa2 = NULL;
//static IXAudio2MasteringVoice*			g_xa2_master = NULL;

//=============================================================================
// コンストラクタ処理（初期化）
//=============================================================================
Effect::Effect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// XAudio2の初期化を行う
	//XAudio2Create(&g_xa2);

	//g_xa2->CreateMasteringVoice(&g_xa2_master);


	// 描画用インスタンスの生成
	g_renderer = ::EffekseerRendererDX9::Renderer::Create(pDevice, 2000);

	// エフェクト管理用インスタンスの生成
	g_manager = ::Effekseer::Manager::Create(2000);

	// 描画用インスタンスから描画機能を設定
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	// 左手座標系に設定
	g_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);


	//// 音再生用インスタンスの生成
	//g_sound = ::EffekseerSound::Sound::Create(g_xa2, 16, 16);

	//// 音再生用インスタンスから再生機能を指定
	//g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());

	//// 音再生用インスタンスからサウンドデータの読込機能を設定
	//// 独自拡張可能、現在はファイルから読み込んでいる。
	//g_manager->SetSoundLoader(g_sound->CreateSoundLoader());


	// 視点位置を確定	
	g_position = ::Effekseer::Vector3D(0.0f, 5.0f, 0.0f);
	g_rotation = ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f);


	// エフェクトの読込
	g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"TrinityField.efk");
	//g_effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"test.efk");

	// エフェクトの再生
	g_handle = g_manager->Play(g_effect, 0, 0, 0);

	g_manager->SetLocation(g_handle, g_position);
	g_manager->SetScale(g_handle, 5.0f, 5.0f, 5.0f);
}

//=============================================================================
// デストラクタ処理（終了）
//=============================================================================
Effect::~Effect(void)
{
	// エフェクトの停止
	g_manager->StopEffect(g_handle);

	// エフェクトの破棄
	ES_SAFE_RELEASE(g_effect);

	// 先にエフェクト管理用インスタンスを破棄
	g_manager->Destroy();

	//// 次に音再生用インスタンスを破棄
	//g_sound->Destroy();

	// 次に描画用インスタンスを破棄
	g_renderer->Destroy();

	//// XAudio2の解放
	//if (g_xa2_master != NULL)
	//{
	//	g_xa2_master->DestroyVoice();
	//	g_xa2_master = NULL;
	//}
	//ES_SAFE_RELEASE(g_xa2);
}

//=============================================================================
// 更新処理
//=============================================================================
void Effect::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// エフェクトの移動処理を行う
	//g_manager->AddLocation(g_handle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// エフェクトの更新処理を行う
	g_manager->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void Effect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxView, mtxPro, mtxWorld;

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxPro);

	// カメラ行列を設定
	g_renderer->SetCameraMatrix(ConvertMtx44(mtxView));

	// 投影行列を設定
	g_renderer->SetProjectionMatrix(ConvertMtx44(mtxPro));


	// 両面描画する
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


		// エフェクトの描画開始処理を行う。
		g_renderer->BeginRendering();

		//g_position = ::Effekseer::Vector3D(100.0f, 20.0f, 0.0f);
		//g_manager->SetLocation(g_handle, g_position);

		// エフェクトの描画を行う。
		g_manager->Draw();

		// エフェクトの描画終了処理を行う。
		g_renderer->EndRendering();
	

	// 裏面をカリングに戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

::Effekseer::Matrix44 ConvertMtx44(D3DXMATRIX mtx)
{
	::Effekseer::Matrix44 mtx44;
	mtx44.Values[0][0] = mtx._11;
	mtx44.Values[0][1] = mtx._12;
	mtx44.Values[0][2] = mtx._13;
	mtx44.Values[0][3] = mtx._14;
	mtx44.Values[1][0] = mtx._21;
	mtx44.Values[1][1] = mtx._22;
	mtx44.Values[1][2] = mtx._23;
	mtx44.Values[1][3] = mtx._24;
	mtx44.Values[2][0] = mtx._31;
	mtx44.Values[2][1] = mtx._32;
	mtx44.Values[2][2] = mtx._33;
	mtx44.Values[2][3] = mtx._34;
	mtx44.Values[3][0] = mtx._41;
	mtx44.Values[3][1] = mtx._42;
	mtx44.Values[3][2] = mtx._43;
	mtx44.Values[3][3] = mtx._44;
	return mtx44;
}