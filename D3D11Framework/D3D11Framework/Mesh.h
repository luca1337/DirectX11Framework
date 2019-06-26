#pragma once

#include "Mvp.h"
#include "Transform.h"
#include <string>
#include <vector>
#include "Core.h"
#include "Material.h"
#include "Light.h"

class GPUBuffer;
class GPUConstBuffer;
class Texture;

using namespace DirectX;

class Mesh
{
public:
	Mesh(std::string file_path);

	void SetPosition(const SimpleMath::Vector3& pos);

	void SetPosition(float x, float y, float z);

	void SetRotation(float x, float y, float z);

	void Translate(const SimpleMath::Vector3& pos);

	void Translate(float x, float y, float z);

	void Scale(float x, float y, float z);

	void Rotate(const SimpleMath::Vector3& rot);

	void Rotate(float x, float y, float z);

	const SimpleMath::Vector3& GetPosition() const;

	void Draw(std::shared_ptr<Texture> albedo, std::shared_ptr<Texture> normal_map, std::shared_ptr<Material> material);

	SimpleMath::Vector3 location_v;
	SimpleMath::Vector3 rotation_v;
	SimpleMath::Vector3 scale_v;
private:
	void AddBuffer(UINT size, UINT stride, void* data);

	void UpdateMatrix();

	std::vector<SimpleMath::Vector3> vertices;
	std::vector<SimpleMath::Vector3> normals;
	std::vector<SimpleMath::Vector2> uvs;
	std::vector<SimpleMath::Vector3> tangents;
	std::vector<SimpleMath::Vector3> bitangents;

	SimpleMath::Matrix translation;
	SimpleMath::Matrix rotation;
	SimpleMath::Matrix scale;

	Mvp mvp;

	std::vector<std::shared_ptr<GPUBuffer>> buffers;
	std::shared_ptr<GPUConstBuffer> mvp_buffer;
	std::shared_ptr<GPUConstBuffer> material_buffer;

	UINT vertices_count;

	const std::shared_ptr<Material> default_material = std::make_shared<Material>
		(
			SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),
			SimpleMath::Vector4(0.1f, 0.1f, 0.1f, 1.0f),
			SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f),
			SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f),
			32.0f,
			false,
			false
		);

	LightProperties light_properties;
	Material deault_material;

	friend class MeshLoader;
};