#include "pch.h"
#include "AI_stateIdle.h"


AI_stateIdle::AI_stateIdle()
	: AI_state(MTR_STATE::IDLE)
{
}

AI_stateIdle::~AI_stateIdle()
{
}

void AI_stateIdle::Enter()
{
}

void AI_stateIdle::update()
{
	//플레이어 위치체크
	CObj_01PLR* pPlr = (CObj_01PLR*)mgr_Scn::GetInst()->getCurScn()->Scn_getPlr();
	Vec2 vPlrPos = pPlr->Obj_getPos();

	//조건부 추적전환
	CObj_02MTR* pMtr = getAI_owner();
	Vec2 vMtrPos = pMtr->Obj_getPos();

	float fLen = (vPlrPos - vMtrPos).Length();
	if (fLen < pMtr->getInfoMTR().fRecogRange)
	{
		Evt_changeAI_state(getAI(), MTR_STATE::TRACE);
	}

	//아이들 상태에서 순찰
	float a = pMtr->getInfoMTR().fMovRange;
	fDist += fDT * pMtr->getInfoMTR().fSpeed * fDir;
	if (pMtr->getInfoMTR().fMovRange < fDist || -pMtr->getInfoMTR().fMovRange > fDist){
		fDir *= -1.f;
		fDist = 0.f;
	}
	vMtrPos.x += fDT * pMtr->getInfoMTR().fSpeed * fDir;
	pMtr->Obj_setPos(vMtrPos);
}

void AI_stateIdle::Exit()
{
}