#pragma once
#include "pch.h"
#include "CObj_05UI.h"

class UI_Panel :public CObj_05UI
{
private:
    Vec2 m_vDragStart;

public:
    CLONE(UI_Panel);

    virtual void update();
    virtual void render(HDC _dc);

    virtual void cursorOn();
    virtual void cursorLbtnDown();
    virtual void cursorLbtnUp();


public:
    UI_Panel();
    ~UI_Panel();
};

