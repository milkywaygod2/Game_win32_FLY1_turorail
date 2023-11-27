#include "pch.h"
#include "CMdl_02AI.h"


CMdl_02AI::CMdl_02AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

CMdl_02AI::~CMdl_02AI()
{
	Freq_clearMap(m_mapState);
}

void CMdl_02AI::update()
{

	m_pCurState->update(); //오버라이드, CMdl_02AI::update() 아님
}

void CMdl_02AI::addState(AI_state* _pState)
{
	AI_state* pState = getState(_pState->getAI_state());
	assert(!pState);

	//make_pair(상태명칭,vitual구현부)
	m_mapState.insert(make_pair(_pState->getAI_state(), _pState));
	_pState->m_pAI = this; //주소부여
}

AI_state* CMdl_02AI::getState(MTR_STATE _eState)
{
	map<MTR_STATE, AI_state*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void CMdl_02AI::setCurState(MTR_STATE _eState)
{
	m_pCurState = getState(_eState);
	assert(m_pCurState);
}

void CMdl_02AI::changeState(MTR_STATE _eNextState)
{
	AI_state* pNextState = getState(_eNextState);
	assert(m_pCurState != pNextState);

	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}
