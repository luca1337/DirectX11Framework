#include "Sphere.h"
#include "SphereCollider.h"
#include "MeshRenderer.h"
#include "Transform.h"

Sphere::Sphere()
{
	// Default mesh renderer
	sphere_mesh = std::make_shared<MeshRenderer>(*this, mesh_path);
	AddComponent<MeshRenderer>(sphere_mesh);

	// Default Collider
	sphere_collider = std::make_shared<SphereCollider>(*this);
	AddComponent<SphereCollider>(sphere_collider);
}
