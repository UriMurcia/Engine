#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleWindow.h"

#include <fstream>
#include <iostream>

ModuleProgram::ModuleProgram()
{
}

// Destructor
ModuleProgram::~ModuleProgram()
{}

GLuint ModuleProgram::CreateShader(const char* shaderString, int shaderType) {
	int success;
	char infoLog[512];

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

GLuint ModuleProgram::CreateProgram(const char* vertexShaderString, const char* fragmentShaderString) {

	GLuint vertexShader = CreateShader(vertexShaderString, GL_VERTEX_SHADER);
	GLuint fragmentShader = CreateShader(fragmentShaderString, GL_FRAGMENT_SHADER);
	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	return shaderProgram;
}


std::string ModuleProgram::ReadFile(std::string path) {

	std::string fileContent;
	std::ifstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		fileContent.append(line + "\n");
	}

	fileStream.close();

	return fileContent;
}
