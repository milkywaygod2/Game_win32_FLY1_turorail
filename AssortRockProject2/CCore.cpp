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

	//해상도에 맞게 윈도우 크기조정
	CCore_windowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	//메뉴바
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_ASSORTROCKPROJECT2));


	m_hDC = GetDC(m_hWnd);

	//이중버퍼링용 텍스쳐 한장 만들기
	m_pTxr = mgr_Rsc::GetInst()->createTxr(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);
		
	createBrushPen(); //자주사용할 펜,브러쉬

	//매니저 초기화
	mgr_Path::GetInst()->init();
	mgr_Timer::GetInst()->init();
	mgr_Key::GetInst()->init();
	mgr_Cam::GetInst()->init();
	mgr_Snd::GetInst()->init();
	mgr_Scn::GetInst()->init();

	//Sound 로드테스트
	mgr_Rsc::GetInst()->loadSnd(L"BGM_01", L"sound\\BGM_01_let-s-go-easy-fast-loop.wav");
	CRsc_02SND* pBGM_01 = mgr_Rsc::GetInst()->findSnd(L"BGM_01"); //객체 로드

	pBGM_01->playSound();

	pBGM_01->setSoundPercent(0.f); //백분률, 소리진행도
	pBGM_01->playSoundBGM(true);
	//pBGM_01->setSoundVolume(60.f);

	return S_OK;
}

void CCore::progress()
{
	//매니저 업데이트
	mgr_Timer::GetInst()->update(); //시간계산
	mgr_Key::GetInst()->update(); //조작키업데이트
	mgr_Cam::GetInst()->update(); //카메라위치보정
	mgr_Scn::GetInst()->update(); //화면업데이트
	mgr_Clls::GetInst()->update(); //충돌체크
	mgr_UI::GetInst()->update(); //UI이벤트체크

	//준비화면 클리어
	Rectangle(m_pTxr->getDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CCore_Clear();
	
	//랜더링 (순서도주석)
	mgr_Scn::GetInst()->render(m_pTxr->getDC());
	mgr_Cam::GetInst()->render(m_pTxr->getDC());
	/*
	1.랜더링 : 씬매니저.render 실행 명령
		mgr_Scn::GetInst()->render(m_hDC1);
	
	2.씬매니저의 배열중 STT씬을 랜더링 명령
		m_arrScn[(UINT)SCN_TYPE::STT]->render(_dc);

	3.class CScn_01STT 는 render함수가 없지만, 
	CScn을 상속 CScn.render '전체'가 실행됨, 
	m_arrObj[obj타입][obj객체]->render(_dc) 명령이 반복문으로 여러번 실행됨
		void CScn::render(HDC _dc)	{
			for (UINT i = 0; i < (UINT)OBJ_TYPE::objEND; ++i)	{
				for (size_t j = 0; j < m_arrObj[i].size(); ++j)		{
					m_arrObj[i][j]->render(_dc); //m_arrObj[오브젝트타입][오브젝트번호]->render(_dc)}}}

	**참고 class CScn_01STT는 해당 씬에 오브젝트 추가하는 기능, 렌더기능은 없음
		CObj* pObj = new CObj;
		Scn_addObj(pObj, OBJ_TYPE::DFT);

	4.m_arrObj[obj타입][obj객체]->render(_dc) 명령중 
	특정오브젝트의 m_arrObj[오브젝트타입][오브젝트번호]에 해당하는 1줄을 받아와서, 
	그안의 오브젝트에게 void CObj::render(HDC _dc)를 실행 명령.
		void CObj::render(HDC _dc)	{
			Rectangle(_dc
				, (int)(m_vPos.x - m_vScale.x / 2.f)
				, (int)(m_vPos.y - m_vScale.y / 2.f)
				, (int)(m_vPos.x + m_vScale.x / 2.f)
				, (int)(m_vPos.y + m_vScale.y / 2.f) );	}
	*/

	//실제화면에 송출 (GPU몫, 프레임 많이 먹음)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pTxr->getDC(), 0, 0, SRCCOPY);

	//FPS화면표시기능
	mgr_Timer::GetInst()->render();

	//이벤트처리 (지연처리)
	mgr_Evt::GetInst()->update();
}

void CCore::createBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); //스톡오브젝트는 생성소멸 캐어 불필요
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
	//메뉴붙이기
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
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); //윈도우 스타일,메뉴바
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}
