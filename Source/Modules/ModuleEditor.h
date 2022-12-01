#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

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
	
	bool show_demo_window = true;
	bool show_another_window = false;

	std::vector<std::string> textsLog;
	std::vector<float> fpsLog;
};