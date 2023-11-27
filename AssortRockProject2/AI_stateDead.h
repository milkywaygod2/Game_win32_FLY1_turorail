#pragma once
#include "AI_state.h"
class AI_stateDead :
    public AI_state
{
private:

public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();

public:

};

