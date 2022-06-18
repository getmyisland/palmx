#include <SDKDDKVer.h>

// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstdio>

#include "SystemManager.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"Palm Engine";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING] = L"Palm Engine Window";

// Forward declarations of functions included in this code module:
ATOM                RegisterEngineClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

ATOM RegisterEngineClass(HINSTANCE hInstance)
{
    WNDCLASSEXW windowClass;

    windowClass.cbSize = sizeof(WNDCLASSEX);

    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = szWindowClass;
    windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);

    return RegisterClassExW(&windowClass);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg) {
    case WM_SYSKEYDOWN:
        // swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        // OutputDebugString(msg);
        break;

    case WM_SYSCHAR:
        // swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        // OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        // swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        // OutputDebugString(msg);
        break;

    case WM_KEYDOWN:
        // Output Example: 0x57
        // swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        // OutputDebugString(msg);
        break;

    case WM_KEYUP:
        // Output Example: 0x57
        // swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        // OutputDebugString(msg);
        break;

    case WM_CHAR:
        // Send the event to the system manager
        SystemManager::GetInstance().SendMessageEvent(Message(Message::MessageEvent::KEY_CHAR, "A"));

        // Output Example: A
        swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    RegisterEngineClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, IDI_APPLICATION);
    MSG msg;

    // Init all Systems
    SystemManager::GetInstance().InitSystems();

    // Main loop
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Update Systems
        //SystemManager::GetInstance().UpdateSystems();
    }

    // Shutdown Systems with SystemManager
    SystemManager::GetInstance().ShutDownSystems();

    return (int)msg.wParam;
}