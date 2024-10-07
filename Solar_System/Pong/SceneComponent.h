#pragma once
#include "Transform.h"

class SceneComponent
{
public:

	Transform transform;

	virtual void Update(float deltaTime) {}
};