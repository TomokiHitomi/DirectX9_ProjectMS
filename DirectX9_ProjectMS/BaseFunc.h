#include "main.h"
#include	<float.h>

#define GET_MEM_BYTE( ptr )						( ( ( BYTE * )ptr )[ 0 ] )
#define GET_MEM_WORD( ptr )						( ( ( BYTE * )ptr )[ 0 ] | ( ( ( BYTE * )ptr )[ 1 ] << 8 ) )
#define GET_MEM_DWORD( ptr )					( ( ( BYTE * )ptr )[ 0 ] | ( ( ( BYTE * )ptr )[ 1 ] << 8 ) | ( ( ( BYTE * )ptr )[ 2 ] << 16 ) | ( ( ( BYTE * )ptr )[ 3 ] << 24 ) )

#define GET_MEM_SIGNED_BYTE( ptr )				( ( signed char  )GET_MEM_BYTE( ptr ) )
#define GET_MEM_SIGNED_WORD( ptr )				( ( signed short )GET_MEM_WORD( ptr ) )
#define GET_MEM_SIGNED_DWORD( ptr )				( ( signed int   )GET_MEM_DWORD( ptr ) )

#define READ_MEM_1BYTE( dst_ptr, src_ptr )		( ( BYTE * )( dst_ptr ) )[ 0 ] = ( ( BYTE * )( src_ptr ) )[ 0 ] ;

#define READ_MEM_2BYTE( dst_ptr, src_ptr )		( ( BYTE * )( dst_ptr ) )[ 0 ] = ( ( BYTE * )( src_ptr ) )[ 0 ] ;\
												( ( BYTE * )( dst_ptr ) )[ 1 ] = ( ( BYTE * )( src_ptr ) )[ 1 ] ;

#define READ_MEM_4BYTE( dst_ptr, src_ptr )		( ( BYTE * )( dst_ptr ) )[ 0 ] = ( ( BYTE * )( src_ptr ) )[ 0 ] ;\
												( ( BYTE * )( dst_ptr ) )[ 1 ] = ( ( BYTE * )( src_ptr ) )[ 1 ] ;\
												( ( BYTE * )( dst_ptr ) )[ 2 ] = ( ( BYTE * )( src_ptr ) )[ 2 ] ;\
												( ( BYTE * )( dst_ptr ) )[ 3 ] = ( ( BYTE * )( src_ptr ) )[ 3 ] ;

// FLOAT4ŒÂƒf[ƒ^Œ^
typedef struct tagFLOAT4
{
	float					x, y, z, w;
} FLOAT4, *LPFLOAT4;


extern int _FPCLASS(double x)
{
	return _fpclass(x);
}

extern void _MEMSET(void *Memory, unsigned char Char, size_t Size)
{
	if (Size == 0) return;

#ifndef DX_NON_INLINE_ASM
	DWORD s = (DWORD)Size;
	DWORD DwordChar = (DWORD)Char;
	__asm
	{
		CLD
		MOV EAX, DwordChar
		MOV ECX, s
		MOV EDI, Memory
		REP STOSB
	}
#else
	do
	{
		*((BYTE *)Memory) = Char;
		Memory = (BYTE *)Memory + 1;
	} while (--Size != 0);
#endif
}

extern void _MEMSETD(void *Memory, unsigned int Data, int Num)
{
	if (Num == 0) return;

#ifndef DX_NON_INLINE_ASM
	DWORD s = (DWORD)Num;
	__asm
	{
		CLD
		MOV EAX, Data
		MOV ECX, s
		MOV EDI, Memory
		REP STOSD
	}
#else
	do
	{
		*((DWORD *)Memory) = Data;
		Memory = (BYTE *)Memory + 4;
	} while (--Num != 0);
#endif
}


extern int _MEMCMP(const void *Buffer1, const void *Buffer2, int Size)
{
	if (Size == 0) return 0;

#ifndef DX_NON_INLINE_ASM
	DWORD s1 = (DWORD)Buffer1;
	DWORD s2 = (DWORD)Buffer2;
	DWORD s = (DWORD)Size;
	DWORD res;
	__asm
	{
		CLD
		XOR EAX, EAX
		MOV ESI, s1
		MOV EDI, s2
		MOV ECX, s
		REPZ CMPSB
		MOV res, EAX
		JE END
		MOV EAX, 1
		MOV res, EAX
		END :
	}
	return (int)res;
#else
	do
	{
		if (*((BYTE *)Buffer1) > *((BYTE *)Buffer2)) return -1;
		if (*((BYTE *)Buffer1) < *((BYTE *)Buffer2)) return  1;
		Buffer1 = (BYTE *)Buffer1 + 1;
		Buffer2 = (BYTE *)Buffer2 + 1;
	} while (--Size != 0);
	return 0;
#endif
}


extern void _MEMCPY(void *Buffer1, const void *Buffer2, size_t Size)
{
	if (Size == 0) return;

#ifndef DX_NON_INLINE_ASM
	DWORD s1 = (DWORD)Buffer1;
	DWORD s2 = (DWORD)Buffer2;
	DWORD s = (DWORD)Size;
	__asm
	{
		CLD
		MOV ESI, s2
		MOV EDI, s1
		MOV ECX, s
		REP MOVSB
	}
#else
	do
	{
		*((BYTE *)Buffer1) = *((BYTE *)Buffer2);
		Buffer1 = (BYTE *)Buffer1 + 1;
		Buffer2 = (BYTE *)Buffer2 + 1;
	} while (--Size != 0);
#endif
}
