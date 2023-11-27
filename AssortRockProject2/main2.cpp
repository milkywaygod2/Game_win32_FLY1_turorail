// main1.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "pch.h"
//#include "CCore.h"
#include "framework.h"
#include "main1.h" 

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                        // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                          // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];                    // �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWnd;

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         /*����� ���μ����� �����ּ�, �޸𸮻� �����ּҴ� �ƴ� ����ӽ��������� �ּ�*/
    _In_opt_ HINSTANCE hPrevInstance,  /*������ ����*/
    _In_ LPWSTR    lpCmdLine,          /*cmd �������� �������α׷� �����Ҷ� �߰� ��ɾ�*/
    _In_ int       nCmdShow)
{
    //�޸� �� üũ
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(); //���� �������� �ߴ��� �Ŵ� ���


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
   
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDC_ASSORTROCKPROJECT2, szWindowClass, MAX_LOADSTRING); // key�� ���� �κ�

    MyRegisterClass(hInstance);// ������ ���� ���

    if (!InitInstance(hInstance, nCmdShow))    // ���ø����̼� �ʱ�ȭ�� �����մϴ�: (���������)
    {
        return FALSE;                           //�����ϸ� ����
    }

    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280,768 }))) //Core�ʱ�ȭ
    {
        MessageBox(nullptr, L"Core ��ü �ʱ�ȭ ����", L"ERROR", MB_OK);
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSORTROCKPROJECT2)); //����Ű ���̺� ���� �ε�

    MSG msg; //�޼��� ����ü
    
    // �⺻ �޽��� ����: (���� ���� ���μ���, ����Ʈ��GetMessage, �޼���ť���� �޼��� Ȯ�ε� ������ ���), �޼��������� ���α׷�������, ������ �ƹ��͵� ����
    // msg.message == WM_QUIT�� ��� false�� ��ȯ => ���α׷� ����
    while (true) //!�޼��� Queue ���Լ���,�߻��� (����:������ ���Լ���),PeekMessage��ܺ���==>����������PM_REMOVE�� �޽��� ťó�� �� ��������߰�
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            ULONGLONG iTime = GetTickCount64(); //�����ð�
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); //!�ؼ�
                DispatchMessage(&msg); //!�߼�
            }
        }
        else //�������� �޼��� ��� �۵���� �ܿ�, ȣ���� ���� �� ��
        {
            //Game�ڵ� ����
            //����������(��������)
            //�̱��� ����
            CCore::GetInst()->progress();
        }
    }
    //KillTimer(g_hWnd, 10); //Ŀ�ο�����Ʈ�� ������ �ݵ�� ����!
    return (int)msg.wParam;
}

//  �Լ�: MyRegisterClass()
//  �뵵: â Ŭ������ ����մϴ�.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; //����ü

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; //���漱���� �Ʒ������ο� �Լ������� ����
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSORTROCKPROJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_ASSORTROCKPROJECT2); //�޴���
    wcex.lpszClassName = szWindowClass; //���������� key��
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); //������ �����Լ�, �ڵ�� ������ ���� ��������
}

//   �Լ�: InitInstance(HINSTANCE, int)
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//   �ּ�:�� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ� �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // Ŀ�ο�����Ʈ_MS����(szWindowClass => key�� ã��)
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        return FALSE;
    }

    ShowWindow(g_hWnd, nCmdShow); // hWnd => �������� id
    UpdateWindow(g_hWnd);

    return TRUE;
}

//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//  �뵵: �� â�� �޽����� ó���մϴ�.
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//

//���漱��
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam); //CScn_00TL.cpp


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)// �޴� ������ ���� �м��մϴ�:
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case ID_MENU_TILE_COUNT://Ŀ�����߰� CScn_00TL.cpp
            DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT_TILE), hWnd, TileCountProc);
        
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }break;
    case WM_PAINT: //��ȿȭ ����(invalidate)�� �߻��� ��� by MSDN
    { // switch case���� {} �ִ� ���, �������� ���� �ʿ��� ���
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps); //Device Context��� �ڵ�
        //Rectangle(hdc, 1180 ,0, 1280, 100);
        EndPaint(hWnd, &ps);//����
    }break;

    case WM_KEYDOWN: //Ű�������ۺ�
        break;
    case WM_LBUTTONDOWN: //���콺L Ŭ��
        break;
    case WM_MOUSEMOVE: //���콺�̵���
        break;
    case WM_LBUTTONUP: //���콺L ��Ŭ��
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // ��Ÿ �亯 ����
    }return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
