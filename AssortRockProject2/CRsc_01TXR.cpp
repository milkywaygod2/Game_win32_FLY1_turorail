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
	//���Ϻ�Ʈ��
	m_hBit = (HBITMAP)LoadImage(nullptr, _rscFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);//LoadImage(�ý��ۺ�������?,�߰����ϰ��,������������,���κ���,���κ���,DIB���ǻ���|���������Ϸ�)
	assert(m_hBit);

	//��Ʈ�ʰ� ������dc
	m_dc = CreateCompatibleDC(CCore::GetInst()->getMainDC());
	
	//����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
		
	//��Ʈ�� ����������
	GetObject(m_hBit, sizeof(BITMAP), &m_bmInfo);
}

void CRsc_01TXR::create(UINT _iWidth, UINT _iHeight)
{
	HDC mainDC = CCore::GetInst()->getMainDC();
	m_hBit = CreateCompatibleBitmap(mainDC, _iWidth, _iHeight); //Compatibleȣȯ��
	m_dc = CreateCompatibleDC(mainDC);

	HBITMAP hBit1 = (HBITMAP)SelectObject(m_dc, m_hBit); //SelectObject(A,B) A�� DC�� ����, B�� ��Ʈ������ ����, ''���� ��Ʈ��''�� ��ȯ!!
	DeleteObject(hBit1); //���� ��Ʈ�� ����

	//��Ʈ�� ����������
	GetObject(m_hBit, sizeof(BITMAP), &m_bmInfo);
}
