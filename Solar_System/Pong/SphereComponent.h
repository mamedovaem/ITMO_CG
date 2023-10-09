//Written by Frank D. Luna

#pragma once
#include "GameComponent.h"


class SphereComponent : public GameComponent
{
public:
	float radius;

	bool isResourcesAlloced = false;
	
	SphereComponent(D3DApp* app, float radius, DirectX::XMFLOAT4 color)
	{ 
		this->app = app;
		this->radius = radius;
		this->color = color;

		CreateSphere(radius, 36, 36);
		AllocResources();

	}
	void CreateSphere(float radius, int sliceCount, int stackCount);	
	
	HRESULT AllocResources() override;
	HRESULT DestroyResources() override;
	void Draw() override;
};
