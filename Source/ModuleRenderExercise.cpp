#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "Frustum.h"
#include "MathGeoLibFwd.h"
#include "MatrixProxy.h"
#include "Math/float3.h"
#include "Math/float2.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "debug_draw.hpp"
#include "ModuleWindow.h"
#include "Ray.h"

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


    //calculem matrius
    //model = 


    return true;
}

update_status ModuleRenderExercise::Update() {

    glUseProgram(shaderProgram);

    model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
        float4x4::RotateZ(pi / 4.0f),
        float3(2.0f, 1.0f, 0.0f));

    Frustum frustum;
    //type is private?
    //frustum.type = FrustumType::PerspectiveFrustum;
    frustum.SetPos(float3::zero);
    frustum.SetFront(-float3::unitZ);
    frustum.SetUp(float3::unitY);
    frustum.SetViewPlaneDistances(0.1f, 100.0f);
    frustum.SetVerticalFovAndAspectRatio(math::pi / 4.0f, 1.0f);
    frustum.SetHorizontalFovAndAspectRatio(2.f * atanf(tanf(90.0f * 0.5f) * 1.0f), 1.0f);
    projection = frustum.ProjectionMatrix();


    //view = LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY);
    

    view.LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY, float3::unitY);

    glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(2, 1, GL_TRUE, &projection[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

    dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
    dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Gray);
    int w;
    int h;
    SDL_GetWindowSize(App->window->window, &w, &h);
    App->debugDraw->Draw(view, projection, w, h);

    return UPDATE_CONTINUE;
}

float4x4 ModuleRenderExercise::LookAt(float3 eye, float3 target, float3 upVector) {
    float zaxis = (target - eye).Normalize();
    float3 f3zaxis = float3(zaxis);
    float xaxis = (upVector.Cross(f3zaxis)).Normalize();
    float3 f3xaxis = float3(xaxis);
    float3 f3yaxis = (f3xaxis.Cross(f3zaxis));

    f3zaxis.Neg();

    float4x4 viewMatrix = {
      float4(f3xaxis.x, f3xaxis.y, f3xaxis.z, -f3xaxis.Dot(eye)),
      float4(f3yaxis.x, f3yaxis.y, f3yaxis.z, -f3yaxis.Dot(eye)),
      float4(f3zaxis.x, f3zaxis.y, f3zaxis.z, -f3zaxis.Dot(eye)),
      float4(0, 0, 0, 1)
    };

    return viewMatrix;
}