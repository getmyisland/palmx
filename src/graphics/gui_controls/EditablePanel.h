#ifndef GUI_CONTROLS_EDITABLE_PANEL_H
#define GUI_CONTROLS_EDITABLE_PANEL_H
#ifdef _WIN32
#pragma once
#endif

#include "Panel.h"

namespace gui_controls {
	class EditablePanel : public Panel {
	public:
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText); // Standard
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle);
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight);
		EditablePanel(HINSTANCE* p_hInstance, Panel* p_ParentPanel, const wchar_t* p_wszWindowText, UINT p_wStyle, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight); // Complete Constructor
		~EditablePanel();

		// Inherited methods via Panel
		UINT GetStyle() override;
		DWORD GetDwStyle() override;
		void SetDwStyle(DWORD p_dwNewStyle) override;

		// Inherited members via Panel
		UINT m_wStyle = CS_HREDRAW | CS_VREDRAW;
		DWORD m_dwStyle = WS_THICKFRAME | WS_CLIPCHILDREN;
	
	protected:
		EditablePanel() {};
	};
}

#endif // GUI_CONTROLS_EDITABLE_PANEL_H