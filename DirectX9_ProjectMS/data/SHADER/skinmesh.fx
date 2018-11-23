//
// Skinned Mesh Effect file 
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//

//float4 lhtDir = { 0.0f, 0.0f, -1.0f, 1.0f };    //light Direction 
//float4 lightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f }; // Light Diffuse
//float4 MaterialAmbient : MATERIALAMBIENT = { 0.1f, 0.1f, 0.1f, 1.0f };
//float4 MaterialDiffuse : MATERIALDIFFUSE = { 1.0f, 1.0f, 1.0f, 1.0f };

// Matrix Pallette
static const int MAX_MATRICES = 26;
float4x4    mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    mViewProj : VIEWPROJECTION;
float4x4	mView;
float4		eye;		// ���_���W
float4 test = float4(1.0f, 1.0f, 1.0f, 1.0f);


// ���C�g
typedef struct _LIGHT
{
	float4		dif;	// �g�U��
	float4		amb;	// ����
	float4		spc;	// ���ˌ�
	float3		pos;	// ���W
	float3		dir;	// ���s����
}LIGHT;

// �}�e���A��
typedef struct _MATERIAL
{	// D3DMATERIAL9�Ɠ�������
	float4		dif;	// �g�U��
	float4		amb;	// ����
	float4		spc;	// ���ˌ�
	float4		emi;	// ������
	float		pwr;	// ���ˌ��̃p���[�l
}MATERIAL;

LIGHT		lt;
MATERIAL	mat;

texture tex;			// �g�p����e�N�X�`��
sampler smp = sampler_state {
	texture = <tex>;
	//MinFilter = LINEAR;
	//MagFilter = LINEAR;
	//MipFilter = NONE;

	//AddressU = Clamp;
	//AddressV = Clamp;
};

float4x4 Scl(float scl)
{
	float4x4 mtx;
	mtx._11 = scl;
	mtx._12 = 0.0f;
	mtx._13 = 0.0f;
	mtx._14 = 0.0f;
	mtx._21 = 0.0f;
	mtx._22 = scl;
	mtx._23 = 0.0f;
	mtx._24 = 0.0f;
	mtx._31 = 0.0f;
	mtx._32 = 0.0f;
	mtx._33 = scl;
	mtx._34 = 0.0f;
	mtx._41 = 0.0f;
	mtx._42 = 0.0f;
	mtx._43 = 0.0f;
	mtx._44 = 1.0f;
	return mtx;
}

///////////////////////////////////////////////////////
struct VS_IN
{
	float4	Pos				: POSITION;
	float4	BlendWeights	: BLENDWEIGHT;
	float4	BlendIndices	: BLENDINDICES;
	float3	Normal			: NORMAL;
	float3	Tex0			: TEXCOORD0;
};

struct VS_OUT
{
	float4	Pos				: POSITION;
	float4	Color			: COLOR;
	float2	Tex0			: TEXCOORD0;
	float3	Normal			: TEXCOORD1;
	float4	Specular		: TEXCOORD2;
};

//
//float3 Diffuse(float3 Normal)
//{
//	float CosTheta;
//
//	// N.L Clamped
//	CosTheta = max(0.0f, dot(Normal, lhtDir.xyz));
//
//	// propogate scalar result to vector
//	return (CosTheta);
//}


VS_OUT VSOutline(VS_IN In, uniform int NumBones)
{
	VS_OUT	Out = (VS_OUT)0;
	float3      Pos = 0.0f;
	float       LastWeight = 0.0f;

	// Compensate for lack of UBYTE4 on Geforce3
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	// cast the vectors to arrays for use in the for loop below
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;

	// calculate the pos/normal using the "normal" weights 
	//        and accumulate the weights to calculate the last weight
	for (int iBone = 0; iBone < NumBones - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.Pos , mul(mWorldMatrixArray[IndexArray[iBone]], mView)) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	// Now that we have the calculated weight, add in the final influence
	Pos += (mul(In.Pos, mul(mWorldMatrixArray[IndexArray[NumBones - 1]], mView)) * LastWeight);

	// transform position from world space into view and then projection space
	Out.Pos = mul(float4(Pos.xyz, 1.0f), mViewProj);

	//Out.Pos.x += 1.0f;

	Out.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return Out;
}


VS_OUT VShade(VS_IN In, uniform int NumBones)
{
	VS_OUT	Out = (VS_OUT)0;
	float3      Pos = 0.0f;
	float       LastWeight = 0.0f;

	float3	N = 0.0f;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L = 0.0f;		// ���̍������ޕ���
	float3	P = 0.0f;		// ���[���h��ԏ�̒��_���W
	float3	V = 0.0f;		// �i�J�������W�[���_���W�j�x�N�g��
	float3  H = 0.0f;		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j

	// Compensate for lack of UBYTE4 on Geforce3
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	// cast the vectors to arrays for use in the for loop below
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;

	// calculate the pos/normal using the "normal" weights 
	//        and accumulate the weights to calculate the last weight
	for (int iBone = 0; iBone < NumBones - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.Pos, mul(mWorldMatrixArray[IndexArray[iBone]], mView)) * BlendWeightsArray[iBone];
		Out.Normal += mul(In.Normal, (float3x3)mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	// Now that we have the calculated weight, add in the final influence
	Pos += (mul(In.Pos, mul(mWorldMatrixArray[IndexArray[NumBones - 1]],mView)) * LastWeight);
	Out.Normal += (mul(In.Normal, (float3x3)mWorldMatrixArray[IndexArray[NumBones - 1]]) * LastWeight);

	// transform position from world space into view and then projection space
	Out.Pos = mul(float4(Pos.xyz, 1.0f), mViewProj);

	// normalize normals
	Out.Normal = normalize(Out.Normal);


	P = Out.Pos.xyz;

	N = Out.Normal;

	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(-lt.dir);

	// �����x�N�g�������߂�
	V = normalize(eye.xyz - P);

	// ���x�N�g���Ǝ����Ƃ̃n�[�t�x�N�g�������߂�
	H = normalize(L + V);

	// �����v�Z���s���ďo�̓J���[�����߂�
	Out.Color = mat.emi + 
		lt.amb * mat.amb +
		lt.dif * mat.dif *
		max(0.0f, dot(N, L));	// 0.0�����̏ꍇ��0.0��

	Out.Color.a = mat.dif.a;

	// �X�y�L�����[�ɂ�锽�ːF���v�Z�@g_power���傫���قǉs������
	Out.Specular = lt.spc * mat.spc *
		pow(max(0.0f, dot(N, H)), mat.pwr);

	// copy the input texture coordinate through
	Out.Tex0 = In.Tex0.xy;
	return Out;
}

int CurNumBones = 2;
VertexShader vsArray[4] = { compile vs_3_0 VShade(1),
							compile vs_3_0 VShade(2),
							compile vs_3_0 VShade(3),
							compile vs_3_0 VShade(4)
};

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_nomal(VS_OUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(In.Color * tex2D(smp, In.Tex0)/* + In.Specular*/);
	out_color.a = In.Color.a;
	return out_color;
}

float4 ps_notex(VS_OUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(In.Color /*+ In.Specular*/);
	out_color.a = In.Color.a;
	return out_color;
}

float4 ps_Outline(VS_OUT In) : COLOR0
{
	return In.Color;
}


//////////////////////////////////////
// Techniques specs follow
//////////////////////////////////////
technique t0
{
	//pass p0
	//{
	//	VertexShader = compile vs_3_0 VSOutline(2);
	//	PixelShader = compile ps_3_0 ps_Outline();
	//}

	pass p0
	{
		VertexShader = (vsArray[CurNumBones]);
		PixelShader = compile ps_3_0 ps_nomal();
	}
}

technique t1
{
	pass p0
	{
		VertexShader = (vsArray[CurNumBones]);
		PixelShader = compile ps_3_0 ps_notex();
	}
}


