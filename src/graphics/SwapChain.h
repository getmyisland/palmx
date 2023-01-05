#ifndef SWAP_CHAIN_H
#define SWAP_CHAIN_H
#ifdef _WIN32
#pragma once
#endif

#include "../graphics/GraphicModule.h"

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Init(gui_controls::Panel* p_pPanel);
	bool Present(bool p_bVSync);
	bool Release();

private:
	IDXGISwapChain* m_pDxgiSwapChain;
	ID3D11RenderTargetView* m_pID3D11RenderTargetView;

	friend class DeviceContext;
};

#endif // SWAP_CHAIN_H