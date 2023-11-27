#include "pch.h"
#include "CRsc_01TXR.h"


CRsc_01TXR::CRsc_01TXR()
	: m_dc(0)
	, m_hBit(0)
	, m_bmInfo{}
{}
CRsc_01TXR::~CRsc_01TXR()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CRsc_01TXR::Load(const wstring& _rscFilePath)
{
	//파일비트맵
	m_hBit = (HBITMAP)LoadImage(nullptr, _rscFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);//LoadImage(시스템보유파일?,추가파일경로,담을파일형식,가로변경,세로변경,DIB섹션생성|가져온파일로)
	assert(m_hBit);

	//비트맵과 연결할dc
	m_dc = CreateCompatibleDC(CCore::GetInst()->getMainDC());
	
	//연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
		
	//비트맵 사이즈정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bmInfo);
}

void CRsc_01TXR::create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInst()->getMainDC();
	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight); //Compatible호환성
	m_dc = CreateCompatibleDC(mainDC);

	HBITMAP hBit1 = (HBITMAP)SelectObject(m_dc, m_hBit); //SelectObject(A,B) A를 DC로 선택, B를 비트맵으로 선택, ''이전 비트맵''을 반환!!
	DeleteObject(hBit1); //이전 비트맵 삭제

	//비트맵 사이즈정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bmInfo);
}
