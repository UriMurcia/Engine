#pragma once
#include "Globals.h"
#include "assimp/scene.h"
#include "glew.h"
#include "MathAll.h"

#include <vector>

class Mesh
{
public:

	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures, float3 position, float3 rotation, float scale);

	GLuint ebo = 0;
	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint shaderProgram = 0;
	int numIndices = 0;
	int numVertices = 0;
	int materialIndex = 0;
	int numFaces = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	std::string vertexShaderSource, fragmentShaderSource;
};
