#pragma once
#include "Libs.h"

struct Transform
{
	Transform* parent = nullptr;

	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f };

	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMMATRIX GetViewMatrix();

	DirectX::XMFLOAT3 GetRight();
	DirectX::XMFLOAT3 GetUp();
	DirectX::XMFLOAT3 GetForward();

};