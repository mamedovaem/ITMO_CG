#include "TriangleComponent.h"

HRESULT TriangleComponent::AllocResources()
{
	SetMatrixes();
	SetBuffers();
	SetShaders();
	SetInputLayout();
	isResourcesAlloced = true;

	return S_OK;
}


void TriangleComponent::Draw()
{
	UINT stride = sizeof(DirectX::XMFLOAT4) * 2;
	UINT offset = 0;

	app->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	app->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	app->context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	app->context->VSSetConstantBuffers(0, 1, &constantBuffer);
	app->context->VSSetShader(vertexShader, NULL, 0);
	app->context->PSSetShader(pixelShader, NULL, 0);

	app->context->DrawIndexed(3, 0, 0);

}

HRESULT TriangleComponent::DestroyResources()
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


