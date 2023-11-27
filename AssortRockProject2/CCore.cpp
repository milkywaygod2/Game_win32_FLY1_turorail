#include "pch.h"
#include "CCore.h"
#include "CRsc_01TXR.h"

//#include "mgr_Timer.h"
//#include "mgr_Key.h"

//#include "CObj.h"


CCore::CCore()
	:m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{}
CCore::~CCore(){
	ReleaseDC(m_hWnd, m_hDC);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i){DeleteObject(m_arrPen[i]);}
	DestroyMenu(m_hMenu);
}

int CCore::init(HWND _hWnd, POINT _ptResolution) 
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	//�ػ󵵿� �°� ������ ũ������
	CCore_windowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	//�޴���
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_ASSORTROCKPROJECT2));


	m_hDC = GetDC(m_hWnd);

	//���߹��۸��� �ؽ��� ���� �����
	m_pTxr = mgr_Rsc::GetInst()->createTxr(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
		
	createBrushPen(); //���ֻ���� ��,�귯��

	//�Ŵ��� �ʱ�ȭ
	mgr_Path::GetInst()->init();
	mgr_Timer::GetInst()->init();
	mgr_Key::GetInst()->init();
	mgr_Cam::GetInst()->init();
	mgr_Snd::GetInst()->init();
	mgr_Scn::GetInst()->init();

	//Sound �ε��׽�Ʈ
	mgr_Rsc::GetInst()->loadSnd(L"BGM_01", L"sound\\BGM_01_let-s-go-easy-fast-loop.wav");
	CRsc_02SND* pBGM_01 = mgr_Rsc::GetInst()->findSnd(L"BGM_01"); //��ü �ε�

	pBGM_01->playSound();

	pBGM_01->setSoundPercent(0.f); //��з�, �Ҹ����൵
	pBGM_01->playSoundBGM(true);
	//pBGM_01->setSoundVolume(60.f);

	return S_OK;
}

void CCore::progress()
{
	//�Ŵ��� ������Ʈ
	mgr_Timer::GetInst()->update(); //�ð����
	mgr_Key::GetInst()->update(); //����Ű������Ʈ
	mgr_Cam::GetInst()->update(); //ī�޶���ġ����
	mgr_Scn::GetInst()->update(); //ȭ�������Ʈ
	mgr_Clls::GetInst()->update(); //�浹üũ
	mgr_UI::GetInst()->update(); //UI�̺�Ʈüũ

	//�غ�ȭ�� Ŭ����
	Rectangle(m_pTxr->getDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CCore_Clear();
	
	//������ (�������ּ�)
	mgr_Scn::GetInst()->render(m_pTxr->getDC());
	mgr_Cam::GetInst()->render(m_pTxr->getDC());
	/*
	1.������ : ���Ŵ���.render ���� ���
		mgr_Scn::GetInst()->render(m_hDC1);
	
	2.���Ŵ����� �迭�� STT���� ������ ���
		m_arrScn[(UINT)SCN_TYPE::STT]->render(_dc);

	3.class CScn_01STT �� render�Լ��� ������, 
	CScn�� ��� CScn.render '��ü'�� �����, 
	m_arrObj[objŸ��][obj��ü]->render(_dc) ����� �ݺ������� ������ �����
		void CScn::render(HDC _dc)	{
			for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)	{
				for (size_t j = 0; j < m_arrObj[i].size(); ++j)		{
					m_arrObj[i][j]->render(_dc); //m_arrObj[������ƮŸ��][������Ʈ��ȣ]->render(_dc)}}}

	**���� class CScn_01STT�� �ش� ���� ������Ʈ �߰��ϴ� ���, ��������� ����
		CObj* pObj = new CObj;
		Scn_addObj(pObj, OBJ_TYPE::DFT);

	4.m_arrObj[objŸ��][obj��ü]->render(_dc) ����� 
	Ư��������Ʈ�� m_arrObj[������ƮŸ��][������Ʈ��ȣ]�� �ش��ϴ� 1���� �޾ƿͼ�, 
	�׾��� ������Ʈ���� void CObj::render(HDC _dc)�� ���� ���.
		void CObj::render(HDC _dc)	{
			Rectangle(_dc
				, (int)(m_vPos.x - m_vScale.x / 2.f)
				, (int)(m_vPos.y - m_vScale.y / 2.f)
				, (int)(m_vPos.x + m_vScale.x / 2.f)
				, (int)(m_vPos.y + m_vScale.y / 2.f) );	}
	*/

	//����ȭ�鿡 ���� (GPU��, ������ ���� ����)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pTxr->getDC(), 0, 0, SRCCOPY);

	//FPSȭ��ǥ�ñ��
	mgr_Timer::GetInst()->render();

	//�̺�Ʈó�� (����ó��)
	mgr_Evt::GetInst()->update();
}

void CCore::createBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //���������Ʈ�� �����Ҹ� ĳ�� ���ʿ�
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::CCore_Clear()
{
	//CMdl_01SltGDI gdi(m_pTxr->getDC(), BRUSH_TYPE::BLACK);
	//Rectangle(m_pTxr->getDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CCore_attachMenu()
{
	//�޴����̱�
	SetMenu(m_hWnd, m_hMenu);
	CCore_windowSize(getResolution(), true);
}

void CCore::CCore_detachMenu()
{
	SetMenu(m_hWnd, nullptr);
	CCore_windowSize(getResolution(), false);
}

void CCore::CCore_windowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0,(long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); //������ ��Ÿ��,�޴���
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}
