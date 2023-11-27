#pragma once
class CCmp_01Cldr;

union uCldr_ID //유니언, 여러 자료형 들어가 있을때 가장 큰거 기준으로 1번만 메모리할당
{	struct	{ UINT iLeftID;	UINT iRightID;	};
	ULONGLONG iLeftRightID;
};

class mgr_Clls
{
	SINGLETON(mgr_Clls)

private:
	map<ULONGLONG, bool>	m_mapCllsInfo;						//이전 프레임 충돌 매트릭스 (ObjCldrID,isClls())
	UINT					m_arrCheck[(UINT)OBJ_TYPE::objEND]; //현재 프레임 충돌 매트릭스

public:
	void checkObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	void update();
	void reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJ_TYPE::objEND); }  //memset지정주소를 byte단위로 세팅

private:
	void updateCllsObj(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	bool isClls(CCmp_01Cldr* _pLeftCldr, CCmp_01Cldr* _pRightCldr);
};

