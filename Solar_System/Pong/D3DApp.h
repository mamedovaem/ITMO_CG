#pragma once
#include "Libs.h"
#include "Win32App.h"

class SceneComponent;
class CameraComponent;

struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProj;
};

struct LightBuffer
{
	DirectX::XMFLOAT3 direction;
	float ambient;

	DirectX::XMFLOAT4 cameraPos;
};

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
	D3D11_VIEWPORT viewport;

	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* lightBuffer;

	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;

	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;

	CameraComponent* camera;
	std::vector<SceneComponent*> components;

	bool isResourcesAlloced = false;
	
	D3DApp();
	//~D3DApp();
	HRESULT Initialize();
	bool Render();
	bool DestroyResources();

	HRESULT InitDeviceAndSwapChain();
	HRESULT InitDepthStencil();
	HRESULT InitViewport();
	HRESULT InitRastState();
	HRESULT InitInputLayout();
	HRESULT InitConstantBuffers();

//	void SetMatrixes();
//	void UpdateMatrixes();

	HRESULT CompileShaders();
	HRESULT CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
};
