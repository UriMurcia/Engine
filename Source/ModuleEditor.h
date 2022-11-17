#pragma once
#include "Module.h"
#include "Globals.h"


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

	
	bool show_demo_window = true;
	bool show_another_window = false;

};