#pragma once
#include "pch.h"
#include "CObj.h"
class CRsc_01TXR;

class CObj_04TL :
    public CObj
{
private:
    CRsc_01TXR*  m_pTileTXR;
    int          m_iTileIdx; //아무것도 안넣을때 -1

public:
    void setTileTXR(CRsc_01TXR* _pTileTXR) { m_pTileTXR = _pTileTXR; }
    void addTileIdx() { ++m_iTileIdx; }

private:
    virtual void update();
    virtual void render(HDC _DC);

public:
    virtual void save(FILE* _pFile);
    virtual void load(FILE* _pFile);

    CLONE(CObj_04TL);

public:

public:
    CObj_04TL();
    virtual ~CObj_04TL();
};

