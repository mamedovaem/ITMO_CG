#include "PlanetComponent.h"

void PlanetComponent::Update(float deltaTime)
{
	
	angle += deltaTime * orbitAngularSpeed;

	transform.position.x = orbitRadius * sin(angle);
	transform.position.z = orbitRadius * cos(angle);

}
