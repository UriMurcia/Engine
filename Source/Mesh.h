#pragma once
#include "Globals.h"
#include "assimp/scene.h"
#include "glew.h"

#include <vector>

class Mesh
{
public:

	Mesh();
	~Mesh();

	void LoadVBO(const aiMesh* mesh);
	void LoadEBO(const aiMesh* mesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& model_textures);

	GLuint ebo, vao, vbo, shaderProgram;
	int num_indices, num_vertices;
	std::string vertexShaderSource, fragmentShaderSource;
	int material_index;
};
