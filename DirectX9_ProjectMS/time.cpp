//=============================================================================
//
// スコア処理 [time.cpp]
//
//=============================================================================
#include "main.h"
#include "time.h"
#include "fade.h"
#include "sound.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//HRESULT MakeVertexTime(void);
//void SetTextureTime(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pD3DTextureTime = NULL;		// テクスチャへのポリゴン
//VERTEX_2D				TimeObj[0].vertexWk[TEXTURE_TIME_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

Time::Time()
{
	// オブジェクトIDとプライオリティの設定処理
	SetIdAndPriority(ObjectID::TIME, Priority::Middle, Priority::Lowest);

	Init();
}

//=============================================================================
// デストラクタ
//=============================================================================
Time::~Time()
{
	Uninit();
}

HRESULT Time::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_TIME_000,				// ファイルの名前
		&TimeObj[0].pD3DTexture);				// 読み込むメモリのポインタ
	

	TimeObj[0].Pos = D3DXVECTOR3((float)TEXTURE_TIME_POSITION000_X, (float)TEXTURE_TIME_POSITION000_Y, 0.0f);
	TimeObj[0].Timer = TEXTURE_TIME_SECOND * FRAME;

	// 頂点情報の作成
	MakeVertexTime();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Time::Uninit(void)
{
	if (TimeObj[0].pD3DTexture != NULL)
	{	// テクスチャの開放
		TimeObj[0].pD3DTexture->Release();
		TimeObj[0].pD3DTexture = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Time::Update(void)
{
	// 毎フレーム実行される処理を記述する
	TimeObj[0].Timer--;

	SetTextureTime();

}

//=============================================================================
// 描画処理
//=============================================================================
void Time::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;


	//// レンダーステートパラメータの設定
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	//// サンプラーステートパラメータの設定
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	//pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	//// テクスチャステージステートの設定
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数


	// テクスチャの設定
	pDevice->SetTexture(0, TimeObj[0].pD3DTexture);

	// スコア
	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, TimeObj[0].vertexWk[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Time::MakeVertexTime(void)
{
	int i;
	float habaX = TEXTURE_TIME_SIZE000_X;	// 数字の横幅

											// 桁数分処理する
	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// 頂点座標の設定
		TimeObj[0].vertexWk[i][0].vtx.x = -habaX * i + TimeObj[0].Pos.x;
		TimeObj[0].vertexWk[i][0].vtx.y = TimeObj[0].Pos.y;
		TimeObj[0].vertexWk[i][0].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][1].vtx.x = -habaX * i + TimeObj[0].Pos.x + TEXTURE_TIME_SIZE000_X;
		TimeObj[0].vertexWk[i][1].vtx.y = TimeObj[0].Pos.y;
		TimeObj[0].vertexWk[i][1].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][2].vtx.x = -habaX * i + TimeObj[0].Pos.x;
		TimeObj[0].vertexWk[i][2].vtx.y = TimeObj[0].Pos.y + TEXTURE_TIME_SIZE000_Y;
		TimeObj[0].vertexWk[i][2].vtx.z = 0.0f;
		TimeObj[0].vertexWk[i][3].vtx.x = -habaX * i + TimeObj[0].Pos.x + TEXTURE_TIME_SIZE000_X;
		TimeObj[0].vertexWk[i][3].vtx.y = TimeObj[0].Pos.y + TEXTURE_TIME_SIZE000_Y;
		TimeObj[0].vertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		TimeObj[0].vertexWk[i][0].rhw = 1.0f;
		TimeObj[0].vertexWk[i][1].rhw = 1.0f;
		TimeObj[0].vertexWk[i][2].rhw = 1.0f;
		TimeObj[0].vertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		TimeObj[0].vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		TimeObj[0].vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		TimeObj[0].vertexWk[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		TimeObj[0].vertexWk[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		TimeObj[0].vertexWk[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		TimeObj[0].vertexWk[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void Time::SetTextureTime(void)
{
	int i;
	int number = TimeObj[0].Timer / FRAME;

	for (i = 0; i < TEXTURE_TIME_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		TimeObj[0].vertexWk[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		TimeObj[0].vertexWk[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		TimeObj[0].vertexWk[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		TimeObj[0].vertexWk[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
//void AddTime(int add)
//{
//	TimeObj[0].Time += add;
//	if (g_nTime > TIME_MAX)
//	{
//		g_nTime = TIME_MAX;
//	}
//	else if (g_nTime < 0)
//	{
//
//		g_nTime = 0;
//	}
//
//}
