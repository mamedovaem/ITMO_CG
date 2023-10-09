#pragma once
#include "GameComponent.h"

class CircleComponent: public GameComponent
{
public:
	//D3DApp* app;
	DirectX::XMFLOAT2 pos;

	float radius;
	int sideNum = 36;

	bool isResourcesAlloced = false;

	CircleComponent(D3DApp* app, float radius = 0.1, DirectX::XMFLOAT2 pos = { 0.4f, 0.2f },
		 DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 0.5f, 1.0f })
	{
		this->app = app;
		this->pos = pos;
		this->radius = radius;
		this->color = color;

		GenerateGeometry();
		AllocResources();
	}

	void GenerateGeometry();
	
	HRESULT AllocResources() override;
	HRESULT DestroyResources() override;
	void Draw() override;
};