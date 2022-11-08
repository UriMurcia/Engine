#include "ModuleCameraEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"

ModuleCameraEditor::ModuleCameraEditor()
{}

ModuleCameraEditor::~ModuleCameraEditor()
{
}

bool ModuleCameraEditor::Init() {
    SDL_GetWindowSize(App->window->window, &screenWidth, &screenHeight);

    frustum.SetPos(float3(0, 3, 5.0f));
    frustum.SetFront(-float3::unitZ);
    frustum.SetUp(float3::unitY);
    frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum.SetViewPlaneDistances(0.1f, 100.0f);
    frustum.SetHorizontalFovAndAspectRatio((pi / 180) * 90.0f, (float)screenWidth / (float)screenHeight);

    projection = frustum.ProjectionMatrix();

    view = frustum.ViewMatrix();

    return true;
}

update_status ModuleCameraEditor::Update() {
    SDL_GetWindowSize(App->window->window, &screenWidth, &screenHeight);
    frustum.SetHorizontalFovAndAspectRatio((pi / 180) * 90.0f, (float)screenWidth / (float)screenHeight);
    projection = frustum.ProjectionMatrix();
    view = frustum.ViewMatrix();

    dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
    dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::White);
    App->debugDraw->Draw(view, projection, screenWidth, screenHeight);
    return UPDATE_CONTINUE;
}


void ModuleCameraEditor::SetFOV(float FOV) {
    frustum.SetHorizontalFovAndAspectRatio((pi / 180) * FOV, frustum.AspectRatio());
}

void ModuleCameraEditor::SetAspectRatio(int screenWidth, int screenHeight) {
    frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), (float)screenWidth / (float)screenHeight);
}

void ModuleCameraEditor::SetPlaneDistances(float nearDistance, float farDistance) {
    frustum.SetViewPlaneDistances(nearDistance, farDistance);
}

void ModuleCameraEditor::SetPos(float3 pos) {
    frustum.SetPos(pos);
}



//camera horizontal rotate: y world
//camera vertical rotate: y camera

//Needs to be fixed
void ModuleCameraEditor::SetOrientation(float3x3 up) {
    vec oldUp = frustum.Up().Normalized();
    frustum.SetUp(up.MulDir(oldUp));
}

//Needs to be fixed
void ModuleCameraEditor::LookAt(float3x3 front) {
    vec oldFront = frustum.Front().Normalized();
    frustum.SetFront(front.MulDir(oldFront)); //.MultDir(oldFront);
}

void ModuleCameraEditor::Rotate(float3x3 rotation) {
    vec oldUp = frustum.Up().Normalized();
    vec oldFront = frustum.Front().Normalized();
    frustum.SetUp(rotation.MulDir(oldUp));
    frustum.SetFront(rotation.MulDir(oldFront)); //.MultDir(oldFront);
}



float4x4 ModuleCameraEditor::GetProjectionMatrix() {
    return frustum.ProjectionMatrix();
}

float4x4 ModuleCameraEditor::GetViewMatrix() {
    return frustum.ViewMatrix();
}