#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"

ModuleRenderExercise::ModuleRenderExercise()
{}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{}

bool ModuleRenderExercise::Init() {
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

	this->program = new ModuleProgram();
	this->program->CreateProgram(vertexShaderSource, fragmentShaderSource);

    return true;
}

update_status ModuleRenderExercise::Update() {

    return UPDATE_CONTINUE;
}


bool ModuleRenderExercise::CleanUp() {
    return true;
}