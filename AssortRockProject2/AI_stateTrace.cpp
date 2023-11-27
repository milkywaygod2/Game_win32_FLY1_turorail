#include "pch.h"
#include "AI_stateTrace.h"

AI_stateTrace::AI_stateTrace()
	: AI_state(MTR_STATE::TRACE)
{
}

AI_stateTrace::~AI_stateTrace()
{
}


void AI_stateTrace::Enter()
{
}

void AI_stateTrace::update()
{
	//타겟을 쫒아간다.
	CObj_01PLR* pPlr = (CObj_01PLR*)mgr_Scn::GetInst()->getCurScn()->Scn_getPlr();
	Vec2 vPlrPos = pPlr->Obj_getPos();
	
	CObj_02MTR* pMtr = getAI_owner();
	Vec2 vMtrPos = pMtr->Obj_getPos();

	float fLen = (vPlrPos - vMtrPos).Length();
	if (fLen >= pMtr->getInfoMTR().fRecogRange)
	{
		Evt_changeAI_state(getAI(), MTR_STATE::IDLE);
		return;
	}

	Vec2 vMtrDir = vPlrPos - vMtrPos;
	vMtrDir.Normalize();
	vMtrPos += vMtrDir * getAI_owner()->getInfoMTR().fSpeed * fDT;
	

	getAI_owner()->Obj_setPos(vMtrPos);
}

void AI_stateTrace::Exit()
{
}
