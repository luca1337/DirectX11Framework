#include "UpdateSystem.h"
#include "World.h"

UpdateSystem::UpdateSystem()
{
	update_offset = 1;
}

void UpdateSystem::Update(float delta_time)
{
	World::Get().Tick(delta_time);
}
