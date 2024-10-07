#pragma once
#include "GameComponent.h"


class RectComponent : public RenderComponent
{
public:
	//D3DApp* app;

	DirectX::XMFLOAT4 center;
	float length;
	float width; 

	bool isResourcesAlloced = false;

	RectComponent()
	{

	}

	RectComponent(D3DApp* app, float length = 0.4, float width = 0.1,
		DirectX::XMFLOAT4 center = { -0.5f, -0.5f, 0.5f, 1.0f },
		DirectX::XMFLOAT4 color = { 0.2f, 1.0f, 0.4f, 1.0f })
	{
		this->app = app;
		this->color = color;
		this->center = center;
		this->length = length;
		this->width = width;

		float x0 = center.x - length / 2;
		float x1 = center.x + length / 2;
		float y0 = center.y - width / 2;
		float y1 = center.y + width / 2;


		DirectX::XMFLOAT4 vertex = { x0, y0, center.z, center.w };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x0, y1, center.z, center.w };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x1, y1, center.z, center.w };
		vertices.push_back(vertex);
		vertices.push_back(color);
		vertex = { x1, y0, center.z, center.w };
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
