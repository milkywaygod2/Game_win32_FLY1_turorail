#pragma once

class CCmp_01Cldr;
class CCmp_02Amtr;
class CCmp_03RgdB;
class CCmp_04Grbt;


class CObj
{

private: 
	wstring			m_objName;
	Vec2			m_vPos;
	Vec2			m_vScale;

	CCmp_01Cldr*	m_pCldr;
	CCmp_02Amtr*	m_pAmtr;
	CCmp_03RgdB*	m_pRgdB;
	CCmp_04Grbt*	m_pGrbt;

	bool			m_bAlive;

protected://�ڽ� �ٷ� ������ �����ؾ� private�� ������ �츮���� �����Լ��� protected �׷��� ������� ����
	//void Scn_addObj(CObj* _pObj, OBJ_TYPE _eType); CScn.h����


public:
	//�ڽ��� ȣ������ �����ϴ� ����
	Vec2 Obj_getPos() { return m_vPos; }
	void Obj_setPos(Vec2 _vPos) { m_vPos = _vPos; }

	Vec2 Obj_getScale() { return m_vScale; }
	void Obj_setScale(Vec2 _vScale) { m_vScale = _vScale; }

	void Obj_setName(const wstring& _strName) { m_objName = _strName; }
	const wstring& Obj_getName() { return m_objName; }

	void Obj_createCldr();
	void Obj_createAmtr();
	void Obj_createRgdB();
	void Obj_createGrbt();


	CCmp_01Cldr* Obj_getCldr() { return m_pCldr; }
	CCmp_02Amtr* Obj_getAmtr() { return m_pAmtr; }
	CCmp_03RgdB* Obj_getRgdB() { return m_pRgdB; }
	CCmp_04Grbt* Obj_getGrbt() { return m_pGrbt; }


	void Obj_renderCmp(HDC _dc); //�ݸ��� ���� ������ ���� �� ����

	bool Obj_isDlt() { return !m_bAlive; }

private:
	void Obj_setDlt() { m_bAlive = false; }
	friend class mgr_Evt;

public:
	virtual void Obj_onClls(CCmp_01Cldr* _pOther) {} //CCmp_01Cldr.cpp���� ��ȣ�޾ƿ�
	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pOther) {}
	virtual void Obj_onCllsExit(CCmp_01Cldr* _pOther) {}

public:
	virtual void Obj_start() {}; //Scn�����ϱ� ������ ȣ��, �����ڶ� ��� ������ �ǹ��ִ� ���������
	virtual void update() = 0;
	virtual void finalupdate(); 
	virtual void render(HDC _dc);

	virtual CObj* clone() = 0;
	

public:
	CObj();
	CObj(const CObj& _origin);

	virtual ~CObj(); //�Ļ���ӿ� Ŭ������ ��������ϴ� �۾�
};

