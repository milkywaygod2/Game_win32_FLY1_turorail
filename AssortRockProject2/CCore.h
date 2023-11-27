#pragma once
#include "CRsc_01TXR.h"
//�̱��� �д� (��𼭳� ����+��ü 1���� ����)
class CCore
{
public:
	SINGLETON(CCore); //public: static

private:
	HWND	m_hWnd;			//���� ������ �ڵ�
	POINT	m_ptResolution;	//���� ������ �ػ�
	HDC		m_hDC;			//���� �����쿡 �׸� DC

	CRsc_01TXR* m_pTxr; //HBITMAP,HDC���� �̰ɷ� ��ü ���� - ������ؽ�ó

	//���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	HMENU	m_hMenu; //������

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