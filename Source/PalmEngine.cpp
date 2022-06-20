#include <SDKDDKVer.h>

// Windows Header Files
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstdio>
#include <codecvt>
#include <locale>
#include <iostream>
#include <io.h>
#include <fcntl.h>

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
	switch (uMsg) 
	{
	case WM_SYSKEYDOWN: 
	{
		// Send an input event to the input manager
		SystemManager::GetInstance().GetInputSystem().ProcessKeyboardInput(InputSystem::InputType::INPUT_KEY_DOWN, (char)(wchar_t)wParam);

		// swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
		// OutputDebugString(msg);
		
		break;
	}
	case WM_SYSKEYUP: 
	{
		// Send an input event to the input manager
		SystemManager::GetInstance().GetInputSystem().ProcessKeyboardInput(InputSystem::InputType::INPUT_KEY_UP, (char)(wchar_t)wParam);

		// swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
		// OutputDebugString(msg);
		
		break;
	}
	case WM_SYSCHAR: 
	{
		// swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
		// OutputDebugString(msg);
		
		break;
	}
	case WM_KEYDOWN: 
	{
		// Send an input event to the input manager
		SystemManager::GetInstance().GetInputSystem().ProcessKeyboardInput(InputSystem::InputType::INPUT_KEY_DOWN, (char)(wchar_t)wParam);

		// Output Example: 0x57
		// swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
		// OutputDebugString(msg);
		
		break;
	}
	case WM_KEYUP: 
	{
		// Send an input event to the input manager
		SystemManager::GetInstance().GetInputSystem().ProcessKeyboardInput(InputSystem::InputType::INPUT_KEY_UP, (char)(wchar_t)wParam);

		// Output Example: 0x57
		// swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
		// OutputDebugString(msg);
		
		break;
	}
	case WM_CHAR: 
	{
		// Output Example: A
		//swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
		//OutputDebugString(msg);

		break;
	}
	case WM_DESTROY: 
	{
		PostQuitMessage(0);

		break;
	}
	default:  { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr)
{
	// Re-initialize the C runtime "FILE" handles with clean handles bound to "nul". We do this because it has been
	// observed that the file number of our standard handle file objects can be assigned internally to a value of -2
	// when not bound to a valid target, which represents some kind of unknown internal invalid state. In this state our
	// call to "_dup2" fails, as it specifically tests to ensure that the target file number isn't equal to this value
	// before allowing the operation to continue. We can resolve this issue by first "re-opening" the target files to
	// use the "nul" device, which will place them into a valid state, after which we can redirect them to our target
	// using the "_dup2" function.
	if (bindStdIn)
	{
		FILE* dummyFile;
		freopen_s(&dummyFile, "nul", "r", stdin);
	}
	if (bindStdOut)
	{
		FILE* dummyFile;
		freopen_s(&dummyFile, "nul", "w", stdout);
	}
	if (bindStdErr)
	{
		FILE* dummyFile;
		freopen_s(&dummyFile, "nul", "w", stderr);
	}

	// Redirect unbuffered stdin from the current standard input handle
	if (bindStdIn)
	{
		HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);
		if (stdHandle != INVALID_HANDLE_VALUE)
		{
			int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
			if (fileDescriptor != -1)
			{
				FILE* file = _fdopen(fileDescriptor, "r");
				if (file != NULL)
				{
					int dup2Result = _dup2(_fileno(file), _fileno(stdin));
					if (dup2Result == 0)
					{
						setvbuf(stdin, NULL, _IONBF, 0);
					}
				}
			}
		}
	}

	// Redirect unbuffered stdout to the current standard output handle
	if (bindStdOut)
	{
		HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (stdHandle != INVALID_HANDLE_VALUE)
		{
			int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
			if (fileDescriptor != -1)
			{
				FILE* file = _fdopen(fileDescriptor, "w");
				if (file != NULL)
				{
					int dup2Result = _dup2(_fileno(file), _fileno(stdout));
					if (dup2Result == 0)
					{
						setvbuf(stdout, NULL, _IONBF, 0);
					}
				}
			}
		}
	}

	// Redirect unbuffered stderr to the current standard error handle
	if (bindStdErr)
	{
		HANDLE stdHandle = GetStdHandle(STD_ERROR_HANDLE);
		if (stdHandle != INVALID_HANDLE_VALUE)
		{
			int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
			if (fileDescriptor != -1)
			{
				FILE* file = _fdopen(fileDescriptor, "w");
				if (file != NULL)
				{
					int dup2Result = _dup2(_fileno(file), _fileno(stderr));
					if (dup2Result == 0)
					{
						setvbuf(stderr, NULL, _IONBF, 0);
					}
				}
			}
		}
	}

	// Clear the error state for each of the C++ standard stream objects. We need to do this, as attempts to access the
	// standard streams before they refer to a valid target will cause the iostream objects to enter an error state. In
	// versions of Visual Studio after 2005, this seems to always occur during startup regardless of whether anything
	// has been read from or written to the targets or not.
	if (bindStdIn)
	{
		std::wcin.clear();
		std::cin.clear();
	}
	if (bindStdOut)
	{
		std::wcout.clear();
		std::cout.clear();
	}
	if (bindStdErr)
	{
		std::wcerr.clear();
		std::cerr.clear();
	}
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

#ifdef _DEBUG
	// Allocate a console window for this process
	AllocConsole();

	// Update the C/C++ runtime standard input, output, and error targets to use the console window
	BindCrtHandlesToStdHandles(true, true, true);

	std::clog << "Starting Palm Engine" << std::endl;
#endif

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