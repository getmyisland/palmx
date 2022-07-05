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
		const wchar_t* GetWindowName() override;
		void SetWindowName(const wchar_t* p_wszNewText) override;
		const wchar_t* GetWindowClassName() override;

		int GetPosX() override;
		int GetPosY() override;
		void SetPos(int p_nPosX, int p_nPosY) override;

		int GetWidth() override;
		int GetHeight() override;
		void SetSize(int p_nWidth, int p_nHeight) override;
		DWORD GetDwStyle() override;
		void SetDwStyle(DWORD p_dwNewStyle) override;

		// Inherited members via Panel
		// Name of the window
		const wchar_t* m_wszWindowText = L"Default Window";

		// Name of the window class !UNIQUE!
		const wchar_t* m_wszWindowClassText = L"Default Window Class";

		DWORD m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
		
		// X and Y position
		int m_nPosX = 0;
		int m_nPosY = 0;

		// Width and height of window
		int m_nWidth = 1280;
		int m_nHeight = 720;
	};
}

#endif // GUI_CONTROLS_FRAME_H