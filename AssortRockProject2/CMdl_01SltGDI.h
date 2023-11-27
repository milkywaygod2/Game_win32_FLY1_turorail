#pragma once
class CMdl_01SltGDI
{
private:
	HDC		m_hDC;
	HPEN	m_hDefaultPen;
	HBRUSH	m_hDefaultBrush;

public:
	CMdl_01SltGDI(HDC _dc, PEN_TYPE _ePenType);
	CMdl_01SltGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~CMdl_01SltGDI();


};

