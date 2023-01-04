#ifndef SWAP_CHAIN_H
#define SWAP_CHAIN_H
#ifdef _WIN32
#pragma once
#endif

#include "../graphics/GraphicModule.h"

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Init(gui_controls::Panel* p_pPanel);
	bool Release();

private:
	IDXGISwapChain* m_pDxgiSwapChain;
};

#endif // SWAP_CHAIN_H