#pragma once
#include "Module.h"
#include "Globals.h"
#include <glew.h>
#include <string>
typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	GLuint CreateProgram(const char* vertexShaderString, const char* fragmentShaderString);
	GLuint CreateShader(const char* shaderString, int shaderType);
	std::string ReadFile(std::string path);

};