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
	std::shared_ptr<GPUConstBuffer> mesh_mvp_buffer;

	SimpleMath::Vector3 mesh_position;
	SimpleMath::Quaternion mesh_rotation;
	SimpleMath::Vector3 mesh_scale;

protected:
	std::vector<std::shared_ptr<GPUBuffer>> buffers;

	void PushGPUBuffer(unsigned int size, unsigned int stride, void* buf_data);

	void DrawMesh(unsigned int vertices_count);
	void UpdateMeshMatrix();

	SimpleMath::Matrix translation;
	SimpleMath::Matrix rotation;
	SimpleMath::Matrix scale;

	Mvp mesh_mvp;
};