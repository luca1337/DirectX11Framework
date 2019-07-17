#include "Mesh.h"
#include "MeshLoader.h"
#include "Engine.h"
#include "Device.h"
#include "GPUConstBuffer.h"
#include "Light.h"
#include "Texture.h"
#include "Graphics.h"
#include "Camera.h"
#include "ShaderObject.h"
#include "Utils.h"

Mesh::Mesh(std::string file_path) : light_properties{}
{
	MeshLoader::Load(file_path, *this);

	// add 3 buffers always so that we can see the rendered model onto the scene
	PushGPUBuffer(static_cast<UINT>(vertices.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), vertices.data());
	PushGPUBuffer(static_cast<UINT>(normals.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), normals.data());
	PushGPUBuffer(static_cast<UINT>(uvs.size() * sizeof(float) * 2), static_cast<UINT>(sizeof(float) * 2), uvs.data());
	PushGPUBuffer(static_cast<UINT>(tangents.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), tangents.data());
	PushGPUBuffer(static_cast<UINT>(bitangents.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), bitangents.data());

	// MVP buffer for 3D projection local to world
	mesh_mvp_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(Mvp)));

	// -- NEW -- material buffer -- NEW --
	material_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(Material)));

	mesh_position = { 0.0f, 0.0f, 0.0f };
	mesh_rotation = SimpleMath::Quaternion::Identity;
	mesh_scale = { 1.0f, 1.0f, 1.0f };
}

void Mesh::Draw(std::shared_ptr<Texture> albedo, std::shared_ptr<Texture> normal_map, std::shared_ptr<Material> material)
{
	// bind up camera and ambient light but only once!!!! they must not be changed
	light_properties.eye_position = Graphics::Singleton().GetMainCamera()->GetPosition();
	light_properties.global_ambient = SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);

	Graphics::Singleton().lights_properties_buffer->BindInPixel(2, &light_properties, 1);

	if (material)
		material_buffer->BindInPixel(3, material.get(), 1);
	else
		material_buffer->BindInPixel(3, Utils::default_material.get(), 1);

	///// HERE WE NEED TO BIND LIGHT BUFFER /////

	Graphics::Singleton().lights_buffer->BindInPixel(1, Graphics::Singleton().lights.data(), 1);

	if (albedo)
		albedo->GetShaderObject()->Bind(0);

	if (normal_map)
		normal_map->GetShaderObject()->Bind(1);

	MeshShape::DrawMesh(vertices_count);

	if (albedo)
		albedo->GetShaderObject()->Unbind(0);

	if (normal_map)
		normal_map->GetShaderObject()->Unbind(1);
}

void Mesh::Draw()
{
	// bind up camera and ambient light but only once!!!! they must not be changed
	light_properties.eye_position = Graphics::Singleton().GetMainCamera()->GetPosition();
	light_properties.global_ambient = SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);

	Graphics::Singleton().lights_properties_buffer->BindInPixel(2, &light_properties, 1);

	///// HERE WE NEED TO BIND LIGHT BUFFER /////

	Graphics::Singleton().lights_buffer->BindInPixel(1, Graphics::Singleton().lights.data(), 1);

	MeshShape::DrawMesh(vertices_count);
}