#pragma once
#include "Globals.h"
#include "assimp/scene.h"
#include "glew.h"
#include "Mesh.h"


#include <vector>

class Model
{
public:

	Model();
	~Model();

	void Update();
	void Load(const char* file_name);
	void LoadMaterials(aiMaterial** textures, int numMaterials);
	void LoadMeshes(aiMesh** meshes, int numMeshes);

	std::vector<GLuint> materials;
	std::vector<GLuint> meshes;
	Mesh mesh;
};

