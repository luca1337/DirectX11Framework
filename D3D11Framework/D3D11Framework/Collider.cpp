#include "Collider.h"

#include "Mesh.h"
#include "Actor.h"
#include "ShaderManager.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Engine.h"

unsigned int Collider::Type = 0;

Collider::Collider(Actor& owner) : owner(owner)
{
	collider_mesh = std::make_shared<Mesh>("Assets/Models/cube.txt");
	collider_mesh->SetScale(owner.transform->scale);
	collider_mesh->SetPosition(owner.transform->location);
	collider_mesh->SetRotation(owner.transform->rotation);
}

Collider::Collider(Actor& owner, const float radius) : owner(owner)
{
	collider_mesh = std::make_shared<Mesh>("Assets/Models/sphere.txt");
	collider_mesh->Scale(owner.transform->scale.x, owner.transform->scale.y, owner.transform->location.z);
}

void Collider::Tick(float delta_time)
{
	Engine::Singleton().GetDxDevice()->TurnOnWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("collider_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("collider_pixel")->Bind();

	collider_mesh->SetScale(owner.transform->scale);
	collider_mesh->SetPosition(owner.transform->location);
	collider_mesh->SetRotation(owner.transform->rotation);

	collider_mesh->Draw(nullptr, nullptr, nullptr);

	Engine::Singleton().GetDxDevice()->TurnOffWireframeRendering();

	ShaderManager::GetVertexShaderResourceFromMemory("basic_vertex")->Bind();
	ShaderManager::GetPixelShaderResourceFromMemory("basic_pixel")->Bind();
}

Collider::~Collider()
{
	shape->release();
}
