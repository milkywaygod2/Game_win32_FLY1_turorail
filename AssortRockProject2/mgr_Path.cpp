#include "pch.h"
#include "mgr_Path.h"

mgr_Path::mgr_Path()
	: m_szCttPath{}
{}
mgr_Path::~mgr_Path(){}

void mgr_Path::init()
{
	GetCurrentDirectory(255, m_szCttPath);	//����� �������� ��� ã���ִ� Ŀ��,
	int iLength = (int)wcslen(m_szCttPath);		//C:\Users\user\source\repos\AssortRock_win32\x64\bin
	for (int i = iLength-1; 0 <= i; --i)
	{
		if ('\\' == m_szCttPath[i]) {
			m_szCttPath[i] = '\0';//nulló��, ���������� ���� �ǹ� ~~~~AssortRock_win32\x64
			break;
		}
	}
	wcscat_s(m_szCttPath, 255, L"\\bin\\resource\\"); //���ڿ� �����ֱ�~~~~AssortRock_win32\x64\\bin\\resource\\
	
	SetWindowText(CCore::GetInst()->getMainHwnd(), m_szCttPath);
}

wstring mgr_Path::getRltvPath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;
	size_t iAbsLen = wcslen(m_szCttPath);
	size_t iFllLen = strFilePath.length();
	wstring strRltvPath = strFilePath.substr(iAbsLen, iFllLen - iAbsLen); // �߶� ��ġ����, �ڸ� ����
	return strRltvPath;
}
