#pragma once
#include "Libs.h"
#include "Collision.h"
#include "RectComponent.h"

class Paddle : public RectComponent, public Collision
{
public:
	float velocity = 1;

	Paddle(){}
	void Move(DirectX::XMFLOAT4)
	{
	
	}
};