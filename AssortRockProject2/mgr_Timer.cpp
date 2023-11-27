#include "pch.h"
#include "mgr_Timer.h"
#include "CCore.h"
#include <wchar.h>

mgr_Timer::mgr_Timer()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{}
mgr_Timer::~mgr_Timer(){}

void mgr_Timer::init()
{
	//����ī��Ʈ (����ð� ���нð�)
	QueryPerformanceCounter(&m_llCurCount);
	//�ʴ�ī��Ʈ (�ʴ� õ���� ī��Ʈ) vs gettickcount(1�ʿ� 1000�� ī��Ʈ)
	QueryPerformanceFrequency(&m_llFrequency);
}

void mgr_Timer::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	//�����Ӵ� �ð�
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; //quadpart�κ��� ���� longlong �����ͺκ�, �����ϰ� float��� double
	
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
// _DEBUG ������Ҷ��� ����, �ߴ��� �ɾ����� �ð��� �ʹ� ���� �귯���� ���� �߻�

	
}

void mgr_Timer::render()
{
	//�ʴ� ������Ƚ��
	//= 1. / m_dDT; �ʹ� �ⷷ�Ÿ�
	m_dAcc += m_dDT; //DT����
	++m_iCallCount;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, (float)m_dDT);
		SetWindowText(CCore::GetInst()->getMainHwnd(), szBuffer);
	}

}
