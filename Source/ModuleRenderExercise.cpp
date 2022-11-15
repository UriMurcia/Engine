#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "float3x3.h"
#include "ModuleCameraEditor.h"

#include <vector>


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

    /*float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };*/
    float vertices[] = {
         -1.0f, -1.0f, 0.0f, // v0 pos
         1.0f, -1.0f, 0.0f, // v1 pos
         1.0f, 1.0f, 0.0f, // v2 pos
         -1.0f, 1.0f, 0.0f, // v3 pos

         0.0f, 0.0f, // v0 texcoord
         1.0f, 0.0f, // v1 texcoord
         1.0f, 1.0f, // v2 texcoord
         0.0f, 1.0f // v3 texcoord
    };


    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    std::string vertexShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_vertexShader.glsl");
    std::string fragmentShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_fragmentShader.glsl");

	shaderProgram = this->moduleProgram->CreateProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
        float4x4::RotateZ(pi / 4.0f),
        float3(2.0f, 1.0f, 0.0f));


    return true;
}

update_status ModuleRenderExercise::Update() {
    
    glUseProgram(shaderProgram);

    projection = App->cameraEditor->GetProjectionMatrix();
    view = App->cameraEditor->GetViewMatrix();

    glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);//GlTrue to transpose matrices due we are not using OpenGl (using mathgeolib)
    glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(0, 1, GL_TRUE, &projection[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * 4 * sizeof(float)));

    glDrawArrays(GL_QUADS, 0, 3 * 2);

    return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate() {



    return UPDATE_CONTINUE;
}