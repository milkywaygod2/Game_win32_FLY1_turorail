#pragma once
#include "pch.h"


#include "CObj.h"
class CObj_05UI :
    public CObj
{
private:
    vector<CObj_05UI*>  m_vecChildUI;
    CObj_05UI*          m_pParentUI;

    Vec2                m_vAccPos;
    bool                m_bCamRender; //카메라영향여부
    bool                m_bCursorOn;
    bool                m_bPrevLbtnDown;

public:
    void addChild(CObj_05UI* _pUI) { m_vecChildUI.push_back(_pUI); 
                                        _pUI->m_pParentUI = this; }
    CObj_05UI* getParent() { return m_pParentUI; }

    Vec2 getAccPos() { return m_vAccPos; }
    
    bool isCursorOn() { return m_bCursorOn; }
    bool isLbtnOn() { return m_bPrevLbtnDown; }

    const vector<CObj_05UI*>& getChildUI() { return m_vecChildUI; }

public:
    virtual void cursorOn();
    virtual void cursorLbtnDown();
    virtual void cursorLbtnUp();
    virtual void cursorLbtnDownUp();

    void checkCursorOn();

public:
    virtual CObj_05UI* clone() = 0; //순수가상함수, 포인터로 관리를 위한

    virtual void update();
    virtual void render(HDC _dc);
    virtual void finalupdate();

private:
    void updateChild();
    void renderChild(HDC _dc);
    void finalupdateChild();

public:
    CObj_05UI(bool _bCamRender); //기본생성자없애고 강제요구
    CObj_05UI(const CObj_05UI& _origin);
    virtual ~CObj_05UI();

    friend class mgr_UI;
    friend class mgr_Evt;
};

