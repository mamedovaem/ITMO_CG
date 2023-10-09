#pragma once
#include "CircleComponent.h"
//#include "Collision.h"


class Ball : public CircleComponent
{
public:
	float velocityX{};
	float initialVelocityX = 1.5f;
	float velocityY{};
	float initialVelocityY = 0.0f;

	float multiplier = 1.05f;

	Ball(D3DApp* app, float radius = 0.1, DirectX::XMFLOAT2 center = { 0.0f, 0.0f },
		DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 0.5f, 1.0f }) : CircleComponent(app, radius, center, color) {
		velocityX = initialVelocityX;
		velocityY = initialVelocityY;
	}

	void Move(float deltaTime)
	{
		pos.x += velocityX * deltaTime;
		pos.y += velocityY * deltaTime;

		matrixes.mMVP = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
		UpdateMatrixes();

		float upBoundary = 1.0f - radius;
		float downBoundary = -1.0f + radius;
		if (pos.y >= upBoundary || pos.y <= downBoundary)
		{
			velocityY = -velocityY;
		}
	}
};