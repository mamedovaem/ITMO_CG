#include "MyApp.h"

bool MyApp::Init()
{
	if (!D3DApp::Init())
		return false;
	else
		return true;

}

void MyApp::OnResize()
{
	D3DApp::OnResize();
}

 void MyApp::UpdateScene(float dt)
{
	
}

void MyApp::DrawScene()
{
	assert(md3dImmediateContext);
	assert(mSwapChain);
	
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView,
		reinterpret_cast<const float*>(&DirectX::Colors::CornflowerBlue));

	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	HR(mSwapChain->Present(0, 0));

#pragma region VertexStage
	
	VertexOut VS(float4 Pos : POSITION, float4 Color : COLOR) {}

	struct Vertex
	{
		DirectX::XMFLOAT4 Pos;
		DirectX::XMFLOAT4 Color;
	};

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,0,
		D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16,
		D3D11_INPUT_PER_VERTEX_DATA, 0}
	}

		HRESULT ID3D11Device::CreateInputLayout(
			const D3D11_INPUT_ELEMENT_DESC * vertexDesc,
			UINT 27,
			const void* D3D11VertexShader,

		)
#pragma endregion

}
