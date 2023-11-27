#pragma once
#include "CObj.h"

struct tInfoMTR
{
	float		fSpeed;
	float		fHP;
	float		fRecogRange;
	float		fMovRange;
	float		fAttRange;
	float		fAtt;
};


class CMdl_02AI;

class CObj_02MTR :public CObj
{
private:
	tInfoMTR	m_tInfo;
	Vec2		m_vCenterPos;
	int			m_iDir; //1, -1
	CMdl_02AI*	m_pAI;
	

private:
	void setInfoMTR(const tInfoMTR& _info) { m_tInfo = _info; }
public:
	const tInfoMTR& getInfoMTR() { return m_tInfo; }

public:
	float getSpeed() { return m_tInfo.fSpeed; }
	void setSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void setCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void setMoveDistance(float _f) { m_tInfo.fMovRange = _f; }

	void MTR_setAI(CMdl_02AI* _AI);

public:
	//virtual void Obj_onClls(CCmp_01Cldr* _pOther); //CCmp_01Cldr.cpp에서 신호받아옴
	virtual void Obj_onCllsEnter(CCmp_01Cldr* _pOther);
	//virtual void Obj_onCllsExit(CCmp_01Cldr* _pOther);

public:
	virtual void update();

	CLONE(CObj_02MTR);

public:
	CObj_02MTR();
	virtual ~CObj_02MTR();

	friend class FactoryMTR;

};

