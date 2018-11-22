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
float4x3    mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    mViewProj : VIEWPROJECTION;
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

///////////////////////////////////////////////////////
struct VS_INPUT
{
	float4  Pos             : POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float3  Normal          : NORMAL;
	float3  Tex0            : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4  Pos     : POSITION;
	float4  Diffuse : COLOR;
	float4  Specular : TEXCOORD1;
	float2  Tex0    : TEXCOORD0;
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


VS_OUTPUT VShade(VS_INPUT i, uniform int NumBones)
{
	VS_OUTPUT   o;
	float3      Pos = 0.0f;
	float       LastWeight = 0.0f;

	float3	N = 0.0f;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L = 0.0f;		// ���̍������ޕ���
	float3	P = 0.0f;		// ���[���h��ԏ�̒��_���W
	float3	V = 0.0f;		// �i�J�������W�[���_���W�j�x�N�g��
	float3  H = 0.0f;		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j

	// Compensate for lack of UBYTE4 on Geforce3
	int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);

	// cast the vectors to arrays for use in the for loop below
	float BlendWeightsArray[4] = (float[4])i.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;

	// calculate the pos/normal using the "normal" weights 
	//        and accumulate the weights to calculate the last weight
	for (int iBone = 0; iBone < NumBones - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(i.Pos, mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		N += mul(i.Normal, (float3x3)mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
	}
	LastWeight = 1.0f - LastWeight;

	// Now that we have the calculated weight, add in the final influence
	Pos += (mul(i.Pos, mWorldMatrixArray[IndexArray[NumBones - 1]]) * LastWeight);
	N += (mul(i.Normal, (float3x3)mWorldMatrixArray[IndexArray[NumBones - 1]]) * LastWeight);

	// transform position from world space into view and then projection space
	o.Pos = mul(float4(Pos.xyz, 1.0f), mViewProj);

	P = o.Pos;

	// normalize normals
	N = normalize(N);

	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(-lt.dir);

	// �����x�N�g�������߂�
	V = normalize(eye - P);

	// ���x�N�g���Ǝ����Ƃ̃n�[�t�x�N�g�������߂�
	H = normalize(L + V);

	// �����v�Z���s���ďo�̓J���[�����߂�
	o.Diffuse = lt.amb * mat.amb +
		lt.dif * mat.dif *
		max(0.0f, dot(L, N));	// 0.0�����̏ꍇ��0.0��

	o.Diffuse.a = mat.dif.a;

	// �X�y�L�����[�ɂ�锽�ːF���v�Z�@g_power���傫���قǉs������
	o.Specular = lt.spc * mat.spc *
		pow(max(0.0f, dot(N, H)), mat.pwr);

	// copy the input texture coordinate through
	o.Tex0 = i.Tex0.xy;

	return o;
}

int CurNumBones = 4;
VertexShader vsArray[4] = { compile vs_3_0 VShade(1),
							compile vs_3_0 VShade(2),
							compile vs_3_0 VShade(3),
							compile vs_3_0 VShade(4)
};

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
float4 ps_nomal(VS_OUTPUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(test * tex2D(smp, In.Tex0)/* + In.Specular*/);
	out_color.a = In.Diffuse.a;
	return out_color;
}

float4 ps_notex(VS_OUTPUT In) : COLOR0
{
	float4 out_color;
	// �e�N�X�`���̐F�ƃ|���S���̐F���|�����킹�ďo��
	out_color = saturate(test/* + In.Specular*/);
	out_color.a = In.Diffuse.a;
	return out_color;
}

//////////////////////////////////////
// Techniques specs follow
//////////////////////////////////////
technique t0
{
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


