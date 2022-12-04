#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "MathAll.h"

#include <vector>
#include <string>

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();
	
	bool Init();
	update_status Update();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	void ShowAboutWindow();
	void ShowLogWindow();
	void AddTextToLog(char *const text);
	void ShowFPSGraph();
	void ShowPropertiesWindow();
	void SetPropertiesWindow(const float3& position, const float& scale, const float3& rotation, const int& numTriangles, const int& numVertices);
	
	bool show_demo_window = true;
	bool show_another_window = false;

	std::vector<std::string> textsLog;
	std::vector<float> fpsLog;

private:
	ImVec4 titleColor = ImVec4(0.0f, 0.7f, 0.8f, 1.0f);


	float3 position = float3(0.f, 0.f, 0.f);
	float scale = 0.0f;
	float3 rotation = float3(0.f, 0.f, 0.f);
	int numTriangles = 0;
	int numVertices = 0;
};