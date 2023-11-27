#include "pch.h"
#include "mgr_Snd.h"

mgr_Snd::mgr_Snd()
	: m_pDsoundMain(nullptr)
	, m_pBGM(nullptr)
{
}

mgr_Snd::~mgr_Snd()
{
}

int mgr_Snd::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pDsoundMain, NULL)))
	{
		MessageBox(NULL, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정.
	HWND hWnd = CCore::GetInst()->getMainHwnd();
	if (FAILED(m_pDsoundMain->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag값 정리
	{
		MessageBox(NULL, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void mgr_Snd::setSoundBGM(CRsc_02SND* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->stopSound(true);

	m_pBGM = _pSound;
}