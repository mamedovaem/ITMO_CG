#include "RectComponent.h"

HRESULT RectComponent::AllocResources()
{
	SetMatrixes();
	SetBuffers();
	SetShaders();
	SetInputLayout();
	isResourcesAlloced = true;

	return S_OK;
}


void RectComponent::Draw()
{
	UINT stride = sizeof(DirectX::XMFLOAT4) * 2;
	UINT offset = 0;

	app->context->IASetInputLayout(layout);
	app->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	app->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	app->context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	app->context->VSSetConstantBuffers(0, 1, &constantBuffer);
	app->context->PSSetConstantBuffers(1, 1, &constantBufferColor);
	app->context->VSSetShader(vertexShader, NULL, 0);
	app->context->PSSetShader(pixelShader, NULL, 0);

	app->context->DrawIndexed(6, 0, 0);

}

HRESULT RectComponent::DestroyResources()
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


