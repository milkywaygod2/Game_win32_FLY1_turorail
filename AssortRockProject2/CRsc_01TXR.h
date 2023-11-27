#pragma once
#include "CRsc.h"
class CRsc_01TXR :public CRsc
{
private:
    HDC     m_dc;
    HBITMAP m_hBit;
    BITMAP  m_bmInfo;

public:
    void Load(const wstring& _rscFilePath);
    void create(UINT _iWidth, UINT _iHeight);

    UINT Width() { return m_bmInfo.bmWidth; }
    UINT Height() { return m_bmInfo.bmHeight; }

    HDC getDC() { return m_dc; }
private:
    CRsc_01TXR();
    virtual ~CRsc_01TXR();
    friend class mgr_Rsc;


};

