#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"
#include "MathAll.h"
#include "float4x4.h"


typedef unsigned __int8 Uint8;

class ModuleProgram;

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status Update();
	float4x4 LookAt(float3 eye, float3 target, float3 upVector);

	ModuleProgram* moduleProgram = nullptr;
	GLuint VBO;
	GLuint shaderProgram;
	float4x4 model, view, projection;
	float i = 0.f;
	
};