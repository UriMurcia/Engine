#pragma once
#include "Module.h"
#include "Globals.h"
#include <glew.h>

typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	void CreateProgram(const char* vertexShaderString, const char* fragmentShaderString);
	GLuint createShader(const char* shaderString, int shaderType);
	


};