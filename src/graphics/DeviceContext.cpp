#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* p_pDeviceContext)
{
	m_pD3D11DeviceContext = p_pDeviceContext;
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::ClearRenderTargetColor(SwapChain* p_pSwapChain, float p_fpRed, float p_fpGreen, float p_fpBlue, float p_fpAlpha)
{
	FLOAT clearColor[] = { p_fpRed, p_fpGreen, p_fpBlue, p_fpAlpha };

	m_pD3D11DeviceContext->ClearRenderTargetView(p_pSwapChain->m_pID3D11RenderTargetView, clearColor);

	return false;
}

bool DeviceContext::Release()
{
	m_pD3D11DeviceContext->Release();
	delete this;
	return true;
}
