#include "SwapChain.h"
#include "../Modules.h"
#include "GraphicModule.h"

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

bool SwapChain::Init(gui_controls::Panel* p_pPanel)
{
	ID3D11Device* device = Modules::g_GraphicModule.m_pDevice;
	DXGI_SWAP_CHAIN_DESC d3d11Desc;
	ZeroMemory(&d3d11Desc, sizeof(d3d11Desc));
	d3d11Desc.BufferCount = 1;
	d3d11Desc.BufferDesc.Width = p_pPanel->GetWidth();
	d3d11Desc.BufferDesc.Height = p_pPanel->GetHeight();
	d3d11Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3d11Desc.BufferDesc.RefreshRate.Numerator = 60;
	d3d11Desc.BufferDesc.RefreshRate.Denominator = 1;
	d3d11Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	d3d11Desc.OutputWindow = *p_pPanel->GetHandle();
	d3d11Desc.SampleDesc.Count = 1;
	d3d11Desc.SampleDesc.Quality = 0;
	d3d11Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	d3d11Desc.Windowed = TRUE;

	HRESULT result = Modules::g_GraphicModule.m_pDgxiFactory->CreateSwapChain(device, &d3d11Desc, &m_pDxgiSwapChain);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool SwapChain::Release()
{
	m_pDxgiSwapChain->Release();
	delete this;
	return true;
}
