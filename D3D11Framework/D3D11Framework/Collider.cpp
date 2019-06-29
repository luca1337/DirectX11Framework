#include "Collider.h"

#include "Mesh.h"
#include "Actor.h"
#include "ShaderManager.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Engine.h"
#include <algorithm>

unsigned int Collider::Type = 0;

Collider::Collider(Actor& owner, eColliderType collider_type) : owner(owner), collider_type(collider_type)
{
	if (collider_type == eColliderType::eBOX)
	{
		collider_mesh = std::make_shared<Mesh>("Assets/Models/cube.txt");
		collider_mesh->SetScale(owner.transform->scale);
		collider_mesh->SetPosition(owner.transform->location);
		collider_mesh->SetRotation(owner.transform->rotation);
	}
	else
	{
		collider_mesh = std::make_shared<Mesh>("Assets/Models/sphere.txt");
		collider_mesh->SetScale(owner.transform->scale);
		collider_mesh->SetPosition(owner.transform->location);
		collider_mesh->SetRotation(owner.transform->rotation);

		scales.push_back(owner.transform->scale.x);
		scales.push_back(owner.transform->scale.y);
		scales.push_back(owner.transform->scale.z);

		auto scale = owner.transform->scale;
		float x = scale.x;
		float y = scale.y;
		float z = scale.z;

		scales.push_back(x);
		scales.push_back(y);
		scales.push_back(z);

		std::sort(scales.begin(), scales.end());
		radius = scales[scales.size() - 1];
	}
}

Collider::Collider(Actor& owner, const float radius) : owner(owner)
{
	collider_mesh = std::make_shared<Mesh>("Assets/Models/sphere.txt");
	collider_mesh->Scale(owner.transform->scale.x, owner.transform->scale.y, owner.transform->location.z);
}

physx::PxShape * Collider::GetShape()
{
	return shape;
}

eColliderType Collider::GetGeometryType()
{
	return collider_type;
}

float Collider::GetRadius() const
{
	return radius;
}

void Collider::Tick(float delta_time)
{
	Engine::Singleton().GetDxDevice()->TurnOnWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("collider_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("collider_pixel")->Bind();

	if (collider_type == eColliderType::eBOX)
	{
		collider_mesh->SetScale(owner.transform->scale);
		collider_mesh->SetPosition(owner.transform->location);
		collider_mesh->SetRotation(owner.transform->rotation);
	}
	else
	{
		scales.clear();

		auto scale = owner.transform->scale;
		float x = scale.x;
		float y = scale.y;
		float z = scale.z;

		scales.push_back(x);
		scales.push_back(y);
		scales.push_back(z);

		std::sort(scales.begin(), scales.end());
		radius = scales[scales.size() - 1];

		collider_mesh->SetScale(radius, radius, radius);
		collider_mesh->SetPosition(owner.transform->location);
		collider_mesh->SetRotation(owner.transform->rotation);
	}

	collider_mesh->Draw(nullptr, nullptr, nullptr);

	Engine::Singleton().GetDxDevice()->TurnOffWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();
}

Collider::~Collider()
{
	shape->release();
}
