#include "CInputSystem.h"
#include <iostream>
#include <Windows.h>

HHOOK hHookKeyboard{ NULL };
HHOOK hHookMouse{ NULL };

int shift_active() {
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active() {
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}

// See https://docs.microsoft.com/de-de/windows/win32/winmsg/lowlevelkeyboardproc
LRESULT CALLBACK keyboard_hook(const int nCode, const WPARAM wParam, const LPARAM lParam) {
	switch (wParam) {
	case (WM_KEYDOWN): {
			KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
			DWORD wVirtKey = kbdStruct->vkCode;
			DWORD wScanCode = kbdStruct->scanCode;

			BYTE lpKeyState[256];
			GetKeyboardState(lpKeyState);

			char result;
			ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
			std::cout << result << std::endl;
			break;
		}
	}

	return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
}

// See https://docs.microsoft.com/de-de/windows/win32/winmsg/lowlevelmouseproc
LRESULT CALLBACK mouse_hook(const int nCode, const WPARAM wParam, const LPARAM lParam) {
	switch (wParam) {
	case (WM_MOUSEMOVE): {
		std::cout << "Mouse is moving" << std::endl;
	}
	}
	
	return CallNextHookEx(hHookKeyboard, nCode, wParam, lParam);
}

void CInputSystem::Init() {
	hHookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	hHookMouse = SetWindowsHookEx(WH_MOUSE_LL, mouse_hook, NULL, 0);
}

void CInputSystem::Update() {
	
}

void CInputSystem::Shutdown() {
	
}

void CInputSystem::OnEvent(SystemEvent sysEvent)
{
}
