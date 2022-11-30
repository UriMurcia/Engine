#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"
#include "float4x4.h"
#include "Model.h"

#include <vector>

class ModuleProgram;
class ModuleTexture;

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status Update();
	update_status PostUpdate();
	void LoadModel3D(const char* file_name);

	ModuleProgram* moduleProgram = nullptr;
	ModuleTexture* moduleTexture = nullptr;
	GLuint VBO, shaderProgram;
	GLuint texture;
	float4x4 model, view, projection;
	std::vector<Model*> models3d;
};