#pragma once
#include "Module.h"
#include "Globals.h"
#include "Frustum.h"
#include "float3x3.h"
#include "AABB.h"

class ModuleCameraEditor : public Module
{
public:

	ModuleCameraEditor();
	~ModuleCameraEditor();

	bool Init();
	update_status Update();
	void SetFOV(float FOV);
	void SetAspectRatio(int screenWidth, int screenHeight);
	void SetPlaneDistances(float nearDistance, float farDistance);
	void SetPos(const float3& pos);
	void Translate(const vec& vect);
	void SetOrientation(const float3x3& up);
	void LookAt(const vec& target);
	void Rotate(const float3x3& rotationMatrix);
	void Rotate(const float2& rotate);
	void FocusCamera(const AABB& boundingBox);
	void Orbit(float xOrbit, float yOrbit, const vec& posToOrbit);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();


	Frustum frustum;
	float FOV = 90.f;
	float farPlaneDistance = 100.f;

private:
	float4x4 view, projection;
	int screenWidth = NULL, screenHeight = NULL;
};

