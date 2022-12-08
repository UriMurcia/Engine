#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>

class ModuleHardware : public Module
{

	
public:
	ModuleHardware();
	~ModuleHardware();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	char directXTexVersion[50] = "null";
	char sdlVersion[50] = "null";
	char assimpVersion[50] = "null";
	char glewVersion[50] = "null";
	char mathgeolibVersion[50] = "null";
	char imguiVersion[50] = "null";

	const char* gpuVendor = "null";
	const char* gpuRenderer = "null";
	const char* gpuOpenglVersion = "null";

	int cpuCount = 0;
	int cacheLineSize = 0;
	float ram = 0;

	float totalRam = 0;
	float currentRamAvailabe = 0;
	float ramUsed = 0;
};

