#include "Model.h"
#include "Application.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

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
		
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		LOG_ENGINE("Error loading %s: %s", file_name, aiGetErrorString());
	}
}
