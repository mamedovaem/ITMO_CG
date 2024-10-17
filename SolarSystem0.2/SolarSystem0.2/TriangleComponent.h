#pragma once
#include "GameComponent.h"

class TriangleComponent : public GameComponent
{
public:
	//D3DApp* app;
	bool isResourcesAlloced = false;
	DirectX::XMFLOAT4 color;

	TriangleComponent()
	{

	}

	TriangleComponent(D3DApp* app, DirectX::XMFLOAT4 first = { 0.5f, 0.5f, 0.5f, 1.0f },
		DirectX::XMFLOAT4 second = { -0.5f, -0.5f, 0.5f, 1.0f },
		DirectX::XMFLOAT4 third = { 0.5f, -0.5f, 0.5f, 1.0f },
		DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 1.0f, 1.0f })
	{
		this->app = app;
		this->color = color;
		cbColor = ConstantBufferColor{ color };

		vertices.push_back(first);
		vertices.push_back(color);
		vertices.push_back(second);
		vertices.push_back(color);
		vertices.push_back(third);
		vertices.push_back(color);

		for (int i = 0; i < 3; i++)
		{
			indices.push_back(i);
		}

		AllocResources();
	}

	HRESULT AllocResources();
	HRESULT DestroyResources() override;
	void Draw() override;
};