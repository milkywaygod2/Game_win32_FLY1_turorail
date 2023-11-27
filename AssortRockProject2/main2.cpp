// main1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
//#include "CCore.h"
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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         /*실행된 프로세스의 시작주소, 메모리상 실제주소는 아님 가상머신위에서의 주소*/
    _In_opt_ HINSTANCE hPrevInstance,  /*없어진 개념*/
    _In_ LPWSTR    lpCmdLine,          /*cmd 같은데서 응용프로그램 실행할때 추가 명령어*/
    _In_ int       nCmdShow)
{
    //메모리 릭 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(); //문제 생겼을때 중단점 거는 기능


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
   
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDC_ASSORTROCKPROJECT2, szWindowClass, MAX_LOADSTRING); // key값 들어가는 부분

    MyRegisterClass(hInstance);// 윈도우 정보 등록

    if (!InitInstance(hInstance, nCmdShow))    // 애플리케이션 초기화를 수행합니다: (윈도우생성)
    {
        return FALSE;                           //실패하면 종료
    }

    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280,768 }))) //Core초기화
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSORTROCKPROJECT2)); //단축키 테이블 정보 로딩

    MSG msg; //메세지 구조체
    
    // 기본 메시지 루프: (가장 메인 프로세스, 디폴트는GetMessage, 메세지큐에서 메세지 확인될 때까지 대기), 메세지반응형 프로그램디자인, 없으면 아무것도 안함
    // msg.message == WM_QUIT인 경우 false를 반환 => 프로그램 종료
    while (true) //!메세지 Queue 선입선출,발생순 (참고:스택은 후입선출),PeekMessage흘겨보기==>마지막인자PM_REMOVE로 메시지 큐처리 및 삭제기능추가
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            ULONGLONG iTime = GetTickCount64(); //들어갈때시간
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); //!해석
                DispatchMessage(&msg); //!발송
            }
        }
        else //윈도우의 메세지 기반 작동방식 외에, 호출할 내용 들어갈 곳
        {
            //Game코드 수행
            //디자인패턴(설계유형)
            //싱글톤 패턴
            CCore::GetInst()->progress();
        }
    }
    //KillTimer(g_hWnd, 10); //커널오브젝트는 시작후 반드시 종료!
    return (int)msg.wParam;
}

//  함수: MyRegisterClass()
//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; //구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; //전방선언후 아래구현부에 함수포인터 구현
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSORTROCKPROJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_ASSORTROCKPROJECT2); //메뉴바
    wcex.lpszClassName = szWindowClass; //정보세팅한 key값
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

//전방선언
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam); //CScn_00TL.cpp


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
        case ID_MENU_TILE_COUNT://커스텀추가 CScn_00TL.cpp
            DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT_TILE), hWnd, TileCountProc);
        
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
        HDC hdc = BeginPaint(hWnd, &ps); //Device Context라는 핸들
        //Rectangle(hdc, 1180 ,0, 1280, 100);
        EndPaint(hWnd, &ps);//종료
    }break;

    case WM_KEYDOWN: //키보드조작부
        break;
    case WM_LBUTTONDOWN: //마우스L 클릭
        break;
    case WM_MOUSEMOVE: //마우스이동시
        break;
    case WM_LBUTTONUP: //마우스L 언클릭
        break;
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
