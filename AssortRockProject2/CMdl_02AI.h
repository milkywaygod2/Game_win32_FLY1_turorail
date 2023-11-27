#pragma once
class CObj_02MTR;
class AI_state;

 class CMdl_02AI
{
private:
	map<MTR_STATE, AI_state*>	m_mapState;
	AI_state*					m_pCurState;
	CObj_02MTR*					m_pOwner;

public:
	void update();


public:
	void addState(AI_state* _pState);
	AI_state* getState(MTR_STATE _eState);
	void setCurState(MTR_STATE _eState);

	void changeState(MTR_STATE _eNextState);

	CObj_02MTR* getOwner() { return m_pOwner; }

public:
	CMdl_02AI();
	~CMdl_02AI();
	friend class CObj_02MTR;
};

