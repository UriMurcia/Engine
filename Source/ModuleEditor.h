#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

class ModuleRender;
class ModuleWindow;

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();
	
	bool Init();
	update_status Update();
	bool CleanUp();

};