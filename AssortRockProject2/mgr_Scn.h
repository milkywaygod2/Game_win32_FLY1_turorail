#pragma once
//씬 == 장면 == 게임스테이지의 의미
//렌더링 : 시간동기화(*fDT)&잔상(이중버퍼링)


class CScn;

class mgr_Scn
{
	SINGLETON(mgr_Scn);

private:
	CScn* m_arrScn[(UINT)SCN_TYPE::scnEND];
	CScn* m_pCurScn;

public:
	CScn* getCurScn() { return m_pCurScn; }

private:
	void mgrScn_changeScn(SCN_TYPE _eScnType);
	friend class mgr_Evt;

public:
	void init();
	void update();
	void render(HDC _dc);


};

