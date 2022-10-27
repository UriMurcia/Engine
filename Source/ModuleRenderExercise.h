#pragma once
#include "Module.h"
#include "Globals.h"
#include <glew.h>

typedef unsigned __int8 Uint8;

class ModuleProgram;

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status Update();
	bool CleanUp();

	
};