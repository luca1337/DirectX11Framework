#include "Cube.h"
#include "BoxCollider.h"
#include "MeshRenderer.h"
#include "Transform.h"

Cube::Cube(const SimpleMath::Vector3& size, const SimpleMath::Vector3& position, const SimpleMath::Vector3& rotation)
{
	this->transform->location = { position.x, position.y, position.z };
	this->transform->rotation = { rotation.x, rotation.y, rotation.z };
	this->transform->scale = { size.x, size.y, size.z };

	// Mesh Renderer for cube
	cube_mesh = std::make_shared<MeshRenderer>(*this, mesh_path);
	AddComponent<MeshRenderer>(cube_mesh);

	// Set BoxCollider as default component of each cube we create
	box_collider = std::make_shared<BoxCollider>(*this);
	AddComponent<BoxCollider>(box_collider);
}