#include "Model.h"
#include "Application.h"
#include "assimp/postprocess.h"
#include "assimp/cimport.h"
#include "assimp/Importer.hpp"
#include "ModuleTexture.h"

Model::Model()
{
	for (int i = 0; i < materials.size(); i++) {
		glDeleteTextures(1, &materials[i]);
	}
}

// Destructor
Model::~Model()
{

}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{

		aiString file;
		LoadMaterials(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file_name, aiGetErrorString());
	}
}


void Model::LoadMaterials(aiMaterial** textures, int numMaterials)
{
	aiString file;
	std::string path = "GameObjects/";
	
	materials.reserve(numMaterials);
	for (unsigned i = 0; i < numMaterials; ++i)
	{
		if (textures[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->textures->LoadTexture(path + file.data));
		}
	}
}

void Model::Update() {
	mesh.Draw(materials);
}


void Model::LoadMeshes(aiMesh** meshObjects, int numMeshes)
{
	meshes.reserve(numMeshes);
	for (unsigned i = 0; i < numMeshes; ++i)
	{
		mesh.LoadVBO(meshObjects[i]);
		mesh.LoadEBO(meshObjects[i]);
		mesh.CreateVAO();
	}
}