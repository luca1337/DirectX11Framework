#include "MeshShape.h"
#include "GPUBuffer.h"
#include "Engine.h"
#include "Device.h"
#include "GPUConstBuffer.h"
#include "Graphics.h"
#include "Camera.h"
#include "ShaderObject.h"
#include "Texture.h"

MeshShape::MeshShape() : mesh_mvp { }
{
}

MeshShape::~MeshShape()
{

}

void MeshShape::PushGPUBuffer(unsigned int size, unsigned int stride, void * buf_data)
{
	auto gpu_buffer = std::make_shared<GPUBuffer>(Engine::Singleton().GetDxDevice(), size, stride, buf_data);
	this->buffers.push_back(gpu_buffer);
}

void MeshShape::DrawMesh()
{
	UpdateMeshMatrix();

	mesh_mvp_buffer->BindInVertex(0, &mesh_mvp);

	for (unsigned i = 0; i < buffers.size(); i++)
	{
		buffers[i]->Bind(i);
	}
	
	// Draw-Call!
	Engine::Singleton().GetDxDevice()->GetDXContext()->Draw(6, 0);
}

void MeshShape::UpdateMeshMatrix()
{
	translation = DirectX::XMMatrixTranslation(mesh_position.x, mesh_position.y, mesh_position.z);
	rotation = DirectX::XMMatrixRotationQuaternion(mesh_rotation);
	scale = DirectX::XMMatrixScaling(mesh_scale.x, mesh_scale.y, mesh_scale.z);

	mesh_mvp.model = scale * rotation * translation;
	mesh_mvp.view = Graphics::Singleton().GetMainCamera()->GetViewMatrix();
	mesh_mvp.projection = Graphics::Singleton().GetMainCamera()->GetProjectionMatrix();
}