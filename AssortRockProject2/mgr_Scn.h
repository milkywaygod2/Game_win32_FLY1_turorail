#pragma once
//�� == ��� == ���ӽ��������� �ǹ�
//������ : �ð�����ȭ(*fDT)&�ܻ�(���߹��۸�)


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

