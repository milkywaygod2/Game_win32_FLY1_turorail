#pragma once

// �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CRsc;
class CRsc_02SND;

class mgr_Snd
{
	SINGLETON(mgr_Snd);

private:
	LPDIRECTSOUND8	m_pDsoundMain;	// ����ī�� ��ǥ ��ü��
	CRsc_02SND*		m_pBGM;		// ���� ������ BGM Sound
public:
	int init(void);
	LPDIRECTSOUND8 getSoundMain() { return m_pDsoundMain; }
	void setSoundBGM(CRsc_02SND* _pBGM);

};

