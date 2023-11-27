#pragma once
class mgr_Timer
{
	SINGLETON(mgr_Timer);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			//프레임당 시간값, 델타타임
	double			m_dAcc;			//1초 체크를 위한 누적시간
	UINT			m_iCallCount;	//함수 호출횟수 체크
	UINT			m_iFPS;			//초당 호출횟수

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

