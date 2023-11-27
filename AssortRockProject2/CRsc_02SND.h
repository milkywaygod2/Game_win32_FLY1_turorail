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

	// �Ϲ� ���
	void playSound(bool _bLoop = false);

	// BGM ���
	void playSoundBGM(bool _bLoop = false);

	void stopSound(bool _bReset = false);

	// ���� ���� (0 ~ 100)
	void setSoundVolume(float _fVolume);

	// �������� ��ġ ����
	void setSoundPercent(float _fPosition); // 0 ~ 100 ����

private:
	bool loadSound_wav(const wstring& _strPath);
	int getSoundDecibel(float _fVolume);

public:
	CRsc_02SND();
	virtual ~CRsc_02SND();

};

