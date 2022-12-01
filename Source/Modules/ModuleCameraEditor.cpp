#include "ModuleCameraEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "MathAll.h"

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

void ModuleCameraEditor::Translate(vec vect) {
    vec z = frustum.Front().Normalized() * vect.z;
    vec x = frustum.WorldRight().Normalized() * vect.x;
    vec y = vec(0, -vect.y, 0);
    vec xyz = x + y + z;

    float4x4 translationMat = float4x4(float3x4(float3x3::identity, xyz));

    frustum.SetPos((translationMat * float4(frustum.Pos(), 1.0f)).xyz());
}

void ModuleCameraEditor::SetOrientation(float3x3 up) {
    vec oldUp = frustum.Up().Normalized();
    frustum.SetUp(up.MulDir(oldUp));
}

void ModuleCameraEditor::LookAt(float3x3 front) {
    vec oldFront = frustum.Front().Normalized();
    frustum.SetFront(front.MulDir(oldFront));
}

void ModuleCameraEditor::Rotate(float2 rotation) {
    float3x3 x = float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), rotation.x);
    float3x3 y = float3x3(Cos(rotation.y), 0.0f, Sin(rotation.y), 0.0f, 1.0f, 0.0f, -Sin(rotation.y), 0.0f, Cos(rotation.y));
    float3x3 xy = x * y;

    vec oldUp = frustum.Up().Normalized();
    vec oldFront = frustum.Front().Normalized();

    float3 newUp = xy.MulDir(oldUp);

    if (newUp.y > 0.f) {
        frustum.SetUp(xy.MulDir(oldUp));
        frustum.SetFront(xy.MulDir(oldFront));
    }
}

void ModuleCameraEditor::FocusCamera(float3x3 positionToLook, float modelWidth, float modelHeight) {
    //float distance = sphere.radius / sin(fov / 2);
    //float3 eyePoint = sphere.centerPoint - distance * camera.frontVector;

    LookAt(positionToLook);
    float scaledBasis;
    if (modelWidth >= modelHeight) {
        scaledBasis = modelWidth / (2 * tan(frustum.HorizontalFov() / 2));
    }
    else {
        scaledBasis = modelHeight / (2 * tan(frustum.VerticalFov() / 2));
    }
    //SetPos(frustum.Pos() + scaledBasis);
}

float4x4 ModuleCameraEditor::GetProjectionMatrix() {
    return frustum.ProjectionMatrix();
}

float4x4 ModuleCameraEditor::GetViewMatrix() {
    return frustum.ViewMatrix();
}