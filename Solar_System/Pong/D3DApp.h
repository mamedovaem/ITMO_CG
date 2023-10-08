#pragma once
#include "Libs.h"
#include "Win32App.h"
#include "GameComponent.h"

class GameComponent;

class D3DApp : public Win32App
{
public:
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;

	ID3D11Texture2D* backTex;
	ID3D11Texture2D* depthStencil;
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rastState;
	D3D11_VIEWPORT* viewport;

	std::vector<GameComponent*> components;

	bool isResourcesAlloced = false;
	
	D3DApp();
	//~D3DApp();
	HRESULT Initialize();
	bool Render();
	bool DestroyResources();
	HRESULT SetDeviceAndSwapChain();
	HRESULT SetDepthStencil();
	HRESULT  SetViewport();
	HRESULT SetRastState();

};
