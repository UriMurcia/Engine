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


    model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
        float4x4::RotateZ(pi / 4.0f),
        float3(2.0f, 1.0f, 0.0f));


    return true;
}

update_status ModuleRenderExercise::Update() {
    
    glUseProgram(shaderProgram);


    //App->cameraEditor->Rotate(float3x3(1.0f, 0.0f, 0.0f,     0.0f, Cos(0.01f), -Sin(0.01f),     0.0f, Sin(0.01f), Cos(0.01f)));
    App->cameraEditor->Rotate(float3x3(Cos(0.01f), 0.0f, Sin(0.01f),     0.0f, 1.0f, 0.0f,     -Sin(0.01f), 0.0f, Cos(0.01f)));
    //App->cameraEditor->Rotate(float3x3(Cos(0.01f), -Sin(0.01f), 0.0f,     Sin(0.01f), Cos(0.01f), 0.0f,     0.0f, 0.0f, 1.0f));

    projection = App->cameraEditor->GetProjectionMatrix();
    view = App->cameraEditor->GetViewMatrix();

    glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);//GlTrue to transpose matrices due we are not using OpenGl (we use mathgeolib)
    glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(0, 1, GL_TRUE, &projection[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    i = i+0.01f;

    return UPDATE_CONTINUE;
}