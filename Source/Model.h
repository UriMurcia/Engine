#pragma once
#include "Globals.h"
#include "assimp/scene.h"
#include "DirectXTex.h"


#include <vector>

class Model
{
public:

	Model();
	~Model();

	void Load(const char* file_name);
	void LoadMaterials(const aiScene* scene);
	void LoadTextures(aiMaterial** materials, int numMaterials);
	void LoadMeshes(aiMesh** meshes, int numMeshes);

	std::vector<DirectX::ScratchImage> materials;
};

