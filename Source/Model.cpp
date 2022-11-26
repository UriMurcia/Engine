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
{}

void Model::Load(const char* file_name)
{
	const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{

		aiString file;
		LoadTextures(scene->mMaterials, scene->mNumMaterials);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file_name, aiGetErrorString());
	}
}


void Model::LoadMaterials(const aiScene* scene)
{
	aiString file;
	
	materials.reserve(scene->mNumMaterials);
	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->textures->LoadTexture(file.data));
		}
	}
}


void Model::LoadTextures(aiMaterial** materials, int numMaterialss)
{
	
}

void Model::LoadMeshes(aiMesh** meshes, int numMeshes)
{

}