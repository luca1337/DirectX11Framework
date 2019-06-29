#include "Mesh.h"

#include "MeshLoader.h"
#include "GPUBuffer.h"
#include "GPUConstBuffer.h"
#include "Camera.h"
#include "Engine.h"
#include "Graphics.h"
#include "Texture.h"
#include "ShaderObject.h"

Mesh::Mesh(std::string file_path)
{
	MeshLoader::Load(file_path, *this);

	// add 3 buffers always so that we can see the rendered model onto the scene
	AddBuffer(static_cast<UINT>(vertices.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), vertices.data());
	AddBuffer(static_cast<UINT>(normals.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), normals.data());
	AddBuffer(static_cast<UINT>(uvs.size() * sizeof(float) * 2), static_cast<UINT>(sizeof(float) * 2), uvs.data());
	AddBuffer(static_cast<UINT>(tangents.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), tangents.data());
	AddBuffer(static_cast<UINT>(bitangents.size() * sizeof(float) * 3), static_cast<UINT>(sizeof(float) * 3), bitangents.data());

	// MVP buffer for 3D projection local to world
	mvp_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(Mvp)));

	// -- NEW -- material buffer -- NEW --
	material_buffer = std::make_shared<GPUConstBuffer>(Engine::Singleton().GetDxDevice(), static_cast<UINT>(sizeof(Material)));

	location_v = SimpleMath::Vector3();
	rotation_q = SimpleMath::Quaternion();
	scale_v = SimpleMath::Vector3(1.0f, 1.0f, 1.0f);
}

void Mesh::SetPosition(const SimpleMath::Vector3& pos)
{
	location_v = pos;
}

void Mesh::SetPosition(float x, float y, float z)
{
	location_v = SimpleMath::Vector3(x, y, z);
}

void Mesh::SetRotation(const SimpleMath::Vector3& eulers)
{
	rotation_q = SimpleMath::Quaternion::CreateFromYawPitchRoll(eulers.x, eulers.y, eulers.z);
}

void Mesh::SetRotation(float x, float y, float z)
{
	rotation_q = SimpleMath::Quaternion::CreateFromYawPitchRoll(x, y, z);;
}

void Mesh::SetScale(float x, float y, float z)
{
	scale_v = SimpleMath::Vector3(x, y, z);
}

void Mesh::SetScale(const SimpleMath::Vector3& scale)
{
	scale_v = scale;
}

void Mesh::Translate(const SimpleMath::Vector3& pos)
{
	location_v.x += pos.x;
	location_v.y += pos.y;
	location_v.z += pos.z;
}

void Mesh::Translate(float x, float y, float z)
{
	location_v.x += x;
	location_v.y += y;
	location_v.z += z;
}

void Mesh::Scale(float x, float y, float z)
{
	scale_v.x += x;
	scale_v.y += y;
	scale_v.z += z;
}

void Mesh::Rotate(const SimpleMath::Vector3& rot)
{
	// TODO: build rotation from quaternion starting by eulers
}

void Mesh::Rotate(float x, float y, float z)
{
	// TODO: build rotation from quaternion starting by eulers
}

const SimpleMath::Vector3& Mesh::GetPosition() const
{
	return location_v;
}

void Mesh::Draw(std::shared_ptr<Texture> albedo, std::shared_ptr<Texture> normal_map, std::shared_ptr<Material> material)
{
	// bind up camera and ambient light but only once!!!! they must not be changed
	light_properties.eye_position = Graphics::Singleton().GetMainCamera()->GetPosition();
	light_properties.global_ambient = SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);

	Graphics::Singleton().lights_properties_buffer->BindInPixel(2, &light_properties, 1);

	if (material)
	{
		// bind up material
		material_buffer->BindInPixel(3, material.get(), 1);
	}
	else
	{
		// or default material
		material_buffer->BindInPixel(3, default_material.get(), 1);
	}

	///// HERE WE NEED TO BIND LIGHT BUFFER /////

	Graphics::Singleton().lights_buffer->BindInPixel(1, Graphics::Singleton().lights.data(), 1);

	UpdateMatrix();

	if (albedo)
	{
		albedo->GetShaderObject()->Bind(0);
	}

	if (normal_map)
	{
		normal_map->GetShaderObject()->Bind(1);
	}

	mvp_buffer->BindInVertex(0, &mvp);

	for (int i = 0; i < buffers.size(); i++)
	{
		buffers[i]->Bind(i);
	}

	Engine::Singleton().GetDxDevice()->GetDXContext()->Draw(vertices_count, 0);

	if (albedo)
	{
		albedo->GetShaderObject()->Unbind(0);
	}

	if (normal_map)
	{
		normal_map->GetShaderObject()->Unbind(1);
	}
}

void Mesh::AddBuffer(UINT size, UINT stride, void* data)
{
	auto buffer = std::make_shared<GPUBuffer>(Engine::Singleton().GetDxDevice(), size, stride, data);
	buffers.push_back(buffer);
}

void Mesh::UpdateMatrix()
{
	// set base values for matrix mult
	translation = DirectX::XMMatrixTranslation(location_v.x, location_v.y, location_v.z);
	rotation = DirectX::XMMatrixRotationQuaternion(rotation_q);
	scale = DirectX::XMMatrixScaling(scale_v.x, scale_v.y, scale_v.z);

	// correct the mvp and build it up
	mvp.model = scale * rotation * translation;
	mvp.view = Graphics::Singleton().GetMainCamera()->GetViewMatrix();
	mvp.projection = Graphics::Singleton().GetMainCamera()->GetProjectionMatrix();
}