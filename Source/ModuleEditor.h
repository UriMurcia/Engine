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
	void showLogWindow();
	void AddTextToLog(char *const text);
	
	bool show_demo_window = true;
	bool show_another_window = false;

	ImVector<char*> textsLog;

};