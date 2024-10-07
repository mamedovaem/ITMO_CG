#include "Game.h"
#include "CameraComponent.h"
#include "PlanetComponent.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	PlanetComponent* Sun = new PlanetComponent(this, 2.0f, { 1.0f, 1.0f, 0.0f, 1.0f },0.0f, 1.0f);
	components.push_back(Sun);
	
	PlanetComponent* Planet1 = new PlanetComponent(this, 0.2f, { 1.0f, 0.6f, 0.0f, 1.0f }, 4.0f, 1.0f);
	Planet1->transform.parent = &Sun->transform;
	components.push_back(Planet1);

	PlanetComponent* satellite = new PlanetComponent(this, 0.1f, { 1.0f, 1.0f, 0.7f, 1.0f }, 1.0f, 2.0f);
	satellite->transform.parent = &Planet1->transform;
//	satellite->transform.position.x = 1.0f;
	components.push_back(satellite);

	PlanetComponent* Planet2 = new PlanetComponent(this, 0.3f, { 0.6f, 0.6f, 0.0f, 1.0f },6.0f, 0.7f);
	Planet2->transform.parent = &Sun->transform;
	Planet2->transform.position.x = 6.0f;
	Planet2->transform.position.z = 2.0f;
	components.push_back(Planet2);

	PlanetComponent* Planet3 = new PlanetComponent(this, 0.3f, { 0.4f, 0.6f, 1.0f, 1.0f },7.0f, 0.5f);
	Planet3->transform.parent = &Sun->transform;
	//Planet3->transform.position.x = 7.0f;
	components.push_back(Planet3);

	PlanetComponent* satellite1 = new PlanetComponent(this, 0.1f, { 1.0f, 1.0f, 1.0f, 1.0f },1.0f, 0.3f);
	satellite1->transform.parent = &Planet3->transform;
	//satellite1->transform.position.x = 1.0f;
	components.push_back(satellite1);

	PlanetComponent* Planet4 = new PlanetComponent(this, 0.3f, { 0.7f, 0.0f, 0.0f, 1.0f }, 8.2f, 0.5f);
	Planet4->transform.parent = &Sun->transform;
	//Planet4->transform.position.x = 8.2f;
	components.push_back(Planet4);

	PlanetComponent* Planet5 = new PlanetComponent(this, 0.9f, { 0.8f, 0.4f, 0.2f, 1.0f }, 10.0f, 1.0f);
	Planet5->transform.parent = &Sun->transform;
//	Planet5->transform.position.x = 10.0f;
	components.push_back(Planet5);

	PlanetComponent* Planet6 = new PlanetComponent(this, 0.75f, { 0.7f, 0.6f, 0.2f, 1.0f }, 12.0f, 1.5f);
	Planet6->transform.parent = &Sun->transform;
//	Planet6->transform.position.x = 12.0f;
	components.push_back(Planet6);

	PlanetComponent* Planet7 = new PlanetComponent(this, 0.5f, { 0.0f, 0.8f, 0.8f, 1.0f }, 14.0f, 0.8f);
	Planet7->transform.parent = &Sun->transform;
	//Planet7->transform.position.x = 14.0f;
	components.push_back(Planet7);

	PlanetComponent* Planet8 = new PlanetComponent(this, 0.4f, { 0.2f, 0.0f, 0.9f, 1.0f }, 15.0f, 1.2f);
	Planet8->transform.parent = &Sun->transform;
//	Planet8->transform.position.x = 15.0f;
	components.push_back(Planet8);



	prevTime = GetTickCount64();

	input->MouseMove.AddRaw(this, &Game::OnMouseMove);

	isResourcesAlloced = true;
	return true;
}

bool isExitRequested{ false };
void Game::Run()
{
	MSG msg = {};

	while (!isExitRequested)
	{
		// Handle the windows messages.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT) {
			isExitRequested = true;
		}

		curTime = GetTickCount64();
		
		deltaTime = (curTime - prevTime) * 1e-3f;
	//	components[0]->transform.position.x += deltaTime * 1;
	//	camera->transform.rotation.y += deltaTime;
		ProcessInput();

		for (auto c : components)
		{
			c->Update(deltaTime);
		}

		Render();

		prevTime = curTime;
	}
}

void Game::ProcessInput()
{
	float cameraSpeed = 5.0f;

	if (input->IsKeyDown(Keys::W))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetForward();

		camera->transform.position.x += currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y += currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z += currentDirection.z * deltaTime * cameraSpeed;

		// vector camera.dir * velocity * deltaTime
	}
	if (input->IsKeyDown(Keys::S))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetForward();

		camera->transform.position.x -= currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y -= currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z -= currentDirection.z * deltaTime * cameraSpeed;
	}
	if (input->IsKeyDown(Keys::A))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetRight();

		camera->transform.position.x -= currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y -= currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z -= currentDirection.z * deltaTime * cameraSpeed;
	}
	if (input->IsKeyDown(Keys::D))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetRight();

		camera->transform.position.x += currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y += currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z += currentDirection.z * deltaTime * cameraSpeed;
	}
	if (input->IsKeyDown(Keys::Space))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetUp();

		camera->transform.position.x += currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y += currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z += currentDirection.z * deltaTime * cameraSpeed;
	}
	if (input->IsKeyDown(Keys::C))
	{
		DirectX::XMFLOAT3 currentDirection = camera->transform.GetUp();

		camera->transform.position.x -= currentDirection.x * deltaTime * cameraSpeed;
		camera->transform.position.y -= currentDirection.y * deltaTime * cameraSpeed;
		camera->transform.position.z -= currentDirection.z * deltaTime * cameraSpeed;
	}

}

void Game::DestroyResources()
{
	if (input)
	{
		delete input;
		input = nullptr;
	}

	//if (Sun) {
	//	Sun->DestroyResources();
	//	delete Sun;
	//	Sun = nullptr;
	//}

}

void Game::OnMouseMove(const InputDevice::MouseMoveEventArgs& args)
{
	camera->transform.rotation.y += args.Offset.x * 0.2f / 180.0f * DirectX::XM_PI;
	camera->transform.rotation.x += args.Offset.y * 0.2f / 180.0f * DirectX::XM_PI;
}
