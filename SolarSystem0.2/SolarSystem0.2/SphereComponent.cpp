#include "SphereComponent.h"

void SphereComponent::GenerateGeometry()
{
	float dTheta = 2.0f * 3.14f / sideNum;
	int centerIndex = 0;
	DirectX::XMFLOAT4 center = { pos.x, pos.y,pos.z, 1.f };
	DirectX::XMFLOAT4 northPole = { pos.x, pos.y,pos.z, 1.f };
	vertices.push_back(center);
	vertices.push_back(color);
	for (int i = 1; i < sideNum-1; ++i)
	{
		for (int j = 0; i <= sideNum; ++j)
		{
			float x = center.x + radius * cosf(i * dTheta);
			float y = center.y + radius * sinf(i * dTheta);
			float z = center.z + radius * sinf(j * dTheta);

			DirectX::XMFLOAT4 vertex{ x, y, z, center.w };

			vertices.push_back(vertex);
			vertices.push_back(color);
		}

		for (int i = 1; i < sideNum; ++i)
		{
			indices.push_back(centerIndex);
			indices.push_back(i);
			indices.push_back(i + 1);
		}

		for (int i = 1; i < sideNum; ++i)
		{
			indices.push_back(centerIndex);
			indices.push_back(i);
			indices.push_back(i + 1);
		}

		indices.push_back(centerIndex);
		indices.push_back(sideNum);
		indices.push_back(1);
	}
}

HRESULT SphereComponent::AllocResources()
{
	SetMatrixes();
	SetBuffers();
	SetShaders();
	SetInputLayout();

	isResourcesAlloced = true;

	return S_OK;
}


void SphereComponent::Draw()
{
	UINT stride = sizeof(DirectX::XMFLOAT4) * 2;
	UINT offset = 0;

	app->context->IASetInputLayout(layout);
	app->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	app->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	app->context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	app->context->VSSetConstantBuffers(0, 1, &constantBuffer);
	app->context->PSSetConstantBuffers(1, 1, &constantBufferColor);
	//app->context->PSSetConstantBuffers(0, 1, &constantBuffer);
	app->context->VSSetShader(vertexShader, NULL, 0);
	app->context->PSSetShader(pixelShader, NULL, 0);

	app->context->DrawIndexed(UINT(indices.size()), 0, 0);

}

HRESULT SphereComponent::DestroyResources()
{
	if (isResourcesAlloced)
	{
		if (indexBuffer) indexBuffer->Release();
		if (vertexBuffer) vertexBuffer->Release();
		if (constantBuffer) constantBuffer->Release();

		if (layout)
			layout->Release();
		if (vertexShader)
			vertexShader->Release();
		if (vertexShaderByteCode)
			vertexShaderByteCode->Release();
		if (pixelShader)
			pixelShader->Release();
		if (pixelShaderByteCode)
			pixelShaderByteCode->Release();
	}

	isResourcesAlloced = false;

	return S_OK;
}
