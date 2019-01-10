//=============================================================================
//
// PMX�ǂݍ��ݏ��� [ModelLoaderPMX.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ModelLoaderPMX.h"

#include "BaseFunc.h"

#include	<minwindef.h>
#include	<sys/stat.h>	// �t�@�C���T�C�Y����p

//#define FILE_PATH "Lat_Pastry.pmx"
#define FILE_PATH "v_flower.pmx"


#define SINTABLE_DIV						(65536)				// �T�C���e�[�u���̐��x

#define PMX_MAX_IKLINKNUM		(64)			// �Ή�����IK�����N�̍ő吔

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif


struct PMX_BASEINFO
{
	BYTE	EncodeType;						// �����R�[�h�̃G���R�[�h�^�C�v 0:UTF16 1:UTF8
	BYTE	UVNum;							// �ǉ��t�u�� ( 0�`4 )
	BYTE	VertexIndexSize;				// ���_Index�T�C�Y ( 1 or 2 or 4 )
	BYTE	TextureIndexSize;				// �e�N�X�`��Index�T�C�Y ( 1 or 2 or 4 )
	BYTE	MaterialIndexSize;				// �}�e���A��Index�T�C�Y ( 1 or 2 or 4 )
	BYTE	BoneIndexSize;					// �{�[��Index�T�C�Y ( 1 or 2 or 4 )
	BYTE	MorphIndexSize;					// ���[�tIndex�T�C�Y ( 1 or 2 or 4 )
	BYTE	RigidIndexSize;					// ����Index�T�C�Y ( 1 or 2 or 4 )
};
struct PMX_TXTBUF
{
	int		TxtSize;
	BYTE	*Txt;
};

// ���_�f�[�^
struct PMX_VERTEX
{
	float	Position[3];					// ���W
	float	Normal[3];						// �@��
	float	UV[2];							// �W��UV�l
	float	AddUV[4][4];					// �ǉ�UV�l
	BYTE	WeightType;						// �E�G�C�g�^�C�v( 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF )
	int		BoneIndex[4];					// �{�[���C���f�b�N�X
	float	BoneWeight[4];					// �{�[���E�F�C�g
	float	SDEF_C[3];						// SDEF-C
	float	SDEF_R0[3];						// SDEF-R0
	float	SDEF_R1[3];						// SDEF-R1
	float	ToonEdgeScale;					// �g�D�[���G�b�W�̃X�P�[��
};

// �ʃ��X�g
struct PMX_FACE
{
	int		VertexIndex[3];
};

// �e�N�X�`�����
struct PMX_TEXTURE
{
	wchar_t	TexturePath[512];
};

// �}�e���A�����
struct PMX_MATERIAL
{
	wchar_t	Name[128];						// ���O

	float	Diffuse[4];						// �f�B�t���[�Y�J���[
	float	Specular[3];						// �X�y�L�����J���[
	float	SpecularPower;						// �X�y�L�����萔
	float	Ambient[3];						// �A���r�G���g�J���[

	BYTE	CullingOff;						// ���ʕ`��
	BYTE	GroundShadow;						// �n�ʉe
	BYTE	SelfShadowMap;						// �Z���t�V���h�E�}�b�v�ւ̕`��
	BYTE	SelfShadowDraw;					// �Z���t�V���h�E�̕`��
	BYTE	EdgeDraw;							// �G�b�W�̕`��

	float	EdgeColor[4];					// �G�b�W�J���[
	float	EdgeSize;							// �G�b�W�T�C�Y

	int		TextureIndex;						// �ʏ�e�N�X�`���C���f�b�N�X
	int		SphereTextureIndex;				// �X�t�B�A�e�N�X�`���C���f�b�N�X
	BYTE	SphereMode;						// �X�t�B�A���[�h( 0:���� 1:��Z 2:���Z 3:�T�u�e�N�X�`��(�ǉ�UV1��x,y��UV�Q�Ƃ��Ēʏ�e�N�X�`���`����s��)

	BYTE	ToonFlag;							// ���L�g�D�[���t���O( 0:��Toon 1:���LToon )
	int		ToonTextureIndex;					// �g�D�[���e�N�X�`���C���f�b�N�X

	int		MaterialFaceNum;					// �}�e���A�����K������Ă���ʂ̐�
};

// �h�j�����N���
struct PMX_IKLINK
{
	int		BoneIndex;							// �����N�{�[���̃C���f�b�N�X
	BYTE	RotLockFlag;						// ��]����( 0:OFF 1:ON )
	float	RotLockMin[3];					// ��]�����A����
	float	RotLockMax[3];					// ��]�����A���
};

// �h�j���
struct PMX_IK
{
	int		TargetBoneIndex;					// IK�^�[�Q�b�g�̃{�[���C���f�b�N�X
	int		LoopNum;							// IK�v�Z�̃��[�v��
	float	RotLimit;							// �v�Z���ӂ�̐����p�x

	int		LinkNum;							// �h�j�����N�̐�
	PMX_IKLINK Link[PMX_MAX_IKLINKNUM];		// �h�j�����N���
};

// �{�[�����
struct PMX_BONE
{
	wchar_t	Name[128];						// ���O
	float	Position[3];						// ���W
	int		ParentBoneIndex;					// �e�{�[���C���f�b�N�X
	int		TransformLayer;					// �ό`�K�w

	BYTE	Flag_LinkDest;						// �ڑ���
	BYTE	Flag_EnableRot;					// ��]���ł��邩
	BYTE	Flag_EnableMov;					// �ړ����ł��邩
	BYTE	Flag_Disp;							// �\��
	BYTE	Flag_EnableControl;				// ���삪�ł��邩
	BYTE	Flag_IK;							// IK
	BYTE	Flag_AddRot;						// ��]�t�^
	BYTE	Flag_AddMov;						// �ړ��t�^
	BYTE	Flag_LockAxis;						// ���Œ�
	BYTE	Flag_LocalAxis;					// ���[�J����
	BYTE	Flag_AfterPhysicsTransform;		// ������ό`
	BYTE	Flag_OutParentTransform;			// �O���e�ό`

	float	OffsetPosition[3];				// �I�t�Z�b�g���W
	int		LinkBoneIndex;						// �ڑ���{�[���C���f�b�N�X
	int		AddParentBoneIndex;				// �t�^�e�{�[���C���f�b�N�X
	float	AddRatio;							// �t�^��
	float	LockAxisVector[3];				// ���Œ莞�̎��̕����x�N�g��
	float	LocalAxisXVector[3];				// ���[�J�����̂w��
	float	LocalAxisZVector[3];				// ���[�J�����̂y��
	int		OutParentTransformKey;				// �O���e�ό`���� Key�l

	PMX_IK	IKInfo;							// �h�j���
};

// ���_���[�t���
struct PMX_MORPH_VERTEX
{
	int		Index;								// ���_�C���f�b�N�X
	float	Offset[3];						// ���_���W�I�t�Z�b�g
};

// �t�u���[�t���
struct PMX_MORPH_UV
{
	int		Index;								// ���_�C���f�b�N�X
	FLOAT4	Offset;							// ���_�t�u�I�t�Z�b�g
};

// �{�[�����[�t���
struct PMX_MORPH_BONE
{
	int		Index;								// �{�[���C���f�b�N�X
	float	Offset[3];						// ���W�I�t�Z�b�g
	float	Quat[4];							// ��]�N�H�[�^�j�I��
};

// �ގ����[�t���
struct PMX_MORPH_MATERIAL
{
	int		Index;								// �}�e���A���C���f�b�N�X
	BYTE	CalcType;							// �v�Z�^�C�v( 0:��Z  1:���Z )
	float	Diffuse[4];						// �f�B�t���[�Y�J���[
	float	Specular[3];						// �X�y�L�����J���[
	float	SpecularPower;						// �X�y�L�����W��
	float	Ambient[3];						// �A���r�G���g�J���[
	float	EdgeColor[4];					// �G�b�W�J���[
	float	EdgeSize;							// �G�b�W�T�C�Y
	float	TextureScale[4];					// �e�N�X�`���W��
	float	SphereTextureScale[4];			// �X�t�B�A�e�N�X�`���W��
	float	ToonTextureScale[4];				// �g�D�[���e�N�X�`���W��
};

// �O���[�v���[�t
struct PMX_MORPH_GROUP
{
	int		Index;								// ���[�t�C���f�b�N�X
	float	Ratio;								// ���[�t��
};

// ���[�t���
struct PMX_MORPH
{
	wchar_t	Name[128];						// ���O

	BYTE	ControlPanel;						// ����p�l��
	BYTE	Type;								// ���[�t�̎��  0:�O���[�v 1:���_ 2:�{�[�� 3:UV 4:�ǉ�UV1 5:�ǉ�UV2 6:�ǉ�UV3 7:�ǉ�UV4 8:�ގ�

	int		DataNum;							// ���[�t���̐�

	union
	{
		PMX_MORPH_VERTEX *Vertex;				// ���_���[�t
		PMX_MORPH_UV *UV;						// UV���[�t
		PMX_MORPH_BONE *Bone;					// �{�[�����[�t
		PMX_MORPH_MATERIAL *Material;			// �}�e���A�����[�t
		PMX_MORPH_GROUP *Group;				// �O���[�v���[�t
	};
};

// ���̏��
struct PMX_RIGIDBODY
{
	wchar_t	Name[128];						// ���O

	int		BoneIndex;							// �Ώۃ{�[���ԍ�

	BYTE	RigidBodyGroupIndex;				// ���̃O���[�v�ԍ�
	WORD	RigidBodyGroupTarget;				// ���̃O���[�v�Ώ�

	BYTE	ShapeType;							// �`��( 0:��  1:��  2:�J�v�Z�� )
	float	ShapeW;							// ��
	float	ShapeH;							// ����
	float	ShapeD;							// ���s

	float	Position[3];						// �ʒu
	float	Rotation[3];						// ��]( ���W�A�� )

	float	RigidBodyWeight;					// ����
	float	RigidBodyPosDim;					// �ړ�����
	float	RigidBodyRotDim;					// ��]����
	float	RigidBodyRecoil;					// ������
	float	RigidBodyFriction;					// ���C��

	BYTE	RigidBodyType;						// ���̃^�C�v( 0:Bone�Ǐ]  1:�������Z  2:�������Z(Bone�ʒu���킹) )
};

// �W���C���g���
struct PMX_JOINT
{
	wchar_t	Name[128];						// ���O

	BYTE	Type;								// ���( 0:�X�v�����O6DOF ( PMX2.0 �ł� 0 �̂� )

	int		RigidBodyAIndex;					// �ڑ��捄�̂`
	int		RigidBodyBIndex;					// �ڑ��捄�̂a

	float	Position[3];						// �ʒu
	float	Rotation[3];						// ��]( ���W�A�� )

	float	ConstrainPositionMin[3];			// �ړ�����-����
	float	ConstrainPositionMax[3];			// �ړ�����-���
	float	ConstrainRotationMin[3];			// ��]����-����
	float	ConstrainRotationMax[3];			// ��]����-���

	float	SpringPosition[3];				// �o�l�萔-�ړ�
	float	SpringRotation[3];				// �o�l�萔-��]
};


typedef struct
{
	int				VertexNum;
	PMX_VERTEX		*Vertex;
}PMX;


// �e�L�X�g�f�[�^��wchar_t�ɕϊ����Ď擾
__inline void MV1LoadModelToPMX_GetString(BYTE **Src, wchar_t *DestBuffer, BYTE EncodeType)
{
	char Buffer[1024];
	wchar_t WBuffer[1024];
	DWORD TextSize;

	TextSize = GET_MEM_DWORD(*Src);
	*Src = *Src + 4;

	if (EncodeType == 0)
	{
		// UTF16

		_MEMCPY(WBuffer, *Src, TextSize);
		((BYTE *)WBuffer)[TextSize] = 0;
		((BYTE *)WBuffer)[TextSize + 1] = 0;
		*Src = *Src + TextSize;

		// UTF16�� wchar_t �ɕϊ�
		//ConvString((const char *)WBuffer, DX_CHARCODEFORMAT_UTF16LE, (char *)DestBuffer, BUFFERBYTES_CANCEL, WCHAR_T_CHARCODEFORMAT);
	}
	else
		if (EncodeType == 1)
		{
			// UTF8
			_MEMCPY(Buffer, *Src, TextSize);
			Buffer[TextSize] = '\0';
			*Src = *Src + TextSize;

			// UTF-8�� wchar_t �ɕϊ�
			//ConvString((const char *)Buffer, DX_CHARCODEFORMAT_UTF8, (char *)DestBuffer, BUFFERBYTES_CANCEL, WCHAR_T_CHARCODEFORMAT);
		}
}

// �����l�T�C�Y�ɍ��킹�������l���擾����(32bit�ȊO�����Ȃ�)
__inline int MV1LoadModelToPMX_GetUInt(BYTE **Src, BYTE Size)
{
	int res = 0;

	switch (Size)
	{
	case 1:
		res = (int)((*Src)[0]);
		*Src = *Src + 1;
		break;

	case 2:
		res = (int)(((WORD *)*Src)[0]);
		*Src = *Src + 2;
		break;

	case 4:
		res = ((int *)*Src)[0];
		*Src = *Src + 4;
		break;
	}

	return res;
}


// �����l�T�C�Y�ɍ��킹�������l���擾����(��������)
__inline int MV1LoadModelToPMX_GetInt(BYTE **Src, BYTE Size)
{
	int res = 0;

	switch (Size)
	{
	case 1:
		res = GET_MEM_SIGNED_BYTE(*Src);
		*Src = *Src + 1;
		break;

	case 2:
		res = GET_MEM_SIGNED_WORD(*Src);
		*Src = *Src + 2;
		break;

	case 4:
		res = GET_MEM_SIGNED_DWORD(*Src);
		*Src = *Src + 4;
		break;
	}

	return res;
}


long GetFileSize(const char *file)
{
	struct stat statBuf;

	if (stat(file, &statBuf) == 0)
		return statBuf.st_size;

	return -1L;
}


//=============================================================================
// �ǂݍ��ݏ���
//=============================================================================
int LoadPmx(void)
{
	int NewHandle = -1;
	int ErrorFlag = 1;
	int i, j, k, weightcount, facecount;
	FILE *fp;
	BYTE *Src;
	BYTE *SrcFirst;
	PMX pmx;

	PMX_BASEINFO PmxInfo;
	BYTE AddHeadDataSize;
	DWORD PmxVertexNum;
	PMX_VERTEX *PmxVertex = NULL;
	DWORD PmxFaceNum;
	PMX_FACE *PmxFace = NULL;
	DWORD PmxTextureNum;
	PMX_TEXTURE *PmxTexture = NULL;
	DWORD PmxMaterialNum;
	PMX_MATERIAL *PmxMaterial = NULL;
	DWORD PmxBoneNum = 0;
	PMX_BONE *PmxBone = NULL;
	DWORD PmxIKNum;
	DWORD PmxSkinNum;
	DWORD PmxMorphNum;
	PMX_MORPH *PmxMorph = NULL;
	DWORD PmxRigidbodyNum;
	PMX_RIGIDBODY *PmxRigidbody = NULL;
	DWORD PmxJointNum;
	PMX_JOINT *PmxJoint = NULL;


	// �t�@�C���T�C�Y���m�F
	long lFileSize = GetFileSize(FILE_PATH);
	printf("%d : �t�@�C���T�C�Y���m�F\n", lFileSize);

	// �t�@�C����S�ēǂݍ��ނ��߂̃o�b�t�@�����
	Src = new BYTE[lFileSize + 1];
	// �擪�A�h���X��ۊ�
	SrcFirst = Src;

	// �o�C�i���ǂݎ�胂�[�h�Ńt�@�C���I�[�v��
	fopen_s(&fp, FILE_PATH, "rb");
	if (fp == NULL) {
		printf("�t�@�C�����J���܂���B\n");
		getchar();
		return -1;
	}

	// �t�@�C�����o�b�t�@�ɓǂݍ���
	fread(&*Src, lFileSize, 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	// �����ɔO�̂��� NULL �����Ă���
	Src[lFileSize] = NULL;

	// PMX�t�@�C�����ǂ������m�F
	if (Src[0] != 'P' || Src[1] != 'M' || Src[2] != 'X' || Src[3] != ' ')
		return -1;
	Src += 4;

	// Ver2.0 �����m�F
	if (Src[0] != 0x00 || Src[1] != 0x00 || Src[2] != 0x00 || Src[3] != 0x40)
	{
		printf("PMX Ver2.0�ł͂Ȃ�\n");
		return -1;
	}
	Src += 4;

	// �ǉ����̃T�C�Y���擾
	AddHeadDataSize = Src[0];
	Src++;

	// �ǉ������擾
	PmxInfo.EncodeType = Src[0];
	PmxInfo.UVNum = Src[1];
	PmxInfo.VertexIndexSize = Src[2];
	PmxInfo.TextureIndexSize = Src[3];
	PmxInfo.MaterialIndexSize = Src[4];
	PmxInfo.BoneIndexSize = Src[5];
	PmxInfo.MorphIndexSize = Src[6];
	PmxInfo.RigidIndexSize = Src[7];
	Src += AddHeadDataSize;

	printf("%d : [0] - �G���R�[�h����  | 0:UTF16 1:UTF8\n", PmxInfo.EncodeType);
	printf("%d : [1] - �ǉ�UV�� 	| 0�`4 �ڍׂ͒��_�Q��\n", PmxInfo.UVNum);
	printf("%d : [2] - ���_Index�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.VertexIndexSize);
	printf("%d : [3] - �e�N�X�`��Index�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.TextureIndexSize);
	printf("%d : [4] - �ގ�Index�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.MaterialIndexSize);
	printf("%d : [5] - �{�[��Index�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.BoneIndexSize);
	printf("%d : [6] - ���[�tIndex�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.MorphIndexSize);
	printf("%d : [7] - ����Index�T�C�Y | 1,2,4 �̂����ꂩ\n", PmxInfo.RigidIndexSize);
	printf("\n");

	// ���f�����X�L�b�v
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;
	Src += GET_MEM_DWORD(Src) + 4;

	// ���_�����擾
	PmxVertexNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : ���_��\n", PmxVertexNum);

	// ���_�f�[�^���i�[���郁�����̈�̊m��
	PmxVertex = new PMX_VERTEX[PmxVertexNum];
	if (PmxVertex == NULL)
	{
		printf("�������m�ۂɎ��s�F���_\n");
		goto ENDLABEL;
	}

	// ���_�f�[�^���擾
	for (i = 0; (DWORD)i < PmxVertexNum; i++)
	{
		READ_MEM_4BYTE(&PmxVertex[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxVertex[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxVertex[i].Position[2], &Src[8]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[0], &Src[12]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[1], &Src[16]);
		READ_MEM_4BYTE(&PmxVertex[i].Normal[2], &Src[20]);
		READ_MEM_4BYTE(&PmxVertex[i].UV[0], &Src[24]);
		READ_MEM_4BYTE(&PmxVertex[i].UV[1], &Src[28]);
		Src += 32;

		//printf("pos[%2.2f, %2.2f, %2.2f]  nor[%2.2f, %2.2f, %2.2f]  uv[%2.2f, %2.2f]\n",
		//	PmxVertex[i].Position[0], PmxVertex[i].Position[1], PmxVertex[i].Position[2],
		//	PmxVertex[i].Normal[0], PmxVertex[i].Normal[1], PmxVertex[i].Normal[2],
		//	PmxVertex[i].UV[0], PmxVertex[i].UV[1]);

		for (j = 0; j < PmxInfo.UVNum; j++)
		{
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].AddUV[j][0], &Src[12]);
			Src += 16;
		}

		PmxVertex[i].WeightType = Src[0];
		Src++;

		PmxVertex[i].BoneIndex[0] = -1;
		PmxVertex[i].BoneIndex[1] = -1;
		PmxVertex[i].BoneIndex[2] = -1;
		PmxVertex[i].BoneIndex[3] = -1;
		switch (PmxVertex[i].WeightType)
		{
		case 0:	// BDEF1
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneWeight[0] = 1.0f;
			break;

		case 1:	// BDEF2
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], Src);
			Src += 4;
			PmxVertex[i].BoneWeight[1] = 1.0f - PmxVertex[i].BoneWeight[0];
			break;

		case 2:	// BDEF4
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[2] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[3] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[1], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[2], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[3], &Src[12]);
			Src += 16;
			break;

		case 3:	// SDEF
			PmxVertex[i].BoneIndex[0] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxVertex[i].BoneIndex[1] = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxVertex[i].BoneWeight[0], Src);
			Src += 4;
			PmxVertex[i].BoneWeight[1] = 1.0f - PmxVertex[i].BoneWeight[0];
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[0], &Src[0]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[1], &Src[4]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_C[2], &Src[8]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[0], &Src[12]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[1], &Src[16]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R0[2], &Src[20]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[0], &Src[24]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[1], &Src[28]);
			READ_MEM_4BYTE(&PmxVertex[i].SDEF_R1[2], &Src[32]);
			Src += 36;
			break;
		}

		READ_MEM_4BYTE(&PmxVertex[i].ToonEdgeScale, Src);
		Src += 4;
	}

	// �ʂ̐����擾
	PmxFaceNum = GET_MEM_DWORD(Src) / 3;
	Src += 4;
	printf("%d : �ʐ�\n", PmxFaceNum);

	// �ʃf�[�^���i�[���郁�����̈�̊m��
	PmxFace = new PMX_FACE[PmxFaceNum];
	if (PmxFace == NULL)
	{
		printf("�������m�ۂɎ��s�F��\n");
		goto ENDLABEL;
	}

	// �ʂ��\�����钸�_�C���f�b�N�X�̎擾
	switch (PmxInfo.VertexIndexSize)
	{
	case 1:	// BYTE
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_BYTE(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_BYTE(&Src[1]);
			PmxFace[i].VertexIndex[2] = GET_MEM_BYTE(&Src[2]);
			Src += 3;
		}
		break;

	case 2:	// SHORT
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_WORD(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_WORD(&Src[2]);
			PmxFace[i].VertexIndex[2] = GET_MEM_WORD(&Src[4]);
			Src += 6;
		}
		break;

	case 4: // INT
		for (i = 0; (DWORD)i < PmxFaceNum; i++)
		{
			PmxFace[i].VertexIndex[0] = GET_MEM_DWORD(&Src[0]);
			PmxFace[i].VertexIndex[1] = GET_MEM_DWORD(&Src[4]);
			PmxFace[i].VertexIndex[2] = GET_MEM_DWORD(&Src[8]);
			Src += 12;
		}
		break;
	}

	// �e�N�X�`���̐����擾
	PmxTextureNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : �e�N�X�`����\n", PmxTextureNum);

	// �e�N�X�`���f�[�^���i�[���郁�����̈�̊m��
	PmxTexture = new PMX_TEXTURE[PmxTextureNum];
	if (PmxTexture == NULL)
	{
		printf("�������m�ۂɎ��s�F�e�N�X�`��\n");
		goto ENDLABEL;
	}

	// UTF16���ЂƂ܂��\��������
	//setlocale(LC_ALL, setlocale(LC_CTYPE, ""));

	// �e�N�X�`���̏����擾
	for (i = 0; (DWORD)i < PmxTextureNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxTexture[i].TexturePath, PmxInfo.EncodeType);
		//wprintf(L"%s", PmxTexture[i].TexturePath);
	}

	// �}�e���A���̐����擾
	PmxMaterialNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : �}�e���A����\n", PmxMaterialNum);

	// �}�e���A���f�[�^���i�[���郁�����̈�̊m��
	PmxMaterial = new PMX_MATERIAL[PmxMaterialNum];
	if (PmxMaterial == NULL)
	{
		printf("�������m�ۂɎ��s�F�}�e���A��\n");
		goto ENDLABEL;
	}

	// �}�e���A���̓ǂ݂���
	for (i = 0; (DWORD)i < PmxMaterialNum; i++)
	{
		// �ގ����̎擾
		MV1LoadModelToPMX_GetString(&Src, PmxMaterial[i].Name, PmxInfo.EncodeType);
		if (PmxMaterial[i].Name[0] == L'\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxMaterial[i].Name, PmxInfo.EncodeType);
			if (PmxMaterial[i].Name[0] == L'\0')
			{
				//_SWNPRINTF(PmxMaterial[i].Name, sizeof(PmxMaterial[i].Name) / 2, L"Mat_%d", i);
			}
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[2], &Src[8]);
		READ_MEM_4BYTE(&PmxMaterial[i].Diffuse[3], &Src[12]);
		Src += 16;

		READ_MEM_4BYTE(&PmxMaterial[i].Specular[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Specular[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Specular[2], &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxMaterial[i].SpecularPower, &Src[0]);
		Src += 4;

		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].Ambient[2], &Src[8]);
		Src += 12;

		PmxMaterial[i].CullingOff = (BYTE)((*Src & 0x01) ? 1 : 0);
		PmxMaterial[i].GroundShadow = (BYTE)((*Src & 0x02) ? 1 : 0);
		PmxMaterial[i].SelfShadowMap = (BYTE)((*Src & 0x04) ? 1 : 0);
		PmxMaterial[i].SelfShadowDraw = (BYTE)((*Src & 0x08) ? 1 : 0);
		PmxMaterial[i].EdgeDraw = (BYTE)((*Src & 0x10) ? 1 : 0);
		Src++;

		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[0], &Src[0]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[1], &Src[4]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[2], &Src[8]);
		READ_MEM_4BYTE(&PmxMaterial[i].EdgeColor[3], &Src[12]);
		Src += 16;

		READ_MEM_4BYTE(&PmxMaterial[i].EdgeSize, Src);
		Src += 4;

		PmxMaterial[i].TextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);
		PmxMaterial[i].SphereTextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);

		PmxMaterial[i].SphereMode = *Src;
		Src++;

		PmxMaterial[i].ToonFlag = *Src;
		Src++;
		if (PmxMaterial[i].ToonFlag == 0)
		{
			PmxMaterial[i].ToonTextureIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.TextureIndexSize);
		}
		else
		{
			PmxMaterial[i].ToonTextureIndex = *Src;
			Src++;
		}

		// �����̓X�L�b�v
		Src += GET_MEM_DWORD(Src) + 4;

		PmxMaterial[i].MaterialFaceNum = GET_MEM_SIGNED_DWORD(Src);
		Src += 4;
	}

	// �{�[���̐����擾
	PmxBoneNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : �{�[����\n", PmxBoneNum);

	// �{�[���f�[�^���i�[���郁�����̈�̊m��
	PmxBone = new PMX_BONE[PmxBoneNum];
	if (PmxBone == NULL)
	{
		printf("�������m�ۂɎ��s�F�{�[��\n");
		goto ENDLABEL;
	}

	// �{�[�����̎擾
	PmxIKNum = 0;
	for (i = 0; (DWORD)i < PmxBoneNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxBone[i].Name, PmxInfo.EncodeType);
		if (PmxBone[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxBone[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		READ_MEM_4BYTE(&PmxBone[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxBone[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxBone[i].Position[2], &Src[8]);
		Src += 12;

		PmxBone[i].ParentBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
		PmxBone[i].TransformLayer = GET_MEM_SIGNED_DWORD(Src);
		Src += 4;

		WORD Flag = GET_MEM_WORD(Src);
		Src += 2;
		PmxBone[i].Flag_LinkDest = (BYTE)((Flag & 0x0001) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableRot = (BYTE)((Flag & 0x0002) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableMov = (BYTE)((Flag & 0x0004) != 0 ? 1 : 0);
		PmxBone[i].Flag_Disp = (BYTE)((Flag & 0x0008) != 0 ? 1 : 0);
		PmxBone[i].Flag_EnableControl = (BYTE)((Flag & 0x0010) != 0 ? 1 : 0);
		PmxBone[i].Flag_IK = (BYTE)((Flag & 0x0020) != 0 ? 1 : 0);
		PmxBone[i].Flag_AddRot = (BYTE)((Flag & 0x0100) != 0 ? 1 : 0);
		PmxBone[i].Flag_AddMov = (BYTE)((Flag & 0x0200) != 0 ? 1 : 0);
		PmxBone[i].Flag_LockAxis = (BYTE)((Flag & 0x0400) != 0 ? 1 : 0);
		PmxBone[i].Flag_LocalAxis = (BYTE)((Flag & 0x0800) != 0 ? 1 : 0);
		PmxBone[i].Flag_AfterPhysicsTransform = (BYTE)((Flag & 0x1000) != 0 ? 1 : 0);
		PmxBone[i].Flag_OutParentTransform = (BYTE)((Flag & 0x2000) != 0 ? 1 : 0);

		if (PmxBone[i].Flag_LinkDest == 0)
		{
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].OffsetPosition[2], &Src[8]);
			Src += 12;
		}
		else
		{
			PmxBone[i].LinkBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
		}

		if (PmxBone[i].Flag_AddRot == 1 || PmxBone[i].Flag_AddMov == 1)
		{
			PmxBone[i].AddParentBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			READ_MEM_4BYTE(&PmxBone[i].AddRatio, Src);
			Src += 4;
		}

		if (PmxBone[i].Flag_LockAxis == 1)
		{
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LockAxisVector[2], &Src[8]);
			Src += 12;
		}

		if (PmxBone[i].Flag_LocalAxis == 1)
		{
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisXVector[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[0], &Src[0]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[1], &Src[4]);
			READ_MEM_4BYTE(&PmxBone[i].LocalAxisZVector[2], &Src[8]);
			Src += 12;
		}

		if (PmxBone[i].Flag_OutParentTransform == 1)
		{
			PmxBone[i].OutParentTransformKey = GET_MEM_SIGNED_DWORD(Src);
			Src += 4;
		}

		if (PmxBone[i].Flag_IK == 1)
		{
			PmxIKNum++;

			PmxBone[i].IKInfo.TargetBoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
			PmxBone[i].IKInfo.LoopNum = GET_MEM_SIGNED_DWORD(Src);
			Src += 4;

			READ_MEM_4BYTE(&PmxBone[i].IKInfo.RotLimit, Src);
			Src += 4;

			PmxBone[i].IKInfo.LinkNum = *((int *)Src);
			Src += 4;
			if (PmxBone[i].IKInfo.LinkNum >= PMX_MAX_IKLINKNUM)
			{
				printf("IK�̏���l�𒴉߁F�{�[��\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxBone[i].IKInfo.LinkNum; j++)
			{
				PmxBone[i].IKInfo.Link[j].BoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
				PmxBone[i].IKInfo.Link[j].RotLockFlag = Src[0];
				Src++;

				if (PmxBone[i].IKInfo.Link[j].RotLockFlag == 1)
				{
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[0], &Src[0]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[1], &Src[4]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMin[2], &Src[8]);
					Src += 12;

					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[0], &Src[0]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[1], &Src[4]);
					READ_MEM_4BYTE(&PmxBone[i].IKInfo.Link[j].RotLockMax[2], &Src[8]);
					Src += 12;
				}
			}
		}
	}

	// ���[�t���̐����擾
	PmxMorphNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : ���[�t��\n", PmxMorphNum);

	// ���[�t�f�[�^���i�[���郁�����̈�̊m��
	PmxMorph = new PMX_MORPH[PmxMorphNum];
	if (PmxMorph == NULL)
	{
		printf("�������m�ۂɎ��s�F���[�t\n");
		goto ENDLABEL;
	}

	// ���[�t���̓ǂݍ���
	PmxSkinNum = 0;
	for (i = 0; (DWORD)i < PmxMorphNum; i++)
	{
		PmxMorph[i].Group = NULL;
		PmxMorph[i].Vertex = NULL;
		PmxMorph[i].Bone = NULL;
		PmxMorph[i].UV = NULL;
		PmxMorph[i].Material = NULL;

		MV1LoadModelToPMX_GetString(&Src, PmxMorph[i].Name, PmxInfo.EncodeType);
		if (PmxMorph[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxMorph[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		PmxMorph[i].ControlPanel = Src[0];
		PmxMorph[i].Type = Src[1];
		PmxMorph[i].DataNum = GET_MEM_SIGNED_DWORD(&Src[2]);
		Src += 6;

		switch (PmxMorph[i].Type)
		{
		case 0:	// �O���[�v���[�t
			PmxMorph[i].Group = new PMX_MORPH_GROUP[PmxMorph[i].DataNum];
			if (PmxMorph[i].Group == NULL)
			{
				printf("�������m�ۂɎ��s�F���[�t�O���[�v\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Group[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MorphIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Group[j].Ratio, Src);
				Src += 4;
			}
			break;

		case 1:	// ���_
			PmxSkinNum++;
			PmxMorph[i].Vertex = new PMX_MORPH_VERTEX[PmxMorph[i].DataNum];
			if (PmxMorph[i].Vertex == NULL)
			{
				printf("�������m�ۂɎ��s�F���[�t���_\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Vertex[j].Index = MV1LoadModelToPMX_GetUInt(&Src, PmxInfo.VertexIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Vertex[j].Offset[2], &Src[8]);
				Src += 12;
			}
			break;

		case 2:	// �{�[�����[�t
			PmxMorph[i].Bone = new PMX_MORPH_BONE[PmxMorph[i].DataNum];
			if (PmxMorph[i].Bone == NULL)
			{
				printf("�������m�ۂɎ��s�F�{�[�����[�t\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Bone[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Offset[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Bone[j].Quat[3], &Src[12]);
				Src += 16;
			}
			break;

		case 3:	// UV���[�t
		case 4:	// �ǉ�UV1���[�t
		case 5:	// �ǉ�UV2���[�t
		case 6:	// �ǉ�UV3���[�t
		case 7:	// �ǉ�UV4���[�t
			PmxMorph[i].UV = new PMX_MORPH_UV[PmxMorph[i].DataNum];
			if (PmxMorph[i].UV == NULL)
			{
				printf("�������m�ۂɎ��s�FUV���[�t\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].UV[j].Index = MV1LoadModelToPMX_GetUInt(&Src, PmxInfo.VertexIndexSize);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.x, &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.y, &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.z, &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].UV[j].Offset.w, &Src[12]);
				Src += 16;
			}
			break;

		case 8:	// �ގ����[�t
			PmxMorph[i].Material = new PMX_MORPH_MATERIAL[PmxMorph[i].DataNum];
			if (PmxMorph[i].Material == NULL)
			{
				printf("�������m�ۂɎ��s�F�}�e���A�����[�t\n");
				goto ENDLABEL;
			}

			for (j = 0; j < PmxMorph[i].DataNum; j++)
			{
				PmxMorph[i].Material[j].Index = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MaterialIndexSize);
				PmxMorph[i].Material[j].CalcType = Src[0];
				Src++;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Diffuse[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Specular[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SpecularPower, &Src[0]);
				Src += 4;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].Ambient[2], &Src[8]);
				Src += 12;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeColor[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].EdgeSize, &Src[0]);
				Src += 4;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].TextureScale[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].SphereTextureScale[3], &Src[12]);
				Src += 16;

				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[0], &Src[0]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[1], &Src[4]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[2], &Src[8]);
				READ_MEM_4BYTE(&PmxMorph[i].Material[j].ToonTextureScale[3], &Src[12]);
				Src += 16;
			}
			break;
		}
	}

	// �\���g�f�[�^�̓ǂݍ��݂̓X�L�b�v
	{
		DWORD PmxDispFrameNum;
		DWORD Num;
		BYTE Target;

		// �\���g�f�[�^�̐����擾
		PmxDispFrameNum = GET_MEM_DWORD(Src);
		Src += 4;

		// �g�̐������J��Ԃ�
		for (i = 0; (DWORD)i < PmxDispFrameNum; i++)
		{
			// ���O�ǂݔ�΂�
			Src += GET_MEM_DWORD(Src) + 4;
			Src += GET_MEM_DWORD(Src) + 4;

			// ����g�t���O�ǂݔ�΂�
			Src++;

			// �g���v�f�̐����擾
			Num = GET_MEM_DWORD(Src);
			Src += 4;

			// �g���v�f�̓ǂݔ�΂�
			for (j = 0; (DWORD)j < Num; j++)
			{
				// �v�f�Ώۂ��擾
				Target = Src[0];
				Src++;

				// �v�f�Ώۂɂ���ď����𕪊�
				switch (Target)
				{
				case 0:	// �{�[�����^�[�Q�b�g�̏ꍇ
					MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);
					break;

				case 1:	// ���[�t���^�[�Q�b�g�̏ꍇ
					MV1LoadModelToPMX_GetInt(&Src, PmxInfo.MorphIndexSize);
					break;
				}
			}
		}
	}

	// ���̏��̐����擾
	PmxRigidbodyNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : ���̐�\n", PmxRigidbodyNum);

	// ���̃f�[�^���i�[���郁�����̈�̊m��
	PmxRigidbody = new PMX_RIGIDBODY[PmxRigidbodyNum];
	if (PmxRigidbody == NULL)
	{
		printf("�������m�ۂɎ��s�F����\n");
		goto ENDLABEL;
	}

	// ���̏��̓ǂݍ���
	for (i = 0; (DWORD)i < PmxRigidbodyNum; i++)
	{
		MV1LoadModelToPMX_GetString(&Src, PmxRigidbody[i].Name, PmxInfo.EncodeType);
		if (PmxRigidbody[i].Name[0] == '\0')
		{
			MV1LoadModelToPMX_GetString(&Src, PmxRigidbody[i].Name, PmxInfo.EncodeType);
		}
		else
		{
			Src += GET_MEM_DWORD(Src) + 4;
		}

		PmxRigidbody[i].BoneIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.BoneIndexSize);

		PmxRigidbody[i].RigidBodyGroupIndex = Src[0];
		Src++;

		READ_MEM_2BYTE(&PmxRigidbody[i].RigidBodyGroupTarget, Src);
		Src += 2;

		PmxRigidbody[i].ShapeType = Src[0];
		Src++;

		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeW, &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeH, &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].ShapeD, &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].Position[0], &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Position[1], &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Position[2], &Src[8]);
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[0], &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[1], &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].Rotation[2], &Src[8]);
		if ((_FPCLASS(PmxRigidbody[i].Rotation[0]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[0] = 0.0f;
		if ((_FPCLASS(PmxRigidbody[i].Rotation[1]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[1] = 0.0f;
		if ((_FPCLASS(PmxRigidbody[i].Rotation[2]) & (_FPCLASS_SNAN | _FPCLASS_QNAN | _FPCLASS_NINF | _FPCLASS_PINF)) != 0) PmxRigidbody[i].Rotation[2] = 0.0f;
		Src += 12;

		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyWeight, &Src[0]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyPosDim, &Src[4]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyRotDim, &Src[8]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyRecoil, &Src[12]);
		READ_MEM_4BYTE(&PmxRigidbody[i].RigidBodyFriction, &Src[16]);
		Src += 20;

		PmxRigidbody[i].RigidBodyType = Src[0];
		Src++;
	}

	// �W���C���g���̐����擾
	PmxJointNum = GET_MEM_DWORD(Src);
	Src += 4;
	printf("%d : �W���C���g��\n", PmxJointNum);

	// �W���C���g�f�[�^���i�[���郁�����̈�̊m��
	if (PmxJointNum != 0)
	{
		PmxJoint = new PMX_JOINT[PmxJointNum];
		if (PmxJoint == NULL)
		{
			printf("�������m�ۂɎ��s�F�W���C���g\n");
			goto ENDLABEL;
		}

		// �W���C���g���̓ǂݍ���
		for (i = 0; (DWORD)i < PmxJointNum; i++)
		{
			MV1LoadModelToPMX_GetString(&Src, PmxJoint[i].Name, PmxInfo.EncodeType);
			if (PmxJoint[i].Name[0] == '\0')
			{
				MV1LoadModelToPMX_GetString(&Src, PmxJoint[i].Name, PmxInfo.EncodeType);
			}
			else
			{
				Src += GET_MEM_DWORD(Src) + 4;
			}

			PmxJoint[i].Type = Src[0];
			Src++;

			PmxJoint[i].RigidBodyAIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.RigidIndexSize);
			PmxJoint[i].RigidBodyBIndex = MV1LoadModelToPMX_GetInt(&Src, PmxInfo.RigidIndexSize);

			READ_MEM_4BYTE(&PmxJoint[i].Position[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].Position[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].Position[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].Rotation[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].Rotation[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].Rotation[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMin[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainPositionMax[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMin[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].ConstrainRotationMax[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringPosition[2], &Src[8]);
			Src += 12;

			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[0], &Src[0]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[1], &Src[4]);
			READ_MEM_4BYTE(&PmxJoint[i].SpringRotation[2], &Src[8]);
			Src += 12;
		}
	}




	//// �G���R�[�h������UTF16�̏ꍇ
	//if (pmx.PmxInfo.EncodeType == 0)
	//{
	//	// wprintf��UTF16��\���ł���悤�ɂ���
	//	//setlocale(LC_ALL, "Japanese");
	//	setlocale(LC_ALL, setlocale(LC_CTYPE, ""));
	//}

	//// ���f�������擾
	//for (UINT i = 0; i < MODEL_INFO_MAX; i++)
	//{
	//	fread(&pmx.ModelInfo[i].TxtSize, sizeof(pmx.ModelInfo[i].TxtSize), 1, fp);
	//	printf("%d : �e�L�X�g�o�b�t�@�̃T�C�Y\n", pmx.ModelInfo[i].TxtSize);

	//	if (pmx.ModelInfo[i].TxtSize > 0)
	//	{
	//		pmx.ModelInfo[i].Txt = new BYTE[pmx.ModelInfo[i].TxtSize];
	//		fread(&(*pmx.ModelInfo[i].Txt), sizeof(BYTE) * pmx.ModelInfo[i].TxtSize, 1, fp);

	//		wprintf(L"%s", pmx.ModelInfo[i].Txt);
	//		printf("\n");
	//	}
	//	printf("\n");
	//}
	//printf("\n");

ENDLABEL:
	SAFE_DELETE_ARRAY(SrcFirst);

	SAFE_DELETE_ARRAY(PmxJoint);
	SAFE_DELETE_ARRAY(PmxRigidbody);

	for (i = 0; (DWORD)i < PmxMorphNum; i++)
	{
		SAFE_DELETE_ARRAY(PmxMorph[i].Group);
		SAFE_DELETE_ARRAY(PmxMorph[i].Vertex);
		SAFE_DELETE_ARRAY(PmxMorph[i].Bone);
		SAFE_DELETE_ARRAY(PmxMorph[i].UV);
		SAFE_DELETE_ARRAY(PmxMorph[i].Material);
	}

	SAFE_DELETE_ARRAY(PmxMorph);
	SAFE_DELETE_ARRAY(PmxBone);
	SAFE_DELETE_ARRAY(PmxMaterial);
	SAFE_DELETE_ARRAY(PmxTexture);
	SAFE_DELETE_ARRAY(PmxVertex);
	return 0;
}
