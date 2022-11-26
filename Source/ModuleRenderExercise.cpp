#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "float3x3.h"
#include "ModuleCameraEditor.h"
#include "ModuleTexture.h"

#include <vector>


ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);
}

bool ModuleRenderExercise::Init() {
    
    this->moduleProgram = new ModuleProgram();
    this->moduleTexture = new ModuleTexture();

    /*float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };*/
    float vertices[] = {
         -1.0f, -1.0f, 0.0f, // v0 pos
         1.0f, 1.0f, 0.0f, // v1 pos
         -1.0f, 1.0f, 0.0f, // v2 pos
         -1.0f, -1.0f, 0.0f, // v3 pos
         1.0f, -1.0f, 0.0f, // v4 pos
         1.0f, 1.0f, 0.0f, // v5 pos

         0.0f, 0.0f, // v0 texcoord
         1.0f, 1.0f, // v1 texcoord
         0.0f, 1.0f, // v2 texcoord
         0.0f, 0.0f, // v3 texcoord
         1.0f, 0.0f, // v3 texcoord
         1.0f, 1.0f // v3 texcoord
    };


    /*texture = moduleTexture->LoadTexture("Images/Test-image-Baboon.ppm");

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    std::string vertexShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_vertexShader.glsl");
    std::string fragmentShaderSource = this->moduleProgram->ReadFile("Shaders/helloWorld_fragmentShader.glsl");

	shaderProgram = this->moduleProgram->CreateProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
        float4x4::identity,
        float3(1.0f));*/


    model3d.Load("GameObjects/BakerHouse.fbx");



    return true;
}

update_status ModuleRenderExercise::Update() {
    model3d.Update();
    //Program
    /*glUseProgram(shaderProgram);

    projection = App->cameraEditor->GetProjectionMatrix();
    view = App->cameraEditor->GetViewMatrix();

    glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);//GlTrue to transpose matrices due we are not using OpenGl (using mathgeolib)
    glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(0, 1, GL_TRUE, &projection[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Texture

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 6 * 3));
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, texture);


    glDrawArrays(GL_TRIANGLES, 0, 3 * 2);*/

    return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate() {



    return UPDATE_CONTINUE;
}