#pragma once
#include "GameComponent.h"


class RectComponent : public GameComponent
{
public:
	//D3DApp* app;

	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT4 color;

	float length;
	float width;

	bool isResourcesAlloced = false;

	RectComponent(D3DApp* app, float length = 0.4, float width = 0.1,
		DirectX::XMFLOAT2 pos = { -0.5f, -0.5f },
		DirectX::XMFLOAT4 color = { 0.2f, 1.0f, 0.4f, 1.0f })
	{
		this->app = app;
		this->color = color;
		cbColor = ConstantBufferColor{ color };
		this->pos = pos;
		this->length = length;
		this->width = width;

		float x0 = -length / 2;
		float x1 = length / 2;
		float y0 = -width / 2;
		float y1 = width / 2;

		const float center_z = 0.5;
		const float center_w = 1;

		DirectX::XMFLOAT4 vertex = { x0, y0, center_z, 1.f };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x0, y1, center_z, center_w };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x1, y1, center_z, center_w };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x1, y0, center_z, center_w };
		vertices.push_back(vertex);
		vertices.push_back(color);

		int indices_temp[] = { 0, 1, 2, 2, 3, 0 };
		for (int i = 0; i < 6; i++)
		{
			indices.push_back(indices_temp[i]);
		}

		AllocResources();
	}

	HRESULT AllocResources();
	HRESULT DestroyResources() override;
	void Draw() override;
};