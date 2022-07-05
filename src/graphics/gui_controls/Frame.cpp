#include "Frame.h"
#include <iostream>

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_dwStyle = p_dwStyle;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

gui_controls::Frame::Frame(HINSTANCE* p_hInstance, gui_controls::Panel* p_ParentPanel, const wchar_t* p_wszWindowText, DWORD p_dwStyle, int p_nPosX, int p_nPosY, int p_nWidth, int p_nHeight) {
	m_phInstance = p_hInstance;

	if (m_phInstance == nullptr) {
		std::cout << "HINSTANCE is a nullptr" << std::endl;
		return;
	}

	m_pParentPanel = p_ParentPanel;
	m_wszWindowText = p_wszWindowText;
	m_wszWindowClassText = p_wszWindowText;
	m_dwStyle = p_dwStyle;
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;

	ConstructPanel();
}

gui_controls::Frame::~Frame() {};

const wchar_t* gui_controls::Frame::GetWindowName() {
	return m_wszWindowText;
}

void gui_controls::Frame::SetWindowName(const wchar_t* p_wszNewText) {
	m_wszWindowText = p_wszNewText;
	SetWindowText(m_hWnd, m_wszWindowText);
}

const wchar_t* gui_controls::Frame::GetWindowClassName() {
	return m_wszWindowClassText;
}

int gui_controls::Frame::GetPosX() {
	return m_nPosX;
}

int gui_controls::Frame::GetPosY() {
	return m_nPosY;
}

void gui_controls::Frame::SetPos(int p_nPosX, int p_nPosY) {
	m_nPosX = p_nPosX;
	m_nPosY = p_nPosY;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

int gui_controls::Frame::GetWidth() {
	return m_nWidth;
}

int gui_controls::Frame::GetHeight() {
	return m_nHeight;
}

void gui_controls::Frame::SetSize(int p_nWidth, int p_nHeight) {
	m_nWidth = p_nWidth;
	m_nHeight = p_nHeight;
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}

DWORD gui_controls::Frame::GetDwStyle() {
	return m_dwStyle;
}

void gui_controls::Frame::SetDwStyle(DWORD p_dwNewStyle) {
	m_dwStyle = p_dwNewStyle;
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
	SetWindowPos(m_hWnd, nullptr, m_nPosX, m_nPosY, m_nWidth, m_nHeight, SWP_FRAMECHANGED);
}