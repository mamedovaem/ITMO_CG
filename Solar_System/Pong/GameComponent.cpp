#include "GameComponent.h"


HRESULT GameComponent::SetBuffers()
{
	HRESULT res = S_OK;
	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * vertices.size();

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices.data();
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	res = app->device->CreateBuffer(&vertexBufDesc, &vertexData, &vertexBuffer);

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * indices.size();

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices.data();
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	res = app->device->CreateBuffer(&indexBufDesc, &indexData, &indexBuffer);

	D3D11_BUFFER_DESC constantBufDesc = {};
	constantBufDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufDesc.MiscFlags = 0;
	constantBufDesc.StructureByteStride = 0;
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);

//	std::cout << sizeof(ConstantBuffer);

	D3D11_SUBRESOURCE_DATA constBufData = {};
	constBufData.pSysMem = &matrixes;
	constBufData.SysMemPitch = 0;
	constBufData.SysMemSlicePitch = 0;

	res = app->device->CreateBuffer(&constantBufDesc,&constBufData, &constantBuffer);
	app->context->VSSetConstantBuffers(0, 1, &constantBuffer);

	return res;
}

HRESULT GameComponent::SetShaders()
{
	HRESULT res = S_OK;

	res = CompileShaderFromFile(L"C:/Users/User/Desktop/New_CG/Solar_System/Pong/Shaders/VertexShader.hlsl", "VSMain", "vs_5_0", &vertexShaderByteCode);
	res = CompileShaderFromFile(L"C:/Users/User/Desktop/New_CG/Solar_System/Pong/Shaders/VertexShader.hlsl", "PSMain", "ps_5_0", &pixelShaderByteCode);

	res = app->device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	res = app->device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	return res;
}

HRESULT GameComponent::SetInputLayout()
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
			0}
	};

	res = app->device->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		&layout);

	app->context->IASetInputLayout(layout);

	return res;
}

void GameComponent::SetMatrixes()
{
	matrixes.mWorld = DirectX::XMMatrixIdentity();

	app->context->VSSetConstantBuffers(0, 1, &constantBuffer);
	//UpdateMatrixes();
	DirectX::XMVECTOR Eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);  // Where are we looking from

	DirectX::XMVECTOR At = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);    // Where are we looking at

	DirectX::XMVECTOR Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);    // Up direction

	matrixes.mView = DirectX::XMMatrixLookAtLH(Eye, At, Up);
	matrixes.mProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, app->ClientWidth / (FLOAT)app->ClientHeight, 0.01f, 100.0f);
}


void GameComponent::UpdateMatrixes()
{
	D3D11_MAPPED_SUBRESOURCE mss;
	app->context->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mss);
	memcpy(mss.pData, &matrixes, sizeof(matrixes));
	app->context->Unmap(constantBuffer, 0);
}

HRESULT GameComponent::CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut)
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
			MessageBox(app->hWnd, fileName, L"Missing Shader File", MB_OK);
		}

	}

	if (errorCode) errorCode->Release();

	return res;
}