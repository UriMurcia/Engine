#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleProgram::ModuleProgram()
{}

// Destructor
ModuleProgram::~ModuleProgram()
{}

// Called before render is available
bool ModuleProgram::Init()
{
}

// Called every draw update
update_status ModuleProgram::Update()
{

	return UPDATE_CONTINUE;
}


void CreateProgram(const char* shader_file_name) {

}


bool ModuleProgram::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
