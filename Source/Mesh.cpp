#include "Mesh.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleCameraEditor.h"
#include "ModuleProgram.h"
#include <assimp/mesh.h>
#include "float4x4.h"

Mesh::Mesh()
{
}

// Destructor
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::LoadVBO(const aiMesh* mesh)
{
	LOG_ENGINE("Loading VBO...");
	vertexShaderSource = App->program->ReadFile("Shaders/helloWorld_vertexShader.glsl");
	fragmentShaderSource = App->program->ReadFile("Shaders/helloWorld_fragmentShader.glsl");
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);

	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	
	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	numVertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh)
{
	LOG_ENGINE("Loading EBO...");
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * 3;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	numIndices = mesh->mNumFaces * 3;
}

void Mesh::CreateVAO()
{
	LOG_ENGINE("Creating VAO...");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * numVertices));
}

void Mesh::Draw(const std::vector<unsigned>& model_textures, float3 position, float3 rotation, float scale)
{
	shaderProgram = App->program->CreateProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	float4x4 view = App->cameraEditor->GetViewMatrix();
	float4x4 proj = App->cameraEditor->GetProjectionMatrix();
	float4x4 model = float4x4::FromTRS(position,
		float4x4::identity, //Apply rotation
		float3(scale));

	glUseProgram(shaderProgram);

	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);//GlTrue to transpose matrices due we are not using OpenGl (using mathgeolib)
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, model_textures[materialIndex]);
	glUniform1i(glGetUniformLocation(shaderProgram, "diffuse"), 0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
}