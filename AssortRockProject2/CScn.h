#pragma once

class CObj; // ������� ������Ʈ����� ��ȯ������ ��������, ����� ����� �����ϴ� �� ��������, ������ְ� �Ѿ�� ��ų, Ÿ���� �����Ƿ� �����ͷιۿ� ���ȵ�

class CScn
{
private: 
	wstring			m_objName; //Scn�̸�
	vector<CObj*>	m_arrObj[(UINT)OBJ_TYPE::objEND]; //Object�����Լ����� ���۾� ����

	UINT			m_iTileX;
	UINT			m_iTileY;

	CObj*			m_pPlr; //���Ǽ��ڵ�, �ݿ���

public://�ڽ� �ٷ� ������ �����ؾ� private�� ������ �츮���� �����Լ��� protected �׷��� ������� ����(Ŭ�����ܺ�ȣ���� ���°��)
	void Scn_addObj(CObj* _pObj, OBJ_TYPE _eObjType){m_arrObj[(UINT)_eObjType].push_back(_pObj);} //�Լ����ø�(�Լ�x) Ÿ�Գ־��ִ°� ����, ��������
	void Scn_registerPLR(CObj* _pPlr) { m_pPlr = _pPlr; } //���� ���� �� ���Ǽ� �ݿ���
	CObj* Scn_getPlr() { return m_pPlr; }
	
	void Scn_clearObj(OBJ_TYPE _eObjType) { Freq_clearVec<CObj*> (m_arrObj[(UINT)_eObjType]); } 
	void Scn_clearAll();

	void Scn_createTile(UINT _iXcount, UINT _iYcount);
	UINT getTileX() { return m_iTileX; }
	UINT getTileY() { return m_iTileY; }
	
	void loadTile(const wstring& _strRltvPath);

public:
	const vector<CObj*>& Scn_getObjGroup(OBJ_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	vector<CObj*>& Scn_getObjGroup_UI() { return m_arrObj[(UINT)OBJ_TYPE::UI]; } //UI��, �����ʿ� NO-const

public:
	const wstring& GetName() { return m_objName; }//Scn�̸� Ȯ��
	void SetName(const wstring& _strName) { m_objName = _strName; }//Scn�̸� ����


	virtual void Enter() = 0;	//Scn����, ���������Լ�
	virtual void Exit() = 0;	//ScnŻ��

	virtual void Scn_start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	void renderTL(HDC _dc);
	
public:
	CScn();
	virtual ~CScn(); //�Ļ���ӿ� Ŭ������ ��������ϴ� �۾�

};

