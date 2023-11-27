#include "pch.h"
#include "CObj_02MTR.h"


CObj_02MTR::CObj_02MTR()
	:	m_vCenterPos(Vec2(0.f,0.f))
	,	m_tInfo{}
	//,	m_fSpeed(200.f)
	//,	m_fMaxDistance(100.f)
	,	m_iDir(1)
	//,	m_iHP(5)
{
	Obj_createCldr();
	Obj_getCldr()->Cldr_setScale(Vec2(45.f, 45.f));
}
CObj_02MTR::~CObj_02MTR(){
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CObj_02MTR::update()
{
	if(nullptr!=m_pAI)
	m_pAI->update();
}

void CObj_02MTR::MTR_setAI(CMdl_02AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CObj_02MTR::Obj_onCllsEnter(CCmp_01Cldr* _pOther)
{
	CObj* pOtherObj = _pOther->Cldr_getOtherObj();
	
	if (pOtherObj->Obj_getName() == L"MSL_PLR")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
		{
			Evt_deleteObj(this, OBJ_TYPE::MTR);
		}
	}
	
	//데미지?
	//이팩트?
}
