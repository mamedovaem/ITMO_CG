#pragma once
#include "CircleComponent.h"
//#include "Collision.h"


class Ball : public CircleComponent
{

public:

	float initialVelocityX = 0.05f;
	float initialVelocityY = 0.0f;

	float velocityX = 0.05f;
	float velocityY = 0.0f;

	Ball()
	{

	}
	Ball(D3DApp* app, float radius = 0.1, DirectX::XMFLOAT4 center = { 0.0f, 0.0f, 0.0f, 1.0f },
		DirectX::XMFLOAT4 color = { 1.0f, 0.0f, 0.5f, 1.0f }) : CircleComponent(app, radius, center, color) {}

	void Move(float deltaTime)
	{
		DirectX::XMMATRIX mTranslate;

		center.x += velocityX;
		center.y += velocityY;

		float upBoundary = 1.0f - radius;
		float downBoundary = -1.0f + radius;

		
		mTranslate = DirectX::XMMatrixTranslation(velocityX, velocityY, 0.0f);
		matrixes.mMVP = matrixes.mMVP * mTranslate;
		UpdateMatrixes();

		if (center.y >= upBoundary || center.y <= downBoundary)
		{
			velocityY = -velocityY;
		}
		

	}
};