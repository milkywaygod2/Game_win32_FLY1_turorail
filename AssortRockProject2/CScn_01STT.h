#pragma once
#include "CScn.h"
//����ν� ������Ʈ ������ ��Ȱ...


class CScn_01STT : public CScn //�ڡڻ�ӹ���, ���� Ŭ�������� ������ �� �͵鸸 ��Ʈ�� virtual���� �������� ����, �״�� ��밡��
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
    //update() ���
    //render() ���
    //const wstring& GetName() ���
    //void SetName(const wstring& _strName) ���
    //Scn_addObj(pObj, OBJ_TYPE::DFT) ���

public:
    void createForce();

public:
    CScn_01STT();
    ~CScn_01STT();
};

