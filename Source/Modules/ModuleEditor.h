#pragma once
#include "Module.h"
#include "Globals.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "MathAll.h"


#include "EditorAbout.h"
#include "EditorLog.h"
#include "EditorProperties.h"
#include "EditorConfiguration.h"

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
	void ShowMenu();

	bool editorWindowsFocused = false;
	ImVec4 titleColor = ImVec4(0.0f, 0.7f, 0.8f, 1.0f);

	EditorAbout* editorAbout = new EditorAbout();
	EditorLog* editorLog = new EditorLog();
	EditorProperties* editorProperties = new EditorProperties();
	EditorConfiguration* editorConfiguration = new EditorConfiguration();

private:
	bool editorWindowsEnabled = true;
	bool quit = false;
};