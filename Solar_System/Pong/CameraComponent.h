#pragma once
#include "SceneComponent.h"

class CameraComponent : public SceneComponent
{
public:
	float FOV = DirectX::XM_PIDIV2; //Field of View
	float aspectRatio = 1.0f; 
	float nearZ = 0.01f;
	float farZ = 100.0f;

	DirectX::XMMATRIX GetProjMatrix();
};