#include "pch.h"
#include "AI_state.h"

AI_state::AI_state(MTR_STATE _eState)
	: m_eState(_eState)
{
}

AI_state::~AI_state()
{
}


CObj_02MTR* AI_state::getAI_owner()
{
	
	return m_pAI->getOwner();
}
