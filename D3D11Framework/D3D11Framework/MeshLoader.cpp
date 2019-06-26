#include "MeshLoader.h"

#include "Mesh.h"
#include <vector>
#include <DirectXMath.h>
#include <fstream>

void MeshLoader::Load(std::string file_path, Mesh& mesh)
{
	// read mesh file
	std::ifstream reader;

	reader.open(file_path, std::ios_base::binary);

	if (!reader.is_open()) { throw std::exception("could not open file"); }

	reader.read(reinterpret_cast<char*>(&mesh.vertices_count), sizeof(int));

	mesh.vertices = std::vector<SimpleMath::Vector3>(mesh.vertices_count);
	mesh.normals = std::vector<SimpleMath::Vector3>(mesh.vertices_count);
	mesh.uvs = std::vector<SimpleMath::Vector2>(mesh.vertices_count);
	mesh.tangents = std::vector<SimpleMath::Vector3>(mesh.vertices_count);
	mesh.bitangents = std::vector<SimpleMath::Vector3>(mesh.vertices_count);

	reader.read(reinterpret_cast<char*>(mesh.vertices.data()), mesh.vertices_count * sizeof(float) * 3);
	reader.read(reinterpret_cast<char*>(mesh.normals.data()), mesh.vertices_count * sizeof(float) * 3);
	reader.read(reinterpret_cast<char*>(mesh.uvs.data()), mesh.vertices_count * sizeof(float) * 2);
	reader.read(reinterpret_cast<char*>(mesh.tangents.data()), mesh.vertices_count * sizeof(float) * 3);
	reader.read(reinterpret_cast<char*>(mesh.bitangents.data()), mesh.vertices_count * sizeof(float) * 3);

	reader.close();
}