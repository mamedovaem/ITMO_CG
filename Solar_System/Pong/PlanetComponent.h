#pragma once
#include "SphereComponent.h"

class PlanetComponent: public SphereComponent
{
public:
//	Planet* rotationCenter;

	float orbitRadius = 0.0f;
//	float spinSpeed = 0.0f;
	float orbitAngularSpeed = 0.0f;
	float angle = 0.0f;

	PlanetComponent(D3DApp* app, float radius, DirectX::XMFLOAT4 color, 
	 float orbRadius, float orbAngSpeed /*float spSpeed*/) :
		SphereComponent(app, radius, color)
	{
		orbitRadius = orbRadius;
		orbitAngularSpeed = orbAngSpeed;
		//Planet1->transform.position.x = orbitRadius;
		//spinSpeed = spSpeed;
	}

	virtual void Update(float deltaTime) override;

};