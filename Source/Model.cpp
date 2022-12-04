#include "Model.h"
#include "Application.h"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"
#include "assimp/Importer.hpp"
#include "assimp/mesh.h"
#include "ModuleTexture.h"
#include "ModuleCameraEditor.h"

Model::Model()
{
}

// Destructor
Model::~Model()
{
	for (int i = 0; i < materials.size(); i++) {
		glDeleteTextures(1, &materials[i]);
	}
}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
	
		LoadMaterials(scene->mMaterials, scene->mNumMaterials, file_name);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file_name, aiGetErrorString());
	}
}


void Model::LoadMaterials(aiMaterial** textures, int numMaterials, const char* fullTexturePath)
{
	aiString file;
	
	materials.reserve(numMaterials);
	for (unsigned i = 0; i < numMaterials; ++i)
	{
		if (textures[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->textures->LoadTexture(file.data, fullTexturePath));
		}
	}
}

void Model::Update() {
	for (int i = 0; i < meshes.size(); ++i) {
		meshes[i]->Draw(materials, position, rotation, scale);
	}
}


void Model::LoadMeshes(aiMesh** meshObjects, int numMeshes)
{
	numTriangles = 0;
	numVertices = 0;


	maxVertex.x = minVertex.x = meshObjects[0]->mVertices[0].x;
	maxVertex.y = minVertex.y = meshObjects[0]->mVertices[0].y;
	maxVertex.z = minVertex.z = meshObjects[0]->mVertices[0].z;


	meshes.reserve(numMeshes);
	for (int i = 0; i < numMeshes; ++i)
	{
		Mesh* mesh = new Mesh();
		mesh->LoadVBO(meshObjects[i]);
		mesh->LoadEBO(meshObjects[i]);
		mesh->CreateVAO();
		mesh->material_index = meshObjects[i]->mMaterialIndex;
		meshes.push_back(mesh);

		numTriangles += meshObjects[i]->mNumFaces;
		numVertices += meshObjects[i]->mNumVertices;
		for (int j = 0; j < meshObjects[i]->mNumVertices; j++) {
			aiVector3D vertex = meshObjects[i]->mVertices[j];
			if (vertex.x < minVertex.x) {
				minVertex.x = vertex.x;
			}
			if (vertex.y < minVertex.y) {
				minVertex.y = vertex.y;
			}
			if (vertex.z < minVertex.z) {
				minVertex.z = vertex.z;
			}
			if (vertex.x > maxVertex.x) {
				maxVertex.x = vertex.x;
			}
			if (vertex.y > maxVertex.y) {
				maxVertex.y = vertex.y;
			}
			if (vertex.z > maxVertex.z) {
				maxVertex.z = vertex.z;
			}
		}
	}

	boundingBox = new AABB(minVertex + position, maxVertex + position);
	App->cameraEditor->FocusCamera(*boundingBox);

}