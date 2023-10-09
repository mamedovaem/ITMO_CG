#pragma once
#include "Libs.h"
#include "RectComponent.h"

class Paddle : public RectComponent
{
public:
	float velocity = 1.5f;

	Paddle(D3DApp* app, float length = 0.4, float width = 0.1, DirectX::XMFLOAT2 pos = { 0, 0 },
		DirectX::XMFLOAT4 color = { 0.2f, 1.0f, 0.4f, 1.0f }) : RectComponent(app, length, width, pos, color) {}

	void Move(bool isUpDirection, float deltaTime)
	{
		float upBoundary = 1.0f - width / 2.0f;
		float downBoundary = -1.0f + width / 2.0f;

		if (isUpDirection && pos.y <= upBoundary)
		{
			pos.y += velocity * deltaTime;
		}
		else if (!isUpDirection && pos.y >= downBoundary)
		{
			pos.y -= velocity * deltaTime;
		}
		matrixes.mMVP = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
		UpdateMatrixes();
	}
};