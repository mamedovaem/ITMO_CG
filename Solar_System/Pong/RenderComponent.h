#pragma once
#include "Libs.h"
#include "D3DApp.h"
#include "SceneComponent.h"


class D3DApp;

class RenderComponent : public SceneComponent
{
public:

	D3DApp* app;

	std::vector<DirectX::XMFLOAT4> vertices;
	std::vector<int> indices;


	DirectX::XMFLOAT4 color;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	virtual HRESULT AllocResources() = 0;
	virtual void Draw() = 0;
	//virtual void Update() = 0;
	virtual HRESULT DestroyResources() = 0;

	HRESULT SetBuffers();




};
