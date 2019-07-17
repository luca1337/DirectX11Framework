#pragma once

#include "Actor.h"
#include "MeshRenderer.h"
#include "RigidBody.h"
#include "Utils.h"
#include <string>

class Player : public Actor
{
private:
	std::shared_ptr<MeshRenderer> mesh_renderer;
	std::shared_ptr<RigidBody> rigid_body;

public:
	Player(std::string file_name)
	{
		// MeshRenderer component
		mesh_renderer = std::make_shared<MeshRenderer>(*this, file_name);
		mesh_renderer->AssignMaterial(Utils::default_material);
		AddComponent<MeshRenderer>(mesh_renderer);
	}

	virtual void BeginPlay() override
	{

	}

	virtual void Tick(float delta_time) override
	{

	}
};