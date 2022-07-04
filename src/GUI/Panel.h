#pragma once

#include <Windows.h>
#include <vector>

class Panel
{
public:
	/* === Constructor === */
	Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName); // Default
	Panel(HINSTANCE* hInst, Panel* parent, const wchar_t* pWindowName, UINT pStyle, DWORD pDwExStyle, DWORD pDwStyle, int pX, int pY, int pWidth, int pHeight); // Complete Constructor
	~Panel();

	/* === Methods === */
	void AddChild(Panel* childPanelToAdd) {
		childPanels.push_back(childPanelToAdd);
	}

	/* === Getter === */
	HWND* GetHandle() { return &hwnd; }

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

	/* === Setter === */
	void SetNewParent(Panel* newParent) {
		p_Parent = newParent;
		SetParent(hwnd, *p_Parent->GetHandle());
	}

	void SetWindowName(const wchar_t* newName) {
		windowName = newName;
		SetWindowText(hwnd, windowName);
	}

	void SetDwExStyle(DWORD newDwExStyle) {
		dwExStyle = newDwExStyle;
		SetWindowLong(hwnd, GWL_EXSTYLE, dwExStyle);
		SetWindowPos(hwnd, nullptr, posX, posY, width, height, SWP_FRAMECHANGED);
	}

	void SetDwStyle(DWORD newDwStyle) {
		dwStyle = newDwStyle;
		SetWindowLong(hwnd, GWL_STYLE, dwStyle);
		SetWindowPos(hwnd, nullptr, posX, posY, width, height, SWP_FRAMECHANGED);
	}

	void SetPos(int x, int y) {
		posX = x;
		posY = y;
		SetWindowPos(hwnd, nullptr, posX, posY, width, height, SWP_FRAMECHANGED);
	}

	void SetSize(int wide, int tall) {
		width = wide;
		height = tall;
		SetWindowPos(hwnd, nullptr, posX, posY, width, height, SWP_FRAMECHANGED);
	}

	/* === Static WndProc === */
	static LRESULT CALLBACK StaticWndProc(HWND pHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	// The instance of the engine
	const HINSTANCE* hInstance = nullptr;

	// The handle of the window
	HWND hwnd = nullptr;

	// Parent element
	Panel* p_Parent = nullptr;

	// List of child elements
	std::vector<Panel*> childPanels;

	// Name of the window
	const wchar_t* windowName = L"Default Window";

	// Name of the window class !UNIQUE!
	const wchar_t* windowClassName = L"Default Window Class";

	// Window styles
	UINT style = CS_HREDRAW | CS_VREDRAW;
	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_CHILD | WS_BORDER | WS_VISIBLE;

	// X and Y position
	int posX = 0;
	int posY = 0;

	// Width and height of window
	int width = 1280;
	int height = 720;

	void ConstructPanel();
	void RegisterWindowClass();
	HWND CreateWindowHandle();
	void ShowWindowHandle();

	// Custom window procedure
	LRESULT CALLBACK RealWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};