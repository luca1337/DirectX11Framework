#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Actor.h"
#include "TextureManager.h"

unsigned int MeshRenderer::Type = 0;

MeshRenderer::MeshRenderer(Actor& owner, std::string file_name) : owner(owner)
{
	mesh = std::make_shared<Mesh>(file_name);
}

void MeshRenderer::BeginPlay()
{
}

void MeshRenderer::Tick(float delta_time)
{
	// set the transform
	mesh->SetPosition(owner.transform->location);
	mesh->SetRotation(owner.transform->rotation);
	mesh->SetScale(owner.transform->scale);

	mesh->Draw(albedo, normal_map, material);
}

void MeshRenderer::SetAlbedo(std::string albedo)
{
	this->albedo = TextureManager::GetTexture(albedo);
}

void MeshRenderer::SetNormal(std::string normal_map)
{
	this->normal_map = TextureManager::GetTexture(normal_map);
}

void MeshRenderer::AssignMaterial(std::shared_ptr<Material> material)
{
	this->material = material;
}
