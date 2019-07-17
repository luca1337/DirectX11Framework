#pragma once

#include "Material.h"
#include "MeshShape.h"
#include <memory>

#include "Core.h"
#include <SimpleMath.h>
#include "Light.h"

using namespace DirectX;

class Mesh : public MeshShape
{
public:
	Mesh(std::string file_path);

	void Draw(std::shared_ptr<Texture> albedo, std::shared_ptr<Texture> normal_map, std::shared_ptr<Material> material);
	void Draw();

	unsigned int vertices_count;

private:

	std::vector<SimpleMath::Vector3> vertices;
	std::vector<SimpleMath::Vector3> normals;
	std::vector<SimpleMath::Vector2> uvs;
	std::vector<SimpleMath::Vector3> tangents;
	std::vector<SimpleMath::Vector3> bitangents;

	LightProperties light_properties;

	std::shared_ptr<GPUConstBuffer> material_buffer;

	friend class MeshLoader;
};