//=============================================================================
//
// スキンメッシュシェーダ [skinmesh.fx]
// Author : GP12A295 25 人見友基
//
//=============================================================================
float4x4	world;		// ワールドマトリクス
float4x4	view;		// ビューマトリクス
float4x4	proj;		// プロジェクションマトリクス
float3		ld;			// ライトベクトル

// ライト
float4		dif_lt;		// ディフューズ
float4		amb_lt;		// 環境光
float4		spc_lt;		// スペキュラー光
float3		dir_lt;		// 平行光源の方向

// マテリアル
float4		dif_mat;	// ディフューズ光
float4		emi_mat;	// エミッシブ光
float4		amb_mat;	// 環境光
float4		spc_mat;	// スペキュラー
float		pwr_mat;	// スペキュラー光のパワー値

texture tex;			// 使用するテクスチャ
sampler smp = sampler_state {
	texture = <tex>;
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct VS_IN		// 頂点シェーダの引数
{
	float3	pos : POSITION;
	float3	nor : NORMAL;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;

};

struct VS_OUT		// 頂点シェーダの戻り値かつピクセルシェーダーの引数
{
	float4	pos : POSITION;
	float4	col : COLOR0;
	float2	uv : TEXCOORD0;
};

//=============================================================================
// 頂点シェーダ
//=============================================================================
VS_OUT vs_light_on( VS_IN In )
{
	VS_OUT Out = (VS_OUT)0;
	//VS_OUT Out;

	Out.pos = float4(
		In.pos.x,
		In.pos.y,
		In.pos.z,
		1.0f
	);

	Out.pos = mul(Out.pos, world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, proj);

	// 法線をワールド空間へ
	float3 nor = mul(In.nor, world);

   // 反射する光の強さを算出
	//float Power = saturate(dot(normalize(nor), -normalize(dir_lt)));
	//Power = clamp(Power, 0.0f, 1.0f);

	// ランパード反射
	Out.col = dif_mat * dif_lt;
	Out.col = Out.col + amb_mat * amb_lt;
	Out.col = Out.col + emi_mat;


	// スペキュラ反射（調整中）
	//float4 spc_temp = float4(0.0f, 0.0f, 1.0f, 1.0f);
	float3 eyePos = float3(view._41, view._42, view._43);
	float3	V = normalize(eyePos - Out.pos);		// （カメラ座標ー頂点座標）ベクトル
	//float3	H = -normalize(V + dir_lt);		//  ハーフベクトル（視線ベクトルと光の方向ベクトル）
	float3	R = normalize(2 * dot(dir_lt, nor) * nor - dir_lt);
	float specularLight = pow(saturate(dot(R, V)), 1.5f);
	//Out.col = Out.col + (spc_temp * specularLight);
	Out.col = Out.col + (spc_mat * specularLight);


	// 反射する光の強さを算出
	Out.col = Out.col * saturate(dot(normalize(nor), -normalize(dir_lt)));

	// α値は入力値をそのまま使用
	Out.col.a = dif_mat.a;

	// uvはそのまま使用
	Out.uv  = In.uv;

	return Out;
}

VS_OUT vs_light_off(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	Out.pos = float4(
		In.pos.x,
		In.pos.y,
		In.pos.z,
		1.0f
		);

	Out.pos = mul(Out.pos, world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, proj);

	Out.uv = In.uv;
	Out.col = In.col;
	return Out;
}

//=============================================================================
// ピクセルシェーダ
//=============================================================================
float4 ps_light_on(VS_OUT In) : COLOR0
{
	return tex2D(smp, In.uv) * In.col;
}

float4 ps_light_off(VS_OUT In) : COLOR0
{
	return tex2D(smp, In.uv);
}

//=============================================================================
// テクニック
//=============================================================================
technique LIGHT_ON
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_on();
		PixelShader = compile ps_3_0 ps_light_on();
	}
}

technique LIGHT_OFF
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_light_off();
		PixelShader = compile ps_3_0 ps_light_off();
	}
}