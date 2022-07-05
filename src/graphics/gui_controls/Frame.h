#ifndef GUI_CONTROLS_FRAME_H
#define GUI_CONTROLS_FRAME_H
#ifdef _WIN32
#pragma once
#endif

#include "EditablePanel.h"
#include <Windows.h>

namespace gui_controls {
	class Frame : public EditablePanel {
	public:
		Frame(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText); // Standard
		Frame(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle);
		Frame(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight);
		Frame(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight); // Complete Constructor
		~Frame();

		// Inherited methods via Panel
		DWORD GetDwStyle() override;
		void SetDwStyle(DWORD p_dwNewStyle) override;

		// Inherited members via Panel
		DWORD m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

		LRESULT CALLBACK RealWndProc(HWND m_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // GUI_CONTROLS_FRAME_H