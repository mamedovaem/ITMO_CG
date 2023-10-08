#pragma once
#include "Libs.h"
#include "RectComponent.h"

class Paddle : public RectComponent
{
public:
	float velocity = 0.1;
	bool isLeft = true;

	Paddle()
	{

	}
	Paddle(D3DApp* app, float length = 0.4, float width = 0.1, bool isLeft = true,
		DirectX::XMFLOAT4 center = { -0.5f, -0.5f, 0.5f, 1.0f },
		DirectX::XMFLOAT4 color = { 0.2f, 1.0f, 0.4f, 1.0f }) : RectComponent(app, length, width, center, color) {}

	void Move(bool isUpDirection)
	{
		DirectX::XMMATRIX mTranslate;

		float upBoundary = 1.0f - width / 2.0f;
		float downBoundary = -1.0f + width / 2.0f;


		if (isUpDirection && center.y <= upBoundary)
		{
			center.y += velocity;


			mTranslate = DirectX::XMMatrixTranslation(0.0f, velocity, 0.0f);
			matrixes.mMVP = matrixes.mMVP * mTranslate; // * viewMatrix * projMatrix;
			UpdateMatrixes();
		}
		else if (!isUpDirection && center.y >= downBoundary)
		{
			center.y -= velocity;

			mTranslate = DirectX::XMMatrixTranslation(0.0f, -velocity, 0.0f);
			matrixes.mMVP = matrixes.mMVP * mTranslate; // * viewMatrix * projMatrix;
			UpdateMatrixes();
		}
	}
};