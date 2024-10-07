#include "CameraComponent.h"

DirectX::XMMATRIX CameraComponent::GetProjMatrix()
{
	return DirectX::XMMatrixPerspectiveFovLH(FOV, aspectRatio, nearZ, farZ);
}
