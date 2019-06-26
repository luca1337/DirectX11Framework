#pragma once

#include "Component.h"
#include <string>
#include <memory>

class Mesh;
class Texture;
class Actor;
struct Material;

class MeshRenderer : public Component
{
private:
	std::shared_ptr<Texture> albedo;
	std::shared_ptr<Texture> normal_map;
	std::shared_ptr<Material> material;
	Actor& owner;

public:

	MeshRenderer(Actor& owner, std::string file_name);

	static unsigned int Type;

	virtual void BeginPlay() override;

	virtual void Tick(float delta_time) override;

	std::shared_ptr<Mesh> mesh;

	void SetAlbedo(std::string albedo);
	void SetNormal(std::string normal_map);
	void AssignMaterial(std::shared_ptr<Material> material);
};