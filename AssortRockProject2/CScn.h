#pragma once

class CObj; // 씬내용상 오브젝트변경시 순환참조를 막기위해, 헤더가 헤더를 참조하는 걸 막기위해, 언급해주고 넘어가는 스킬, 타입은 없으므로 포인터로밖에 사용안됨

class CScn
{
private: 
	wstring			m_objName; //Scn이름
	vector<CObj*>	m_arrObj[(UINT)OBJ_TYPE::objEND]; //Object가상함수위한 밑작업 ㅋㅋ

	UINT			m_iTileX;
	UINT			m_iTileY;

	CObj*			m_pPlr; //편의성코딩, 반엔진

public://자식 바로 접근은 지양해야 private의 취지를 살리려면 별도함수를 protected 그래야 디버깅이 편함(클래스외부호출이 없는경우)
	void Scn_addObj(CObj* _pObj, OBJ_TYPE _eObjType){m_arrObj[(UINT)_eObjType].push_back(_pObj);} //함수탬플릿(함수x) 타입넣어주는게 정석, 생략가능
	void Scn_registerPLR(CObj* _pPlr) { m_pPlr = _pPlr; } //씬에 놓는 건 편의성 반엔진
	CObj* Scn_getPlr() { return m_pPlr; }
	
	void Scn_clearObj(OBJ_TYPE _eObjType) { Freq_clearVec<CObj*> (m_arrObj[(UINT)_eObjType]); } 
	void Scn_clearAll();

	void Scn_createTile(UINT _iXcount, UINT _iYcount);
	UINT getTileX() { return m_iTileX; }
	UINT getTileY() { return m_iTileY; }
	
	void loadTile(const wstring& _strRltvPath);

public:
	const vector<CObj*>& Scn_getObjGroup(OBJ_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	vector<CObj*>& Scn_getObjGroup_UI() { return m_arrObj[(UINT)OBJ_TYPE::UI]; } //UI용, 수정필요 NO-const

public:
	const wstring& GetName() { return m_objName; }//Scn이름 확인
	void SetName(const wstring& _strName) { m_objName = _strName; }//Scn이름 조작


	virtual void Enter() = 0;	//Scn입장, 순수가상함수
	virtual void Exit() = 0;	//Scn탈출

	virtual void Scn_start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	void renderTL(HDC _dc);
	
public:
	CScn();
	virtual ~CScn(); //파생상속용 클래스에 꼭해줘야하는 작업

};

