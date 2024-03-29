#pragma once
#include "Libs.h"
#include "D3DApp.h"


struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mViewProj;
};

class D3DApp;

class GameComponent
{
public:
	D3DApp* app;

	std::vector<DirectX::XMFLOAT4> vertices;
	std::vector<int> indices;
	ConstantBuffer matrixes;

	DirectX::XMFLOAT4 color;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constantBuffer;

	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;

	virtual HRESULT AllocResources() = 0;
	virtual void Draw() = 0;
	//virtual void Update() = 0;
	virtual HRESULT DestroyResources() = 0;

	HRESULT SetBuffers();
	HRESULT SetShaders();
	void SetMatrixes();
	void UpdateMatrixes();
	HRESULT SetInputLayout();

	HRESULT CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
};
