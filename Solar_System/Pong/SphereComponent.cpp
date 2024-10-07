#include "SphereComponent.h"

void SphereComponent::CreateSphere(float radius, int sliceCount, int stackCount)
{
	vertices.clear();
	indices.clear();

	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	DirectX::XMFLOAT4 topVertex(0.0f, radius, 0.0f, 1.0f);
	DirectX::XMFLOAT4 bottomVertex(0.0f, -radius, 0.0f,1.0f);

	vertices.push_back(topVertex);
	vertices.push_back(color);
	vertices.push_back(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f));

	float phiStep = DirectX::XM_PI / stackCount;
	float thetaStep = 2.0f * DirectX::XM_PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (int i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		// Vertices of ring.
		for (int j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			DirectX::XMFLOAT3 v;

			// spherical to cartesian
	//		v.w = 1.0f;
			v.x = sinf(phi) * cosf(theta);
			v.y = cosf(phi);
			v.z = sinf(phi) * sinf(theta);


			vertices.push_back(DirectX::XMFLOAT4(v.x * radius, v.y * radius, v.z * radius, 1.0));
			vertices.push_back(color);//color
			vertices.push_back(DirectX::XMFLOAT4(v.x, v.y, v.z, 0.0f));
		}
	}

	vertices.push_back(bottomVertex);
	vertices.push_back(color); //color
	vertices.push_back(DirectX::XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f));

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (int i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; ++i)
	{
		for (int j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	int southPoleIndex = (int)vertices.size()-1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
}

HRESULT SphereComponent::AllocResources()
{
	SetBuffers();
	//SetShaders();
	//SetMatrixes();
	//UpdateMatrixes();
	//SetInputLayout();

	isResourcesAlloced = true;

	return S_OK;
}


void SphereComponent::Draw()
{
	UINT stride = sizeof(DirectX::XMFLOAT4) * 3;
	UINT offset = 0;

	
	app->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	app->context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	

	app->context->DrawIndexed(UINT(indices.size()), 0, 0);

}

HRESULT SphereComponent::DestroyResources()
{
	if (isResourcesAlloced)
	{
		if (indexBuffer) indexBuffer->Release();
		if (vertexBuffer) vertexBuffer->Release();
	//	if (constantBuffer) constantBuffer->Release();

		//if (layout)
		//	layout->Release();
		//if (vertexShader)
		//	vertexShader->Release();
		//if (vertexShaderByteCode)
		//	vertexShaderByteCode->Release();
		//if (pixelShader)
		//	pixelShader->Release();
		//if (pixelShaderByteCode)
		//	pixelShaderByteCode->Release();
	}

	isResourcesAlloced = false;

	return S_OK;
}