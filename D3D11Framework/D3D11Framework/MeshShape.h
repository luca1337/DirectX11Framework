#pragma once

#include <memory>
#include <vector>

#include "Mvp.h"

#include "Core.h"
#include <SimpleMath.h>

using namespace DirectX;

class GPUBuffer;
class GPUConstBuffer;
class Texture;

class MeshShape
{
public:
	MeshShape();
	virtual ~MeshShape() = 0;

protected:
	std::vector<std::shared_ptr<GPUBuffer>> buffers;

	void PushGPUBuffer(unsigned int size, unsigned int stride, void* buf_data);

	void DrawMesh();
	void UpdateMeshMatrix();

	SimpleMath::Matrix translation;
	SimpleMath::Matrix rotation;
	SimpleMath::Matrix scale;

	std::vector<SimpleMath::Vector3> vertices;
	std::vector<SimpleMath::Vector3> normals;
	std::vector<SimpleMath::Vector2> uvs;
	std::vector<SimpleMath::Vector3> tangents;
	std::vector<SimpleMath::Vector3> bitangents;

	unsigned int vertices_count;

	std::shared_ptr<GPUConstBuffer> mesh_mvp_buffer;

	SimpleMath::Vector3 mesh_position;
	SimpleMath::Quaternion mesh_rotation;
	SimpleMath::Vector3 mesh_scale;

	Mvp mesh_mvp;
};