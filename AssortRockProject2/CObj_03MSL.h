#pragma once
#include "CObj.h"
class CObj_03MSL :public CObj
{
private:
	float	m_fThetaMSL;	//2��������
	Vec2	m_vDirMSL;		//���Ͱ�����

public:
	void SetDir(float _fTheta){m_fThetaMSL = _fTheta;} //ȣ���� : r=1 ������ ���ִ� 2��, 360:����=2��:1 , 1����=180/��=57.17448��
	void SetDir(Vec2 _vDir) 
	{
		m_vDirMSL = _vDir;
		m_vDirMSL.Normalize();
	}
public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	//virtual void Obj_onClls(CCmp_01Cldr* _pOther); //CCmp_01Cldr.cpp���� ��ȣ�޾ƿ�
	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pOther);
	//virtual void Obj_onCllsExit(CCmp_01Cldr* _pOther);
	
	CLONE(CObj_03MSL);

public:
	CObj_03MSL();
	virtual ~CObj_03MSL();

};

