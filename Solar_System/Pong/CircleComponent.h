#pragma once
#include "GameComponent.h"

class CircleComponent: public RenderComponent
{
public:
	//D3DApp* app;
	DirectX::XMFLOAT4 center;

	float radius;
	int sideNum = 36;

	bool isResourcesAlloced = false;

	CircleComponent() {}
	CircleComponent(D3DApp* app, float radius = 0.1, DirectX::XMFLOAT4 center = { 0.4f, 0.2f, 0.0f, 1.0f},
		 DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 0.5f, 1.0f })
	{
		this->app = app;
		this->center = center;
		this->radius = radius;
		this->color = color;

		GenerateGeometry();
		AllocResources();
	}

	void GenerateGeometry();
	
	HRESULT  AllocResources() override;
	HRESULT DestroyResources() override;
	void Draw() override;



};