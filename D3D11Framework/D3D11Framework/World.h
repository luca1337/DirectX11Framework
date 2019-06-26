#pragma once

#include <memory>
#include <vector>

class Actor;

class World
{
public:
	static World& Get();

	void Tick(float delta_time);

	void SpawnActor(std::shared_ptr<Actor> actor);

	std::vector<std::shared_ptr<Actor>> actors;

private:
	World();
};