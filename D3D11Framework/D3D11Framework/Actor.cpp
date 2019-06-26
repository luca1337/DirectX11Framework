#include "Actor.h"

#include "Transform.h"

Actor::Actor()
{
	transform = std::make_shared<Transform>();
	AddComponent<Transform>(transform);
}

void Actor::InternalAddComponent(std::shared_ptr<Component> Component)
{
	this->Components.push_back(Component);
}

void Actor::BeginPlay()
{

}

void Actor::Tick(float delta_time)
{
}

void Actor::FixedTick(float fixed_delta_time)
{
}
