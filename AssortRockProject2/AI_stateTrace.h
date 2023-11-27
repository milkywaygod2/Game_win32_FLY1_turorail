#pragma once
#include "AI_state.h"
class AI_stateTrace :
    public AI_state
{
private:


public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();

public:
    AI_stateTrace();
    ~AI_stateTrace();

};

