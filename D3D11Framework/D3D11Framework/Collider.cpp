#include "Collider.h"

Collider::Collider(Actor& owner, const DirectX::SimpleMath::Vector3 & size)
{
	collider_mesh = std::make_shared<Mesh>("Assets/Models/cube.txt");
	collider_mesh->Scale(owner.transform->scale.x, owner.transform->scale.y, owner.transform->location.z);
}

Collider::Collider(Actor& owner, const float radius)
{
	collider_mesh = std::make_shared<Mesh>("Assets/Models/sphere.txt");
	collider_mesh->Scale(owner.transform->scale.x, owner.transform->scale.y, owner.transform->location.z);
}

void Collider::Tick(float delta_time)
{
	Engine::Singleton().GetDxDevice()->TurnOnWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("collider_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("collider_pixel")->Bind();

	collider_mesh->Draw(nullptr, nullptr, nullptr);

	Engine::Singleton().GetDxDevice()->TurnOffWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vs")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_ps")->Bind();
}

Collider::~Collider()
{
	shape->release();
}
