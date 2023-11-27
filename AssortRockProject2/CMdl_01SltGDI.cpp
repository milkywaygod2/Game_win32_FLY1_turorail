#include "pch.h"
#include "CMdl_01SltGDI.h"

CMdl_01SltGDI::CMdl_01SltGDI(HDC _dc, PEN_TYPE _ePenType)
	:m_hDC(_dc)
	, m_hDefaultBrush(nullptr)
	,m_hDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetInst()->getPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

CMdl_01SltGDI::CMdl_01SltGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	:m_hDC(_dc) 
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->getBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

CMdl_01SltGDI::~CMdl_01SltGDI()
{
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}
