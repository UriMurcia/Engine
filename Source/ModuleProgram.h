#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	void CreateProgram(const char* shader_file_name);

	bool Init();
	update_status Update();
	bool CleanUp();

private:
};