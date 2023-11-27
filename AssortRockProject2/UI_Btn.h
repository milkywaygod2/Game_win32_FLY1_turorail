#pragma once
#include "pch.h"
#include "CObj_05UI.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
typedef void(CScn::* SCN_FUNC)(void); //공통조상만들어두면 모든 객체 커버가능, '맴버함수'포인터
typedef void(CObj::* OBJ_FUNC)(void);

class UI_Btn :public CObj_05UI
{
private:
    BTN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;

    SCN_FUNC    m_pScnFunc;
    CScn*       m_pScnInst;


public:
    CLONE(UI_Btn);
     
    virtual void cursorOn();
    virtual void cursorLbtnDown();
    virtual void cursorLbtnUp();
    virtual void cursorLbtnDownUp();

    void setBtnCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) 
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }
    void setBtnCallBack(CScn* _pScn, SCN_FUNC _pScnFunc);

public:
    UI_Btn();
    ~UI_Btn();


};

