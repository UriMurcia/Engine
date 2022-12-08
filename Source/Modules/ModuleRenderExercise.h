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
	void LoadModel3D(const char* file_name);

	std::vector<Model*> models3d;
};