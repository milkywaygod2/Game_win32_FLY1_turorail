#pragma once
#include "CRsc_01TXR.h"
//싱글톤 패던 (어디서나 접근+객체 1개로 제한)
class CCore
{
public:
	SINGLETON(CCore); //public: static

private:
	HWND	m_hWnd;			//메인 윈도우 핸들
	POINT	m_ptResolution;	//메인 윈도우 해상도
	HDC		m_hDC;			//메인 윈도우에 그릴 DC

	CRsc_01TXR* m_pTxr; //HBITMAP,HDC말고 이걸로 대체 가능 - 백버퍼텍스처

	//자주 사용하는 GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	HMENU	m_hMenu; //툴씬용

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void createBrushPen();
	void CCore_Clear();

public:
	void CCore_attachMenu();
	void CCore_detachMenu();
	void CCore_windowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND getMainHwnd() { return m_hWnd; }
	HDC getMainDC() { return m_hDC; }

	POINT getResolution() { return m_ptResolution; }
	HBRUSH getBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN getPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }


};