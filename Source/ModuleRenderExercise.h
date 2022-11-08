#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"
#include "float4x4.h"


class ModuleProgram;

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status Update();

	ModuleProgram* moduleProgram = nullptr;
	GLuint VBO;
	GLuint shaderProgram;
	float4x4 model, view, projection;
	float i = 0.f;
	
};