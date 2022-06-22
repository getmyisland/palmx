#include <Windows.h>
#include <iostream>
#include <string>

#include "../SystemManager.h"

char KeyInputToHex(wchar_t wchar) {
#ifdef _DEBUG
	std::clog << wchar << std::endl;
#endif

	wchar_t wideChar = printf("0x%x", wchar);

#ifdef _DEBUG
	std::clog << wideChar << std::endl;
#endif

	std::string str = "";
	str.assign(wideChar, 4);

#ifdef _DEBUG
	std::clog << str << std::endl;
#endif

	return 'A';
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SYSKEYDOWN:
	{
		// Send an input event to the input manager
		SystemManager::getInstance().getInputSystem().ProcessKeyInput(KeyInput(KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_DOWN, KeyInputToHex(wParam)));

		break;
	}
	case WM_SYSKEYUP:
	{
		// Send an input event to the input manager
		SystemManager::getInstance().getInputSystem().ProcessKeyInput(KeyInput(KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_UP, KeyInputToHex(wParam)));

		break;
	}
	case WM_SYSCHAR:
	{
		break;
	}
	case WM_KEYDOWN:
	{
		// Send an input event to the input manager
		SystemManager::getInstance().getInputSystem().ProcessKeyInput(KeyInput(KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_DOWN, KeyInputToHex(wParam)));

		break;
	}
	case WM_KEYUP:
	{
		// Send an input event to the input manager
		SystemManager::getInstance().getInputSystem().ProcessKeyInput(KeyInput(KeyInput::KeyInputType::INPUT_KEYBOARD_KEY_UP, KeyInputToHex(wParam)));

		break;
	}
	case WM_CHAR:
	{

		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		break;
	}
	default: { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}