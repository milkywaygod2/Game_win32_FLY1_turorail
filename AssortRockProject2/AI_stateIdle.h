#pragma once
#include "AI_state.h"
class AI_stateIdle :
    public AI_state
{
private:


public:
    float fDir = 1.f;
    float fDist;

public:
    virtual void Enter();
    virtual void update();
    virtual void Exit();

public:
    AI_stateIdle();
    ~AI_stateIdle();

};

