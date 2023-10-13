#include "pch.h"
#include "Application.h"
#include "Timer.h"
#include "Tool.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                               
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

const wchar_t* gWindowName = L"Death's Door";

WindowInfo gWindowInfo;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(41845);

    WNDCLASSEX wcex{ 0 };
    wcex.cbSize = sizeof(wcex);
    wcex.lpszClassName = gWindowName;
    wcex.lpfnWndProc = WndProc;
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
    wcex.hInstance = hInstance;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    ATOM atom = RegisterClassEx(&wcex);

    gWindowInfo.width = 1600;
    gWindowInfo.height = 900;

    HWND hwnd = CreateWindowW(gWindowName, gWindowName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    AssertEx(hwnd, L"wWinMain() - Create WindowHandle Failed");
    gWindowInfo.hwnd = hwnd;

    ShowWindow(hwnd, SW_SHOW);
    MSG msg{ 0 };

    unique_ptr<Application> pApplication = make_unique<Application>();
    pApplication->Initialize(gWindowInfo);
    pApplication->Start();

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(1));

    float accTime = 0.f;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        pApplication->Update();
    }

    pApplication->Destroy();
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (TOOL->DispatchWndMessage(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
