#include "InputCollector.h"
#include <iostream>

InputCollector::InputCollector(InputMapper* inputMapper) { inputMapper = p_InputMapper; };
InputCollector::~InputCollector() {};

InputCollector* p_InputCollector = nullptr;

HHOOK hHookKeyboard{ NULL };
HHOOK hHookMouse{ NULL };

// See https://docs.microsoft.com/de-de/windows/win32/winmsg/lowlevelkeyboardproc
LRESULT CALLBACK keyboard_hook(const int nCode, const WPARAM wParam, const LPARAM lParam) {
	switch (wParam) {
	case (WM_KEYDOWN): {
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		p_InputCollector->SendKeyboardInputToInputMapper(wVirtKey);

		break;
	}
	case (WM_KEYUP): {
		break;
	}
	case(WM_SYSKEYDOWN): {
		break;
	}
	case (WM_SYSKEYUP): {
		break;
	}
	}

	return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
}

// See https://docs.microsoft.com/de-de/windows/win32/winmsg/lowlevelmouseproc
LRESULT mouse_hook(const int nCode, const WPARAM wParam, const LPARAM lParam)
{
	switch (wParam) {
	case (WM_LBUTTONDOWN): {
		break;
	}
	case (WM_LBUTTONUP): {
		break;
	}
	case (WM_RBUTTONDOWN): {
		break;
	}
	case (WM_RBUTTONUP): {
		break;
	}
	case (WM_MOUSEWHEEL): {
		break;
	}
	case (WM_MOUSEMOVE): {
		break;
	}
	}

	return CallNextHookEx(hHookMouse, nCode, wParam, lParam);
}

void InputCollector::EnableLowLevelHooks()
{
	p_InputCollector = this;

	hHookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, nullptr, 0);
	hHookMouse = SetWindowsHookEx(WH_MOUSE_LL, mouse_hook, nullptr, 0);
}

void InputCollector::SendKeyboardInputToInputMapper(DWORD wVirtKey) {
	p_InputMapper->MapKeyboardInputToAction(wVirtKey);
}