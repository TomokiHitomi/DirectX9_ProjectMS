//=============================================================================
//
// ���͏��� [sound.cpp]
// Author : GP12A295 25 �l���F��
//
//=============================================================================
#include "sound.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

// ���܂��Ȃ�
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void		SetSound(void);
long		GetVol(LPDIRECTSOUNDBUFFER8 pBuffer);
void		SetBgmVol(int no, int type);
void		UpdateSoundBgm(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECTSOUNDBUFFER8	g_pBgm[SOUND_BGM_MAX];
LPDIRECTSOUNDBUFFER8	g_pSe[SOUND_SE_MAX];
LPDIRECTSOUNDBUFFER8	g_pVoice[SOUND_VOICE_MAX];
int						g_nBgmFlag;
bool					g_bBgmBoss;
LONG					g_nVol[SOUND_BGM_MAX];


LPDWORD pdwCurrentPlayCursorBGM[SOUND_BGM_MAX];
LPDWORD pdwCurrentWriteCursorBGM[SOUND_BGM_MAX];

LPDWORD pdwCurrentPlayCursorSE[SOUND_SE_MAX];
LPDWORD pdwCurrentWriteCursorSE[SOUND_SE_MAX];

// �T�E���h�t�@�C���̃p�X�isound.h�̒ʂ��i���o�[�Ə��Ԃ����킹�邱�Ɓj
const TCHAR* c_soundFilename[] = {
	// BGM
	_T("data/SOUND/BGM/���ǂ�O���b�P���V���s�[���i���[�v�����j.wav"),		// Title BGM / �Ȓ��F�A�b�v�e���|�E�x�[�X�A�d�q�s�A�m�A�M�^�[��́A�o�b�N�O���E���h �^���o����
	_T("data/SOUND/BGM/DESTINY.wav"),							// Select BGM / �Ȓ��F�G���N�g�����o�b�N�e���|�E�G���L�M�^�[�Ƃ̃t�����g�o�b�N����
	_T("data/SOUND/BGM/Half steps.wav"),						// Game BGM / �Ȓ��F���^���E�h�X�̌������x�[�X�E�u���C�N�r�[�c�Ɠ��̃e���|�E�G���N�g���b�N�s�R�s�R
	_T("data/SOUND/BGM/Night Highway.wav"),						// Result BGM / �Ȓ��F�G���N�g���A�b�v�e���|�E�V���Z�T�C�U�[�E�`�F���W�h�{�C�X��������
	//_T("data/SOUND/BGM/���܂Ő������.wav"),					// Tutorial BGM
	// SE
	_T("data/SOUND/SE/decision26.wav"),
	_T("data/SOUND/SE/decision15.wav"),
	_T("data/SOUND/SE/punch-swing1.wav"),						// �U��SE�Ɏg������
	_T("data/SOUND/SE/bomb2.wav"),
	_T("data/SOUND/SE/nyu3.wav"),
	_T("data/SOUND/SE/robot-footstep2.wav"),
	_T("data/SOUND/SE/�z�C�b�X���E�P��.wav"),					// �I�����}�Ɏg������
	_T("data/SOUND/SE/�z�C�b�X���E�P��02.wav"),					// �I�����}�Ɏg������
	_T("data/SOUND/SE/�z�C�b�X���E�A��.wav"),					// �I�����}�Ɏg������
	_T("data/SOUND/SE/geme_start.wav"),
	_T("data/SOUND/SE/geme_select.wav"),
	_T("data/SOUND/SE/game_kettei.wav"),
	_T("data/SOUND/SE/result_select.wav"),
	_T("data/SOUND/SE/result_kettei.wav"),
	_T("data/SOUND/SE/select_bubu.wav"),
	// �ǉ�SE
	_T("data/SOUND/SE/�V�X�e�����艹_6.wav"),					// �^�C�g���J�ڎ���						SE_TITLE_KETTEI
	_T("data/SOUND/SE/�V�X�e����.wav"),							// �L�������艹							SE_CHARA_SELECT
	_T("data/SOUND/SE/�L�����Z����.wav"),						// �L�����Z����							SE_CANCEL
	_T("data/SOUND/SE/Big_Hits.wav"),							// �L�����Z���N�g���̑J�ډ�			SE_CHARA_SENNI
	_T("data/SOUND/SE/�T�v���C�Y�W����.wav"),					// �W�������i���U���g���ʁj				SE_JAN
	_T("data/SOUND/SE/���ʔ��\.wav"),							// �h�������[���i���U���g���ʁj			SE_ROLLOFDRAM
	_T("data/SOUND/SE/�Ō��E�r���^��.wav"),						// �U��������							SE_COLLIDE
	_T("data/SOUND/SE/�t�@�C�i���A�[�c.wav"),					// �K�E�Z�Q�[�W���^��					SE_SP_MAX
	_T("data/SOUND/SE/�L���[���Ɛ��ɂȂ鉹.wav"),				// �A�C�h��CD							SE_IDOL_CD
	_T("data/SOUND/SE/�D�E�ʂ����.wav"),						// �p�e�B�V�G�K�E�Z						SE_PATISSIER_SP
	_T("data/SOUND/SE/�����E�����i�C�t.wav"),					// ��҃��X����							SE_DOCTOR_THROW
	_T("data/SOUND/SE/_���̐����i�����j.wav"),				// ���h�m����							SE_FIREMAN_WATER
	_T("data/SOUND/SE/gong-played2.wav"),				// ���h�m����							SE_FIREMAN_WATER
	_T("data/SOUND/SE/down1.wav"),				// ���h�m����							SE_FIREMAN_WATER
	_T("data/SOUND/SE/defense1.wav"),				// ���h�m����							SE_FIREMAN_WATER
	_T("data/SOUND/SE/se_maoudamashii_battle16.wav"),				// ���h�m����							SE_FIREMAN_WATER
	_T("data/SOUND/SE/enemybulletreversal.wav"),				// ���h�m����							SE_FIREMAN_WATER

	// VOICE
	_T("data/SOUND/VOICE/round1.wav"),
	_T("data/SOUND/VOICE/round2.wav"),
	_T("data/SOUND/VOICE/round3.wav"),
	_T("data/SOUND/VOICE/fight.wav"),
	_T("data/SOUND/VOICE/youwin.wav")
};

// �O���[�o���ϐ�
IDirectSound8 *g_pDirectSound = NULL;	// �T�E���h�C���^�[�t�F�[�X

// �T�E���h�̏�����
// hWnd:�E�B���h�E�n���h��
HRESULT InitSound( HWND hWnd )
{
	// DirectSound�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectSoundCreate8(NULL, &g_pDirectSound, NULL)))
		return E_FAIL;
	
	// �������x���ݒ� 
	if (FAILED(g_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;
	g_nBgmFlag = SOUND_BGM_TITLE;
	g_bBgmBoss = false;

	for (int i = 0; i < SOUND_BGM_MAX; i++)
	{
		g_nVol[i] = VOLUME_MIN;
	}

	SetSound();
	return S_OK;
}

void UpdateSound(void)
{
	UpdateSoundBgm();
#ifdef _DEBUG
	PrintDebugProc("�y SOUND �z  BGM FLAG[%d]\n", g_nBgmFlag);
	for (int i = 0; i < SOUND_BGM_MAX; i++)
	{
		pdwCurrentPlayCursorBGM[i] = NULL;
		pdwCurrentWriteCursorBGM[i] = NULL;
		g_pBgm[i]->GetCurrentPosition(pdwCurrentPlayCursorBGM[i], pdwCurrentWriteCursorBGM[i]);
		//PrintDebugProc("BGM00%d[%l]  CurrentPos[%d] Write[%d]\n", i, GetVol(g_pBgm[i]), pdwCurrentPlayCursorBGM[i], pdwCurrentWriteCursorBGM[i]);
	}

	for (int i = 0; i < SOUND_SE_MAX; i++)
	{
		pdwCurrentPlayCursorSE[i] = NULL;
		pdwCurrentWriteCursorSE[i] = NULL;
		g_pSe[i]->GetCurrentPosition(pdwCurrentPlayCursorSE[i], pdwCurrentWriteCursorSE[i]);

		//PrintDebugProc(" SE00%d[%l]  CurrentPos[%d] Write[%d]\n", i, GetVol(g_pSe[i]), pdwCurrentPlayCursorSE[i], pdwCurrentWriteCursorSE[i]);
	}

	PrintDebugProc("\n");
#endif
}

// ��Еt��
void UninitSound()
{
	if( g_pDirectSound != NULL )
	{
		g_pDirectSound->Release();
		g_pDirectSound = NULL;
	}
}

// �T�E���h�̃��[�h
// no:�T�E���h�i���o�[�i�w�b�_�ɒ�`���ꂽ�񋓌^�萔�j
LPDIRECTSOUNDBUFFER8 LoadSound( int no )
{
	// MMIO = �}���`���f�B�A���o�́A�̗��B
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;						// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;						// MMIO�n���h��
	MMIOINFO mmioInfo;						// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;							// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID pBlock;				// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD  dwSize;				// �Z�J���_���o�b�t�@�̃T�C�Y

	// 1.�n���h�������ƂɃt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen((LPSTR)c_soundFilename[no], &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3.�t�@�C����͇A �t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');						// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR)		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);	// �����������Ƃɓǂݍ���
	
	if(size != formatChunk.cksize) 		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0); 

	// 4.�t�@�C����͇B �f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');					// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);	// �L�[���[�h�����ƂɌ���
	
	if(mmRes != MMSYSERR_NOERROR) 		// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 5.�f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];					// �K�v�ȑ傫���̗̈���m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);		// �f�[�^��ǂݍ���
	
	if(size != dataChunk.cksize)  		// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// 6.�Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));		// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);			// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if (FAILED(g_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// �T�E���h�o�b�t�@�����o��
	if (FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7.���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if (FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);	// �f�[�^�]��
	delete[] pData;					// ���̓ǂݍ��ݗ̈������

	// �o�b�t�@���b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Z�J���_���o�b�t�@��Ԃ��Ă悤�₭����...
	return pBuffer;
}

void UpdateSoundBgm(void)
{
	switch (g_nBgmFlag)
	{
	case SOUND_BGM_NON:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_SELECT, false);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_TITLE:
		SetBgmVol(BGM_TITLE, true);
		SetBgmVol(BGM_SELECT, false);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_SELECT:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_SELECT, true);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_GAME:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_SELECT, false);
		SetBgmVol(BGM_GAME, true);
		SetBgmVol(BGM_RESULT, false);
		break;
	case SOUND_BGM_RESULT:
		SetBgmVol(BGM_TITLE, false);
		SetBgmVol(BGM_SELECT, false);
		SetBgmVol(BGM_GAME, false);
		SetBgmVol(BGM_RESULT, true);
		break;
	}
}

void SetSoundBgm(int nBgm)
{
	g_nBgmFlag = nBgm;
}

void SetSoundBgmBoss(bool bBgm)
{
	g_bBgmBoss = bBgm;
}

// ����炷
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
// flag   :1(E_DS8_FLAG_LOOP)�Ȃ烋�[�v�Đ�
void PlaySound(  LPDIRECTSOUNDBUFFER8 pBuffer, int flag/*=0*/ ,int nOption, DWORD dwPos)
{	// ��������炷�̂ŁA�ŏ�����炵�����ꍇ��SetCurrentPosition(0)�����邱��
	if (pBuffer != NULL)
	{
		// �A���Đ��I�t�A�܂��͓r������Đ�����ꍇ
		if (nOption == SOUND_OPTION_CONTINUE_OFF || nOption == SOUND_OPTION_CURRENT)
		{
			DWORD status;
			pBuffer->GetStatus(&status);
			// �Đ����Ă��邩���m�F
			if (status & DSBSTATUS_PLAYING)
			{	// �Đ����Ă���ꍇ�͊֐��I��
				return;
			}
			if (nOption == SOUND_OPTION_CURRENT)
			{
				pBuffer->SetCurrentPosition(dwPos);
			}
		}
		else if (nOption == SOUND_OPTION_CONTINUE_ON)
		{
				pBuffer->SetCurrentPosition(dwPos);
		}
		pBuffer->Play(0, 0, flag);
	}
}

// �����~�߂�
void StopSound( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	if (pBuffer != NULL)
	{
		DWORD status;
		pBuffer->GetStatus(&status);
		if (status & DSBSTATUS_PLAYING)	// ���Ă�����
		{
			pBuffer->Stop();	// �Ӗ��I�ɂ�PabUse�ɂȂ�B
		}
	}
}

// �Đ������ǂ������ׂ�
// pBuffer:����炵�����T�E���h�f�[�^�̃Z�J���_���o�b�t�@
bool IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer )
{
	DWORD status;

	pBuffer->GetStatus(&status);
	if( status & DSBSTATUS_PLAYING )
	{
		return true;
	}
	return false;
}

HRESULT SetVol( LPDIRECTSOUNDBUFFER8 pBuffer, LONG lVol)
{
	DWORD status;
	pBuffer->SetVolume(lVol);
	return DS_OK;
}

long GetVol(LPDIRECTSOUNDBUFFER8 pBuffer)
{
	DWORD status;
	long lVol;
	pBuffer->GetStatus(&status);
	pBuffer->GetVolume(&lVol);
	return lVol;
}

//=============================================================================
// �T�E���h�ݒ�֐�
//=============================================================================
void SetSound(void)
{
	// BGM������Ȃ��悤�Ƀ��[�h�ƕ�����
	for (int i = BGM_00; i < SOUND_BGM_MAX; i++)
	{
		// �eBGM���[�h
		g_pBgm[i] = LoadSound(i);
	}
	for (int i = BGM_00; i < SOUND_BGM_MAX; i++)
	{
		// �eBGM�{�����[���Z�b�g
		PlaySound(g_pBgm[i], E_DS8_FLAG_LOOP, SOUND_OPTION_BGM, 0);
		SetVol(g_pBgm[i], VOLUME_MIN);
	}

	for (int i = 0; i < SOUND_SE_MAX; i++)
	{	
		// �eSE���[�h
		g_pSe[i] = LoadSound(i + SE_00);
		//// �eSE�{�����[���Z�b�g
		//if (i != SE_DRAMROLL)
		//{
		//	SetVol(g_pSe[i], (LONG)-5000);
		//}
	}

	//SetVol(g_pSe[11], SE_11_VOLUME_SE);

	for (int i = 0; i < SOUND_VOICE_MAX; i++)
	{
		// �eSE���[�h
		g_pVoice[i] = LoadSound(i + VOICE_00);
	}
}

//=============================================================================
// SE�Đ��֐�
//=============================================================================
void SetSe(int nSe, int nFlag, int nOption, DWORD dwPos)
{
	PlaySound(g_pSe[nSe], nFlag, nOption, dwPos);
}

//=============================================================================
// SE��~�֐�
//=============================================================================
void EndSe(int nSe)
{
	StopSound(g_pSe[nSe]);
}

//=============================================================================
// Voice�Đ��֐�
//=============================================================================
void SetVoice(int nVoice, int nFlag, int nOption, DWORD dwPos)
{
	PlaySound(g_pVoice[nVoice], nFlag, nOption, dwPos);
}

//=============================================================================
// BGM�{�����[���R���g���[��
//=============================================================================
void SetBgmVol(int no, int type)
{
	// type 0=�t�F�[�h�A�E�g 1=�t�F�[�h�C��
	if (type == VOLUME_FADE_OUT)
	{
		if (g_nVol[no] > VOLUME_MIN)
		{
			g_nVol[no] -= VOLUME_CONTROL_DOWN;
			if (g_nVol[no] < VOLUME_MIN)
			{
				g_nVol[no] = VOLUME_MIN;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
	else if (type == VOLUME_FADE_IN)
	{
		if (g_nVol[no] < VOLUME_MAX)
		{
			g_nVol[no] += VOLUME_CONTROL_UP;
			if (g_nVol[no] > VOLUME_MAX)
			{
				g_nVol[no] = VOLUME_MAX;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
	else if (type == VOLUME_FADE_HALF)
	{
		if (g_nVol[no] > VOLUME_HALF)
		{
			g_nVol[no] -= VOLUME_CONTROL_DOWN;
			if (g_nVol[no] < VOLUME_HALF)
			{
				g_nVol[no] = VOLUME_HALF;
			}
			SetVol(g_pBgm[no], g_nVol[no]);
		}
	}
}