//=============================================================================
//
// Xファイルシェーダ [xmodel.fx]
// Author : GP12A295 25 人見友基
//
//=============================================================================
float4x4	world;		// ワールドマトリクス
float4x4	view;		// ビューマトリクス
float4x4	proj;		// プロジェクションマトリクス
float4		eye;		// 視点座標

// ライト
typedef struct _LIGHT
{
	float4		dif;	// 拡散光
	float4		amb;	// 環境光
	float4		spc;	// 反射光
	float3		pos;	// 座標
	float3		dir;	// 平行光源
}LIGHT;

// マテリアル
typedef struct _MATERIAL
{	// D3DMATERIAL9と同じ並び
	float4		dif;	// 拡散光
	float4		amb;	// 環境光
	float4		spc;	// 反射光
	float4		emi;	// 自発光
	float		pwr;	// 反射光のパワー値
}MATERIAL;


LIGHT		lt;
MATERIAL	mat;

// テクスチャ
texture tex;
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
	float3	nor : NORMAL;
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
	//float3 nor = mul(In.nor, world);
	Out.nor = mul(In.nor, world);

   // 反射する光の強さを算出
	//float Power = saturate(dot(normalize(nor), -normalize(dir_lt)));
	//Power = clamp(Power, 0.0f, 1.0f);

	//// ランパード反射
	//Out.col = mat.dif * lt.dif;
	//Out.col = Out.col + mat.amb * lt.amb;
	//Out.col = Out.col + mat.emi;


	//// スペキュラ反射（調整中）
	////float4 spc_temp = float4(0.0f, 0.0f, 1.0f, 1.0f);
	//float3 eyePos = float3(view._41, view._42, view._43);
	//float3	V = normalize(eyePos - Out.pos);		// （カメラ座標ー頂点座標）ベクトル
	////float3	H = -normalize(V + dir_lt);		//  ハーフベクトル（視線ベクトルと光の方向ベクトル）
	//float3	R = normalize(2 * dot(lt.dir, Out.nor) * Out.nor - lt.dir);
	//float specularLight = pow(saturate(dot(R, V)), 1.5f);
	////Out.col = Out.col + (spc_temp * specularLight);
	//Out.col = Out.col + (mat.spc * specularLight);

	//// 反射する光の強さを算出
	//Out.col = Out.col * saturate(dot(normalize(Out.nor), -normalize(lt.dir)));

	//// α値は入力値をそのまま使用
	//Out.col.a = mat.dif.a;

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
	// 法線ベクトル
	float3 n = normalize(In.nor.xyz);
	// 視点から頂点のベクトル
	float3 v = normalize(eye.xyz - In.pos.xyz);
	// ライト座標から頂点のベクトル（現状は平行光源のみなのでDirを代入
	float3 l = lt.dir.xyz; /*normalize(lt.pos.xyz - In.pos.xyz);*/
	// ライト座標から頂点までの距離を求める
	//float  d = length(l);
	// ライト座標から頂点のベクトルを正規化
	l = normalize(l);
	// 反射光のベクトルを計算
	float3 r = 2.0 * n * dot(n, l) - l;
	// 距離減退を計算（現状は使わない）
	float  a = 1.0f;
	//a = saturate(1.0f / (pntLight.attenuate.x + pntLight.attenuate.y * d + pntLight.attenuate.z * d * d)); //減衰

	float powTmp = pow(saturate(dot(r, v)), mat.pwr);
	//float powTmp = 1.0f;

	// 環境光を計算
	float3 iA =										mat.amb.xyz * lt.amb.xyz;
	// 拡散光を計算
	float3 iD = saturate(dot(l, n)) *				mat.dif.xyz * lt.dif.xyz * a;
	// 反射光を計算
	float3 iS = powTmp * (mat.spc.xyz * lt.spc.xyz) * a;
	//float3 iS = pow(saturate(dot(r, v)), mat.pwr) * (mat.spc.xyz * lt.spc.xyz) * a;


	float4 iColor = float4(iA + iD /*+ iS*/, 1.0f);

	float4 texcolor = tex2D(smp, In.uv);
	//texcolor = iColor;
	//texcolor.x = iColor.x;
	texcolor.xyz = texcolor.xyz + iColor.xyz;
	//color.xyz = color.xyz * (iA + iD + iS);

	return float4(saturate(texcolor.xyz), 1.0f);
	//return float4(saturate(iA + iD + iS), 1.0);
	//return tex2D(smp, In.uv) * In.col;
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