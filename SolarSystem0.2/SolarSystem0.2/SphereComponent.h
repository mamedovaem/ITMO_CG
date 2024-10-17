#pragma once
#pragma once
#include "GameComponent.h"

class SphereComponent : public GameComponent
{
public:
	//D3DApp* app;
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;

	float radius;
	int sideNum = 36;

	bool isResourcesAlloced = false;

	SphereComponent(D3DApp* app, float radius = 0.1, DirectX::XMFLOAT3 pos = { 0.4f, 0.2f , 0.5},
		DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 0.5f, 1.0f })
	{
		this->app = app;
		this->pos = pos;
		this->radius = radius;
		this->color = color;
		cbColor = ConstantBufferColor{ color };

		GenerateGeometry();
		AllocResources();
	}

	void GenerateGeometry();

	HRESULT AllocResources() override;
	HRESULT DestroyResources() override;
	void Draw() override;
};