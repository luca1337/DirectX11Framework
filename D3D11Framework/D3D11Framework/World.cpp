#include "World.h"

#include "Actor.h"

World::World()
{

}

World& World::Get()
{
	static World* world = nullptr;

	if (!world)
	{
		world = new World();
	}

	return *world;
}

void World::Tick(float delta_time)
{
	for (auto& actor : actors)
	{
		actor->Tick(delta_time);

		for (auto& comp : actor->Components)
		{
			if (!comp->Enabled)
				continue;

			comp->Tick(delta_time);
		}
	}
}

void World::SpawnActor(std::shared_ptr<Actor> actor)
{
	actors.push_back(actor);
}
