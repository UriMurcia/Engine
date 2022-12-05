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
	void SetPos(float3 pos);
	void Translate(vec vect);
	void SetOrientation(float3x3 up);
	void LookAt(vec target);
	void Rotate(float3x3 rotationMatrix);
	void Rotate(float2 rotate);
	void FocusCamera(AABB boundingBox);
	void Orbit(float xOrbit, float yOrbit, vec posToOrbit);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();


	Frustum frustum;
	float4x4 view, projection;
	int screenWidth = NULL, screenHeight = NULL;
};

