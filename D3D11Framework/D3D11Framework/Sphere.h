#pragma once

#include "Actor.h"
#include <memory>

#include "Core.h"
#include <SimpleMath.h>

using namespace DirectX;

class MeshRenderer;
class SphereCollider;

class Sphere : public Actor
{
public:
	Sphere();

private:
	std::shared_ptr<MeshRenderer> sphere_mesh;
	std::shared_ptr<SphereCollider> sphere_collider;

	const std::string mesh_path = "Assets/Models/sphere.txt";

};