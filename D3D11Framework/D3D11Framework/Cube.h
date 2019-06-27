#pragma once

#include "Actor.h"

#include "Core.h"
#include <SimpleMath.h>
#include <string>

using namespace DirectX;

class BoxCollider;
class MeshRenderer;

class Cube : public Actor
{
public:
	Cube(const SimpleMath::Vector3& size);

private:
	std::shared_ptr<MeshRenderer> cube_mesh;
	std::shared_ptr<BoxCollider> box_collider;

	const std::string& mesh_path = "Assets/Models/cube.txt";
};