#include "Model.h"
#include "Application.h"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"
#include "assimp/Importer.hpp"
#include "ModuleTexture.h"

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

		aiString file;
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
		meshes[i]->Draw(materials);
	}
}


void Model::LoadMeshes(aiMesh** meshObjects, int numMeshes)
{
	meshes.reserve(numMeshes);
	for (int i = 0; i < numMeshes; ++i)
	{
		Mesh* mesh = new Mesh();
		mesh->LoadVBO(meshObjects[i]);
		mesh->LoadEBO(meshObjects[i]);
		mesh->CreateVAO();
		mesh->material_index = meshObjects[i]->mMaterialIndex;
		meshes.push_back(mesh);
	}

}