#pragma once
#include "mgr_Snd.h"

class CRsc_02SND :public CRsc
{
private:
	LPDIRECTSOUNDBUFFER		m_pDsoundBuff;
	DSBUFFERDESC			m_tDsoundBuffInfo;
	int						m_iDsoundVolume;

public:
	int loadSound(const wstring& _strPath);

	// 일반 재생
	void playSound(bool _bLoop = false);

	// BGM 재생
	void playSoundBGM(bool _bLoop = false);

	void stopSound(bool _bReset = false);

	// 볼륨 범위 (0 ~ 100)
	void setSoundVolume(float _fVolume);

	// 음악파일 위치 조정
	void setSoundPercent(float _fPosition); // 0 ~ 100 사이

private:
	bool loadSound_wav(const wstring& _strPath);
	int getSoundDecibel(float _fVolume);

public:
	CRsc_02SND();
	virtual ~CRsc_02SND();

};

