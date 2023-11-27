#pragma once
#include "CObj.h"
class CObj_03MSL :public CObj
{
private:
	float	m_fThetaMSL;	//2차원방향
	Vec2	m_vDirMSL;		//벡터각도법

public:
	void SetDir(float _fTheta){m_fThetaMSL = _fTheta;} //호도법 : r=1 원에서 원주는 2π, 360:라디안=2π:1 , 1라디안=180/π=57.17448˚
	void SetDir(Vec2 _vDir) 
	{
		m_vDirMSL = _vDir;
		m_vDirMSL.Normalize();
	}
public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	//virtual void Obj_onClls(CCmp_01Cldr* _pOther); //CCmp_01Cldr.cpp에서 신호받아옴
	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pOther);
	//virtual void Obj_onCllsExit(CCmp_01Cldr* _pOther);
	
	CLONE(CObj_03MSL);

public:
	CObj_03MSL();
	virtual ~CObj_03MSL();

};

