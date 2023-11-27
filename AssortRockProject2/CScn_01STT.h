#pragma once
#include "CScn.h"
//현재로썬 오브젝트 관리자 역활...


class CScn_01STT : public CScn //★★상속문법, 상위 클래스에서 재정의 할 것들만 세트로 virtual선언 나머지는 굳이, 그대로 사용가능
{
private:
    bool m_bUseForce;
    Vec2 m_vForcePos;
    float m_fForceRange;
    float m_fForceRangeCur;
    float m_fForce;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();
    virtual void Exit();
    //update() 상속
    //render() 상속
    //const wstring& GetName() 상속
    //void SetName(const wstring& _strName) 상속
    //Scn_addObj(pObj, OBJ_TYPE::DFT) 상속

public:
    void createForce();

public:
    CScn_01STT();
    ~CScn_01STT();
};

