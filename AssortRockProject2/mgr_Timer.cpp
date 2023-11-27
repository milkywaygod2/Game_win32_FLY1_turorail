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
	//현재카운트 (현재시각 정밀시계)
	QueryPerformanceCounter(&m_llCurCount);
	//초당카운트 (초당 천만번 카운트) vs gettickcount(1초에 1000번 카운트)
	QueryPerformanceFrequency(&m_llFrequency);
}

void mgr_Timer::update()
{
	QueryPerformanceCounter(&m_llCurCount);
	
	//프레임당 시간
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart; //quadpart부분이 실제 longlong 데이터부분, 정밀하게 float대신 double
	
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
// _DEBUG 디버그할때만 실행, 중단점 걸었을때 시간이 너무 많이 흘러가는 문제 발생

	
}

void mgr_Timer::render()
{
	//초당 프레임횟수
	//= 1. / m_dDT; 너무 출렁거림
	m_dAcc += m_dDT; //DT누적
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
