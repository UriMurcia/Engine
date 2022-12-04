#pragma once
#include "Globals.h"
#include "assimp/scene.h"
#include "glew.h"
#include "Mesh.h"
#include "MathAll.h"
#include "AABB.h"


#include <vector>

class Model
{
public:

	Model();
	~Model();

	void Update();
	void Load(const char* file_name);
	void LoadMaterials(aiMaterial** textures, int numMaterials, const char* file_name);
	void LoadMeshes(aiMesh** meshes, int numMeshes);

	std::vector<GLuint> materials;
	std::vector<Mesh*> meshes;
	//Mesh mesh;
	float3 position = float3(2.0f, 0.f, 0.f);
	float scale = 1.0f;
	float3 rotation = float3(0.f, 0.f, 0.f);
	int numTriangles = 0;
	int numVertices = 0;
	vec minVertex;
	vec maxVertex;
	AABB* boundingBox;
};

