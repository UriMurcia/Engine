#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

#include <iostream>

ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}

GLuint createShader(const char* shaderString, int shaderType, int success, char* infoLog) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderString, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		return shader;
	}

}

void CreateProgram(const char* vertexShaderString, const char* fragmentShaderString) {

	int success;
	char infoLog[512];
	GLuint vertexShader = createShader(vertexShaderString, GL_VERTEX_SHADER, success, infoLog);
	GLuint fragmentShader = createShader(fragmentShaderString, GL_FRAGMENT_SHADER, success, infoLog);


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
