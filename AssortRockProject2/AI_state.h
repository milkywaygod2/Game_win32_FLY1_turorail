#pragma once
class CMdl_02AI;

class AI_state
{
private:
	CMdl_02AI*	m_pAI;
	MTR_STATE	m_eState;

public:
	CMdl_02AI* getAI() { return m_pAI; }
	MTR_STATE getAI_state() { return m_eState; }
	CObj_02MTR* getAI_owner();

public:
	virtual void Enter() = 0;
	virtual void update() = 0;
	
	virtual void Exit() = 0;


public:
	AI_state(MTR_STATE _eState);
	virtual ~AI_state();

	friend class CMdl_02AI;
};

