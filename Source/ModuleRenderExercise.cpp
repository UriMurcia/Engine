#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"

#include <string>

ModuleRenderExercise::ModuleRenderExercise()
{}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

bool ModuleRenderExercise::Init() {

    this->moduleProgram = new ModuleProgram();

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    std::string vertexShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_vertexShader.glsl");
    std::string fragmentShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_fragmentShader.glsl");

	shaderProgram = this->moduleProgram->CreateProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());


    //calculem matrius
    //model = 


    return true;
}

update_status ModuleRenderExercise::Update() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glUseProgram(shaderProgram);

    glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(0, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(0, 1, GL_TRUE, &projection[0][0]);


	glDrawArrays(GL_TRIANGLES, 0, 3);

    return UPDATE_CONTINUE;
}
