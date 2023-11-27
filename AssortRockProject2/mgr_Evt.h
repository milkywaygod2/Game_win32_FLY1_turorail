#pragma once


struct tEvt
{
	EVT_TYPE	eEvt;
	DWORD_PTR	lParam; //DWORD_PTR �÷����� ���� 4����Ʈ 8����Ʈ �ڷ���
	DWORD_PTR	wParam;
};

class mgr_Evt
{
	SINGLETON(mgr_Evt)

private:
	vector<tEvt> m_vecEvt;
	vector<CObj*> m_vecDlt; //��������


public:
	void update();
private:
	void excute(const tEvt& _tEvt);

public:
	void addEvt(const tEvt& _tEvt)	{ m_vecEvt.push_back(_tEvt); }


};

