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
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ����̽� �������� ����.
	HWND hWnd = CCore::GetInst()->getMainHwnd();
	if (FAILED(m_pDsoundMain->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
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