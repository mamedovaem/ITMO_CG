#include "D3DApp.h"

D3DApp::D3DApp()
{
	Initialize();
	isResourcesAlloced = true;
}

HRESULT D3DApp::Initialize()
{ 
	HRESULT res = S_OK;
	
	res = SetDeviceAndSwapChain();
	res = SetViewport();
	res = SetRastState();

	return res;
}

HRESULT D3DApp::SetDeviceAndSwapChain()
{
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = ClientWidth;
	swapDesc.BufferDesc.Height = ClientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;


	HRESULT res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(res))
	{
		// Well, that was unexpected
	}

	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)

	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);

	return res;
}

HRESULT D3DApp::SetDepthStencil()
{
	D3D11_TEXTURE2D_DESC descDepth{ };

	descDepth.Width = ClientWidth;

	descDepth.Height = ClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; 
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	HRESULT res = S_OK;

	res = device->CreateTexture2D(&descDepth, NULL, &depthStencil);

	if (FAILED(res)) return res;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};

	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	res = device->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView);

	if (FAILED(res)) return res;

	return res;
}

bool D3DApp::DestroyResources()
{

	if (isResourcesAlloced)
	{
		
			for (auto c : components)
			{
				if(c)
					c->DestroyResources();
			}
			components.clear();


	if (context)
			context->ClearState();
	
	if (rastState)
		rastState->Release();

	 if (backTex)
		 backTex->Release();
	 
	 if (rtv)
		 rtv->Release();

	 if (swapChain) 
		swapChain->Release();

	 if (context) 
		context->Release();

	 if (device) 
		device->Release();
	}

	isResourcesAlloced = false;

	return true;
}

bool D3DApp::Render()
{
	float ClearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	 context->OMSetRenderTargets(1, &rtv, depthStencilView);
	 context->ClearRenderTargetView(rtv, ClearColor);
	

	 for (auto c : components)
	 {
		 c->Draw();
	 }
	 context->OMSetRenderTargets(0, nullptr, depthStencilView);
	// Вывести в передний буфер (на экран) информацию, нарисованную в заднем буфере.
	 swapChain->Present(1, 0);

	return true;
}

HRESULT D3DApp::SetRastState()
{
	HRESULT res = S_OK;

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	res = device->CreateRasterizerState(&rastDesc, &rastState);

	context->RSSetState(rastState);

	return res;
}

HRESULT D3DApp::SetViewport()
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(ClientWidth);
	viewport.Height = static_cast<float>(ClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);

	return S_OK;
}