#pragma once

#include <Windows.h>
#include <vector>
#include <iostream>

class Panel
{
public:
	// Constructor
	Panel(HINSTANCE* hInst, const wchar_t* pWindowName); // Root only constructor
	Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName);

	~Panel();

	// Getters
	HWND* GetPanel() { return &hwnd; }

	Panel* GetParent() { return p_Parent; }

	Panel* GetChild(int index) {
		if (index > ((int)childPanels.size() - 1)) {
			return nullptr;
		}
		else {
			return childPanels[index];
		}
	}

	int GetChildCount() {
		return (int)childPanels.size();
	}

	const wchar_t* GetWindowName() { return windowName; }
	const wchar_t* GetWindowClassName() { return windowClassName; }

	UINT GetStyle() { return style; }

	DWORD GetDwExStyle() { return dwExStyle; }
	DWORD GetDwStyle() { return dwStyle; }

	int GetPosX() { return posX; }
	int GetPosY() { return posY; }

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	// Setters
	void SetNewParent(Panel* newParent) {
		p_Parent = newParent;
		SetParent(hwnd, *p_Parent->GetPanel());
	}

	static LRESULT CALLBACK StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const HINSTANCE* p_hInstance = nullptr;
	HWND hwnd = nullptr;

	Panel* p_Parent = nullptr;
	std::vector<Panel*> childPanels;

	const wchar_t* windowName = L"Default Window";
	const wchar_t* windowClassName = L"Default Window Class";

	UINT style = CS_HREDRAW | CS_VREDRAW;

	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_CHILD | WS_CAPTION;

	int posX = 0;
	int posY = 0;

	int width = 1280;
	int height = 720;

	void RegisterWindowClass();
	HWND CreateWindowHandle();
	HWND CreateWindowHandleWithParent();
	void ShowWindowHandle();

	LRESULT CALLBACK RealWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};