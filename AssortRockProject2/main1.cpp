// main1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "CCore.h"
#include "framework.h"
#include "main1.h" 



#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                        // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                          // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];                    // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//싱글톤 패던 (어디서나 접근+객체 1개로 제한)
class CClass
{
private:
    int m_i;
    
public: //외부에서 실행가능
    static int m_iStatic; //정적 맴버(데이터영역)

public:
        void func()
    {
        m_i = 0;
        m_iStatic = 0;
    }

    //객체가 없어도 만들수있는 맴버함수(this가 없음) == 정적맴버함수(static)
    static void FUNC()
    {
        m_iStatic = 0;
    }

};
int CClass::m_iStatic = 0; // 클래스내 정적변수는 반드시 클래스밖에서 초기화해줘야함





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         /*실행된 프로세스의 시작주소, 메모리상 실제주소는 아님 가상머신위에서의 주소*/
                     _In_opt_ HINSTANCE hPrevInstance,  /*없어진 개념*/
                     _In_ LPWSTR    lpCmdLine,          /*cmd 같은데서 응용프로그램 실행할때 추가 명령어*/
                     _In_ int       nCmdShow)           
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    CClass a;
    CClass::FUNC();
    CClass::m_iStatic = 0; //(public+Class+외부초기화 조합으로 static인자 외부 컨트롤 가능!)


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDC_ASSORTROCKPROJECT2, szWindowClass, MAX_LOADSTRING); // key값 들어가는 부분

    MyRegisterClass(hInstance);// 윈도우 정보 등록
        
    if (!InitInstance (hInstance, nCmdShow))    // 애플리케이션 초기화를 수행합니다: (윈도우생성)
    {
        return FALSE;                           //실패하면 종료
    }

    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{1280,720}))) //Core초기화
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSORTROCKPROJECT2)); //단축키 테이블 정보 로딩

    MSG msg; //메세지 구조체
    //SetTimer(g_hWnd, 0, 10, nullptr); // 핸들,이벤트id,발생지연시간_1000이 1초,추가호출할함수주소_10은 예시), InitInstance안에 HWND hWnd선언된 구조라 독립적으로 체크되려면 별도 전역변수화하는게 좋음
    
    DWORD dwPrevCount = GetTickCount64(); //1초에 1000씩 세는 함수
    DWORD dwAccCount = 0;

    // 기본 메시지 루프: (가장 메인 프로세스, 디폴트는GetMessage, 메세지큐에서 메세지 확인될 때까지 대기), 메세지반응형 프로그램디자인, 없으면 아무것도 안함
    // msg.message == WM_QUIT인 경우 false를 반환 => 프로그램 종료
    while (true) //!메세지 Queue 선입선출,발생순 (참고:스택은 후입선출),PeekMessage흘겨보기==>마지막인자PM_REMOVE로 메시지 큐처리 및 삭제기능추가
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            int iTime = GetTickCount64(); //들어갈때시간
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); //!해석
                DispatchMessage(&msg); //!발송
            }
            dwAccCount += (GetTickCount64() - iTime);
        }
        else //윈도우의 메세지 기반 작동방식 외에, 호출할 내용 들어갈 곳
        {
            DWORD dwCurCount = GetTickCount64();
            if (dwCurCount - dwPrevCount > 1000)
            {
                float fRatio = (float)dwAccCount / 1000.f;

                wchar_t szBuff[50] = {}; //메모리 잡아주고
                swprintf_s(szBuff, L"메세지/전체프로세스 비율 : %f",fRatio); //실수를 문자열로 바꿔=>szBuff에 저장
                SetWindowText(g_hWnd, szBuff); //윈도우의 타이틀바 텍스트 설정

                dwPrevCount = dwCurCount; //초기화 안해주면 시간이 흐름에 따라 PrevCount는 while문들어오기전으로 고정,dwCurCount는 현재로 갱신되어 
                dwAccCount = 0;
            }

            //Game코드 수행
            //디자인패턴(설계유형)
            //싱글톤 패턴
        }
    }
    //KillTimer(g_hWnd, 10); //커널오브젝트는 시작후 반드시 종료!
    return (int) msg.wParam;
}

//  함수: MyRegisterClass()
//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; //구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc; //전방선언후 아래구현부에 함수포인터 구현
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSORTROCKPROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSORTROCKPROJECT2); //nullptr 넣으면 메뉴바 사용하지않겟다 (파일,편집,보기 등등)
    wcex.lpszClassName  = szWindowClass; //정보세팅한 key값
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); //윈도우 제공함수, 코드는 못보고 선언만 볼수있음
}

//   함수: InitInstance(HINSTANCE, int)
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//   주석:이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // 커널오브젝트_MS제공(szWindowClass => key값 찾음)
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow); // hWnd => 윈도우의 id
   UpdateWindow(g_hWnd);

   return TRUE;
}

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//  용도: 주 창의 메시지를 처리합니다.
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
#include <vector>
using std::vector;

struct tObjInfo //오브젝트정보
{
    POINT g_ptObjectPos = { 500,300 }; // 중심위치
    POINT g_ptObjectScale = { 100,100 }; //가로세로 길이
};
vector<tObjInfo> g_vecInfo;
POINT g_ptLT;//좌상단 좌표
POINT g_ptRB;//우하단 좌표

bool bLbtnDown = false; //미리보기기능없애기위한 변수

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)// 메뉴 선택을 구문 분석합니다:
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }break;
    case WM_PAINT: //무효화 영역(invalidate)이 발생한 경우 by MSDN
        { // switch case에서 {} 있는 경우, 지역변수 선언 필요한 경우
            PAINTSTRUCT ps;

            HWND;// ID중복을 피하기 위한? 핸들 들(예시나열)
            HPEN;
            HBRUSH;

            HDC hdc = BeginPaint(hWnd, &ps); //Device Context라는 핸들
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

                //윈도우 핸들 : 윈도우 API를 조작할 수 있는 인자(== ID == 핸들), API자체는 그냥 주는 대로 써야함
                //윈도우 좌표 : 
                //HDC : 커널오브젝트의 일종, DC의 목적지는 hWnd, 기본팬은 검정, 기본브러쉬(페인트)는 흰색

            HPEN hRedPen = CreatePen(PS_SOLID,1,RGB(255,0,0)); ///팬을 직접만들어서 DC에지급
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 115, 0)); // 만들어 쓰는 경우 GetStockObject(); Stock류는 사용후 삭제하면 안됨, HOLLOW BRUSH자주씀

            
            HPEN hDefaualtPen = (HPEN)SelectObject(hdc, hRedPen); //디폴트 반환저장
            HPEN hDefaualtBrush = (HPEN)SelectObject(hdc, hBlueBrush); //SelectObject는 A를 B로 선택해주고, 원래 디폴트A 값을 반환한다

            if (bLbtnDown)//드로잉
            {   
                Rectangle(hdc                                   
                    , g_ptLT.x, g_ptLT.y
                    , g_ptRB.x, g_ptRB.y
                );//(hdc, left, top, right, buttom) x는 정방향 y는 아래가 플러스
            }
            for (size_t i = 0; i < g_vecInfo.size(); ++i)//추가된 사각형 백터로 누적관리
            {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjectPos.x - g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPos.y - g_vecInfo[i].g_ptObjectScale.y / 2
                    , g_vecInfo[i].g_ptObjectPos.x + g_vecInfo[i].g_ptObjectScale.x / 2
                    , g_vecInfo[i].g_ptObjectPos.y + g_vecInfo[i].g_ptObjectScale.y / 2
                );
            }
            SelectObject(hdc, hDefaualtPen);//디폴트로 복구
            SelectObject(hdc, hDefaualtBrush);

            DeleteObject(hRedPen); //삭제
            DeleteObject(hBlueBrush);

            EndPaint(hWnd, &ps);//종료
        }break;

        
    case WM_KEYDOWN: //키보드조작부
    {
        switch (wParam)
        {
        case VK_UP:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
    
        case VK_DOWN:
            //g_ptObjectPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_RIGHT:
            //g_ptObjectPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case VK_LEFT:
            //g_ptObjectPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;

        case 'W': //아스키코드 대문자만 인식함, 소문자 안됨
            {
                int a = 0;
            }break;
        }
    }break;
    
    case WM_LBUTTONDOWN: //마우스L 클릭
        g_ptLT.x = LOWORD(lParam);
        g_ptLT.y = HIWORD(lParam);
        bLbtnDown = true;
        break;

    case WM_MOUSEMOVE: //마우스이동시
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        //InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_LBUTTONUP: //마우스L 언클릭
    {
        tObjInfo info = {};
        info.g_ptObjectPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjectPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjectScale.x = abs(g_ptLT.x - g_ptRB.x); //abs 절대값함수
        info.g_ptObjectScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;

        InvalidateRect(hWnd, nullptr, true);
    }break;

    /*
    case WM_TIMER: //아무내용없으므로 무조건실행, 강제로 한바퀴씩 돌려서 화면 새로고침 실행시켜줌

        break;
    */

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // 기타 답변 ㅋㅋ
    }return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }break;
    }return (INT_PTR)FALSE;
}
