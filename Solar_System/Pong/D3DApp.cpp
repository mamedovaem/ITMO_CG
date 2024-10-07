#include "D3DApp.h"
#include "RenderComponent.h"
#include "CameraComponent.h"

D3DApp::D3DApp()
{
	Initialize();
	isResourcesAlloced = true;
}

HRESULT D3DApp::Initialize()
{ 
	HRESULT res = S_OK;
	
	res = InitDeviceAndSwapChain();
	res = InitDepthStencil();
	res = InitViewport();
	res = InitRastState();
	res = CompileShaders();
	res = InitInputLayout();
	res = InitConstantBuffers();

	camera = new CameraComponent();
	camera->transform.position.z = -5.0f;

	return res;
}

HRESULT D3DApp::InitDeviceAndSwapChain()
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

HRESULT D3DApp::InitDepthStencil()
{
	D3D11_TEXTURE2D_DESC descDepth{};
	backTex->GetDesc(&descDepth);
	descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	HRESULT res = S_OK;

	res = device->CreateTexture2D(&descDepth, NULL, &depthStencil);

	if (FAILED(res)) return res;

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};

	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	res = device->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView);

	if (FAILED(res)) return res;

	context->OMSetRenderTargets(1, &rtv, depthStencilView);
	return res;
}

bool D3DApp::DestroyResources()
{
	if (isResourcesAlloced)
	{
		for (auto c : components)
		{
			if (RenderComponent* rc = dynamic_cast<RenderComponent*>(c))
			{
				rc->DestroyResources();
			}

			delete c;
		}

		components.clear();

		delete camera;

		if (constantBuffer)
			constantBuffer->Release();
		if (layout)
			layout->Release();
		if (vertexShader)
			vertexShader->Release();
		if (vertexShaderByteCode)
			vertexShaderByteCode->Release();
		if (pixelShader)
			pixelShader->Release();
		if (pixelShaderByteCode)
			pixelShaderByteCode->Release();

		if (context) {
			context->ClearState();
		}

		if (rastState) {
			rastState->Release();
		}

		if (depthStencilView)
		{
			depthStencilView->Release();
		}

		if (backTex)
		{
			backTex->Release();
		}

		if (depthStencil)
		{
			depthStencil->Release();
		}

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
	context->ClearState();

	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	context->OMSetRenderTargets(1, &rtv, depthStencilView); // depthStencilView
	context->ClearRenderTargetView(rtv, ClearColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	context->RSSetState(rastState);
	context->RSSetViewports(1, &viewport);

	//bind shaders
	context->VSSetShader(vertexShader, NULL, 0);
	context->PSSetShader(pixelShader, NULL, 0);
	
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->PSSetConstantBuffers(1, 1, &lightBuffer);

	context->IASetInputLayout(layout);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//app->context->PSSetConstantBuffers(0, 1, &constantBuffer);
	
	LightBuffer lights;

	lights.direction = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	lights.ambient = 0.1f;

	lights.cameraPos = DirectX::XMFLOAT4(camera->transform.position.x, camera->transform.position.y,
		camera->transform.position.z, 1.0f);

	D3D11_MAPPED_SUBRESOURCE mss;
	context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mss);
	memcpy(mss.pData, &lights, sizeof(lights));
	context->Unmap(lightBuffer, 0);

	ConstantBuffer matrixes;
	
	camera->aspectRatio = ClientWidth / (FLOAT)ClientHeight;

	matrixes.mView = camera->transform.GetViewMatrix();
	matrixes.mProj = camera->GetProjMatrix();

	for (auto c : components)
	{
		if (RenderComponent* rc = dynamic_cast<RenderComponent*>(c))
		{
			matrixes.mWorld = rc->transform.GetWorldMatrix();

			context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mss);
			memcpy(mss.pData, &matrixes, sizeof(matrixes));
			context->Unmap(constantBuffer, 0);

			rc->Draw();
		}
	}

	context->OMSetRenderTargets(0, nullptr, nullptr);
	// Вывести в передний буфер (на экран) информацию, нарисованную в заднем буфере.
	swapChain->Present(0, 0);

	return true;
}

HRESULT D3DApp::InitRastState()
{
	HRESULT res = S_OK;

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE; //TODO: change to default
	rastDesc.FillMode = D3D11_FILL_SOLID;
	res = device->CreateRasterizerState(&rastDesc, &rastState);

	//context->RSSetState(rastState);

	return res;
}

HRESULT D3DApp::InitViewport()
{
	viewport.Width = static_cast<float>(ClientWidth);
	viewport.Height = static_cast<float>(ClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;

	//context->RSSetViewports(1, &viewport);

	return S_OK;
}

HRESULT D3DApp::InitInputLayout()
{
	HRESULT res = S_OK;

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	res = device->CreateInputLayout(
		inputElements,
		3,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		&layout);

	//context->IASetInputLayout(layout);

	return res;
}

HRESULT D3DApp::InitConstantBuffers()
{
	HRESULT res;

	D3D11_BUFFER_DESC constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);

	//	std::cout << sizeof(ConstantBuffer);

	/*D3D11_SUBRESOURCE_DATA constBufData = {};
	constBufData.pSysMem = &matrixes;
	constBufData.SysMemPitch = 0;
	constBufData.SysMemSlicePitch = 0;*/

	res = device->CreateBuffer(&constantBufDesc, /*&constBufData*/ nullptr, &constantBuffer);

	constantBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(LightBuffer);

	res = device->CreateBuffer(&constantBufDesc, /*&constBufData*/ nullptr, &lightBuffer);

	return res;
}

HRESULT D3DApp::CompileShaders()
{
	HRESULT res = S_OK;

	res = CompileShaderFromFile(L"Shaders/VertexShader.hlsl", "VSMain", "vs_5_0", &vertexShaderByteCode);
	res = CompileShaderFromFile(L"Shaders/VertexShader.hlsl", "PSMain", "ps_5_0", &pixelShaderByteCode);

	res =device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	res =device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	return res;
}

HRESULT D3DApp::CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut)
{
	HRESULT res = S_OK;

	ID3DBlob* errorCode = nullptr;
	res = D3DCompileFromFile(fileName,
		nullptr /*macros*/,
		nullptr /*include*/,
		entryPoint,
		shaderModel,
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		blobOut,
		&errorCode);

	if (FAILED(res))
	{
		// If the shader failed to compile it should have written something to the error message.
		if (errorCode) {
			char* compileErrors = (char*)(errorCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hWnd, fileName, L"Missing Shader File", MB_OK);
		}

	}

	if (errorCode) errorCode->Release();

	return res;
}


//void D3DApp::SetMatrixes()
//{
//	//matrixes.mWorld = DirectX::XMMatrixIdentity();
//
//	 context->VSSetConstantBuffers(0, 1, &constantBuffer);
//	//UpdateMatrixes();
//	/*DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);  // Where are we looking from
//
//	DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);    // Where are we looking at
//
//	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);    // Up direction
//
//	matrixes.mView = DirectX::XMMatrixLookAtLH(Eye, At, Up); */
//	matrixes.mWorld = transform.GetWorldMatrix();
//	matrixes.mView = transform.GetViewMatrix();
//	
//}
//
//
//void D3DApp::UpdateMatrixes()
//{
//	D3D11_MAPPED_SUBRESOURCE mss;
//	context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mss);
//	memcpy(mss.pData, &matrixes, sizeof(matrixes));
//	context->Unmap(constantBuffer, 0);
//}