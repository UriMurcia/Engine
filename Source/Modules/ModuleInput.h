#pragma once
#include "Module.h"
#include "Globals.h"
typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	bool mouseLClicked = false;
	bool mouseRClicked = false;
	bool mouseMidClicked = false;
	float camMoveSpeed = 0.01f;
	float camRotSpeed = 0.005f;
	float zoomSpeed = 0.005f;

};