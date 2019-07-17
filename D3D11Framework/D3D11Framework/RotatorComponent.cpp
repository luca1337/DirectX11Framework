#include "RotatorComponent.h"

#include "Transform.h"
#include "Actor.h"
#include "Time.h"


unsigned int RotatorComponent::Type = 0;

RotatorComponent::RotatorComponent(Actor & owner) : owner(owner)
{
	bRotate = true;
}

void RotatorComponent::Tick(float delta_time)
{
	if (!bRotate)
		return;

	// just rotate the game object
	owner.transform->Rotate(1.0f * Time::GetDeltaTime(), 0.0f, 1.0f * Time::GetDeltaTime());
}
