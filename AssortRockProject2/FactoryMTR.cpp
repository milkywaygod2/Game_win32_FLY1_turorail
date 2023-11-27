#include "pch.h"
#include "FactoryMTR.h"

CObj_02MTR* FactoryMTR::createMTR(MTR_TYPE _eType, Vec2 _vPos)
{
	CObj_02MTR* pMtr = nullptr;

	switch (_eType)
	{
	case MTR_TYPE::NORMAL:
	{	pMtr = new CObj_02MTR;
		pMtr->Obj_setPos(_vPos);

		tInfoMTR info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 250.f;
		info.fHP = 5.f;
		info.fSpeed = 150.f;
		info.fMovRange = 100.f;
		pMtr->setInfoMTR(info);

		pMtr->Obj_createRgdB();
		pMtr->Obj_getRgdB()->setMass(0.5f);

		CMdl_02AI* pAI = new CMdl_02AI;
		pAI->addState(new AI_stateIdle);
		pAI->addState(new AI_stateTrace);
		pAI->setCurState(MTR_STATE::IDLE);


		pMtr->MTR_setAI(pAI);
	}

		break;

	case MTR_TYPE::RANGE:
		break;

	}
	assert(pMtr);

	return pMtr;
}
