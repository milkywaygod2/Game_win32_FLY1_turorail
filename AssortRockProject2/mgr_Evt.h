#pragma once


struct tEvt
{
	EVT_TYPE	eEvt;
	DWORD_PTR	lParam; //DWORD_PTR 플랫폼에 따라 4바이트 8바이트 자료형
	DWORD_PTR	wParam;
};

class mgr_Evt
{
	SINGLETON(mgr_Evt)

private:
	vector<tEvt> m_vecEvt;
	vector<CObj*> m_vecDlt; //삭제예정


public:
	void update();
private:
	void excute(const tEvt& _tEvt);

public:
	void addEvt(const tEvt& _tEvt)	{ m_vecEvt.push_back(_tEvt); }


};

