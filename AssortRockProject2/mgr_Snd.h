#pragma once

// 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CRsc;
class CRsc_02SND;

class mgr_Snd
{
	SINGLETON(mgr_Snd);

private:
	LPDIRECTSOUND8	m_pDsoundMain;	// 사운드카드 대표 객체★
	CRsc_02SND*		m_pBGM;		// 현재 지정된 BGM Sound
public:
	int init(void);
	LPDIRECTSOUND8 getSoundMain() { return m_pDsoundMain; }
	void setSoundBGM(CRsc_02SND* _pBGM);

};

