#pragma once
class mgr_Timer
{
	SINGLETON(mgr_Timer);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	double			m_dDT;			//�����Ӵ� �ð���, ��ŸŸ��
	double			m_dAcc;			//1�� üũ�� ���� �����ð�
	UINT			m_iCallCount;	//�Լ� ȣ��Ƚ�� üũ
	UINT			m_iFPS;			//�ʴ� ȣ��Ƚ��

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

