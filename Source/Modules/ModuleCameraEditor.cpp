#include "ModuleCameraEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "MathAll.h"
#include "Sphere.h"

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
    frustum.SetViewPlaneDistances(0.1f, farPlaneDistance);
    frustum.SetHorizontalFovAndAspectRatio((pi / 180) * FOV, (float)screenWidth / (float)screenHeight);
    

    projection = frustum.ProjectionMatrix();

    view = frustum.ViewMatrix();

    return true;
}

update_status ModuleCameraEditor::Update() {
    SDL_GetWindowSize(App->window->window, &screenWidth, &screenHeight);
    frustum.SetHorizontalFovAndAspectRatio((pi / 180) * FOV, (float)screenWidth / (float)screenHeight);
    projection = frustum.ProjectionMatrix();
    view = frustum.ViewMatrix();

    dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
    dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::White);
    App->debugDraw->Draw(view, projection, screenWidth, screenHeight);
    
    return UPDATE_CONTINUE;
}


void ModuleCameraEditor::SetFOV(float FOV) {
    this->FOV = FOV;
}

void ModuleCameraEditor::SetAspectRatio(int screenWidth, int screenHeight) {
    frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), (float)screenWidth / (float)screenHeight);
}

void ModuleCameraEditor::SetPlaneDistances(float nearDistance, float farDistance) {
    farPlaneDistance = farDistance;
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

void ModuleCameraEditor::LookAt(vec target) {

    float3 direction = target - frustum.Pos();
    direction = direction.Normalized();

    vec y = vec::unitY;

    float3x3 rotationMat = float3x3::LookAt(frustum.Front().Normalized(), direction, frustum.Up().Normalized(), y);
    Rotate(rotationMat);
}

void ModuleCameraEditor::Rotate(float3x3 rotationMatrix) {
    vec oldUp = frustum.Up().Normalized();
    vec oldFront = frustum.Front().Normalized();

    frustum.SetUp(rotationMatrix * oldUp);
    frustum.SetFront(rotationMatrix * oldFront);
}


void ModuleCameraEditor::Rotate(float2 rotation) {
    float3x3 x = float3x3(Cos(rotation.x), 0.0f, Sin(rotation.x), 0.0f, 1.0f, 0.0f, -Sin(rotation.x), 0.0f, Cos(rotation.x));
    float3x3 y = float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), rotation.y);
    float3x3 xy = x * y;

    vec oldUp = frustum.Up().Normalized();
    vec oldFront = frustum.Front().Normalized();

    float3 newUp = xy.MulDir(oldUp);

    if (newUp.y > 0.f) {
        frustum.SetUp(xy.MulDir(oldUp));
        frustum.SetFront(xy.MulDir(oldFront));
    }
}

void ModuleCameraEditor::FocusCamera(AABB boundingBox) {
    Sphere boundingSphere = boundingBox.MinimalEnclosingSphere();

    float radius = boundingSphere.r;
    double fov = frustum.HorizontalFov();
    double camDistance = radius / sin(fov / 2.0);
    vec camDirection = (boundingSphere.pos - frustum.Pos()).Normalized();

    SetPos(boundingSphere.pos - (camDirection * camDistance));
    LookAt(boundingSphere.pos);

}


void ModuleCameraEditor::Orbit(float xOrbit, float yOrbit, vec posToOrbit) {

    Rotate(float2(xOrbit, yOrbit));
    
    vec camDirection = frustum.Front().Normalized();
    float camDistance = posToOrbit.Distance(frustum.Pos());

    SetPos(posToOrbit - (camDirection * camDistance));
}

float4x4 ModuleCameraEditor::GetProjectionMatrix() {
    return frustum.ProjectionMatrix();
}

float4x4 ModuleCameraEditor::GetViewMatrix() {
    return frustum.ViewMatrix();
}