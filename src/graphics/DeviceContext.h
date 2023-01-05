#ifndef DEVICE_CONTEXT_H
#define DEVICE_CONTEXT_H
#ifdef _WIN32
#pragma once
#endif

#include <d3d11.h>
#include "SwapChain.h"

class SwapChain;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* p_pDeviceContext);
	~DeviceContext();

	bool ClearRenderTargetColor(SwapChain* p_pSwapChain, float p_fpRed, float p_fpGreen, float p_fpBlue, float p_fpAlpha);
	bool Release();

private:
	ID3D11DeviceContext* m_pD3D11DeviceContext;
};

#endif // DEVICE_CONTEXT_H