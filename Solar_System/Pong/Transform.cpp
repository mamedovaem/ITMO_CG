#include "Transform.h"

DirectX::XMMATRIX Transform::GetWorldMatrix()
{

    if (parent)
    {
        return DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) 
            * DirectX::XMMatrixTranslation(position.x, position.y, position.z)
            * parent->GetWorldMatrix();
    }
    else
    {
        return DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * DirectX::XMMatrixTranslation(position.x, position.y, position.z);

    }

    return DirectX::XMMATRIX();
}

DirectX::XMMATRIX Transform::GetViewMatrix()
{

    return DirectX::XMMatrixInverse(nullptr, GetWorldMatrix());
}


DirectX::XMFLOAT3 Transform::GetRight()
{
    DirectX::XMFLOAT3 rightDir = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
    DirectX::XMFLOAT3 result;
    DirectX::XMStoreFloat3(&result, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&rightDir), GetWorldMatrix()));
    
    return result;
}

DirectX::XMFLOAT3 Transform::GetUp()
{
    DirectX::XMFLOAT3 upDir = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    DirectX::XMFLOAT3 result;
    DirectX::XMStoreFloat3(&result, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&upDir), GetWorldMatrix()));

    return result;

}

DirectX::XMFLOAT3 Transform::GetForward()
{
    DirectX::XMFLOAT3 forwardDir = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
    DirectX::XMFLOAT3 result;
    DirectX::XMStoreFloat3(&result, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&forwardDir), GetWorldMatrix()));

    return result;
}