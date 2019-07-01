#pragma once

#include "Actor.h"
#include "MeshRenderer.h"
#include "RigidBody.h"
#include "Utils.h"

#include <string>

class Enemy : public Actor
{
private:
	std::shared_ptr<MeshRenderer> mesh_renderer;

public:
	Enemy(std::string file_name)
	{
		// MeshRenderer component
		mesh_renderer = std::make_shared<MeshRenderer>(*this, file_name);
		AddComponent<MeshRenderer>(mesh_renderer);
	}

	virtual void BeginPlay() override
	{

	}

	virtual void Tick(float delta_time) override
	{

	}
};