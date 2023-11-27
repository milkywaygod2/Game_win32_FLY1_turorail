#pragma once
class CCmp_01Cldr
{
friend class CObj;

private:
	static UINT g_iNextID;

	CObj*			m_pOwner; //인자만 만들어두고 값은 Obj생성자가 매칭해줌

	Vec2			m_vOffsetPos; //콜리전의 포지션은 보통 바닥쪽에 둠
	Vec2			m_vCldrPos; //오브젝트위치 + 오프셋
	Vec2			m_vScale;	//충돌체크기
	
	UINT			m_iID;		//고유ID
	int				m_iOnCdlr;	//여러대 충돌 상황고려 bool보다 int로 관리

	bool			m_bActive;	//충돌체 활성화여부

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void Cldr_setScale(Vec2 _vScale) { m_vScale = _vScale; }
	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 Cldr_getScale() { return m_vScale; }

	UINT Cldr_getID() { return m_iID; }
	Vec2 Cldr_getPos_F() { return m_vCldrPos; }

	CObj* Cldr_getOtherObj() { return m_pOwner; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	void Cldr_onClls(CCmp_01Cldr* _pOther); //충돌중 호출함수
	void Cldr_onCllsEnter(CCmp_01Cldr* _pOther);
	void Cldr_onCllsExit(CCmp_01Cldr* _pOther);
	void Cldr_nonClls(CCmp_01Cldr* _pOther);
	CCmp_01Cldr& operator = (CCmp_01Cldr& _origin) = delete; //대입연산기능 못하게

public:
	CCmp_01Cldr();
	CCmp_01Cldr(const CCmp_01Cldr& _origin); //복사생성자로 Cldr가 복사되더라도 고유ID 갖도록
	~CCmp_01Cldr();

};

