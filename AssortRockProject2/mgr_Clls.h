#pragma once
class CCmp_01Cldr;

union uCldr_ID //���Ͼ�, ���� �ڷ��� �� ������ ���� ū�� �������� 1���� �޸��Ҵ�
{	struct	{ UINT iLeftID;	UINT iRightID;	};
	ULONGLONG iLeftRightID;
};

class mgr_Clls
{
	SINGLETON(mgr_Clls)

private:
	map<ULONGLONG, bool>	m_mapCllsInfo;						//���� ������ �浹 ��Ʈ���� (ObjCldrID,isClls())
	UINT					m_arrCheck[(UINT)OBJ_TYPE::objEND]; //���� ������ �浹 ��Ʈ����

public:
	void checkObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	void update();
	void reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJ_TYPE::objEND); }  //memset�����ּҸ� byte������ ����

private:
	void updateCllsObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	bool isClls(CCmp_01Cldr* _pLeftCldr, CCmp_01Cldr* _pRightCldr);
};

