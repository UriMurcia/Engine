#pragma once
#include "Module.h"
#include "Globals.h"
#include "Frustum.h"
#include "float3x3.h"

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
	void SetOrientation(float3x3 up);
	void LookAt(float3x3 front);
	void Rotate(float3x3 rotate);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();


	Frustum frustum;
	float4x4 view, projection;
	int screenWidth = NULL, screenHeight = NULL;
};

