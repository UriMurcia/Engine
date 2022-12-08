#include "ModuleHardware.h"

#include "Globals.h"
#include "Application.h"

#include "SDL_version.h"
#include "SDL_cpuinfo.h"
#include "SDL_video.h"
#include "glew.h"
#include "assimp/version.h"
#include "imgui.h"

ModuleHardware::ModuleHardware()
{
}

// Destructor
ModuleHardware::~ModuleHardware()
{
}

// Called before render is available
bool ModuleHardware::Init()
{
	SDL_version sdlVersions;
	SDL_VERSION(&sdlVersions);

	sprintf_s(directXTexVersion, "1.9.7");
	sprintf_s(sdlVersion, "%i.%i.%i", sdlVersions.major, sdlVersions.minor, sdlVersions.patch);
	sprintf_s(assimpVersion, "%i.%i.%i", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
	sprintf_s(glewVersion, "%i.%i.%i", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
	sprintf_s(mathgeolibVersion, "2.0");
	sprintf_s(imguiVersion, "%s", IMGUI_VERSION);

	gpuVendor = (const char*)glGetString(GL_VENDOR);
	gpuRenderer = (const char*)glGetString(GL_RENDERER);
	gpuOpenglVersion = (const char*)glGetString(GL_VERSION);

	cpuCount = SDL_GetCPUCount();
	cacheLineSize = SDL_GetCPUCacheLineSize();
	ram = SDL_GetSystemRAM() / 1000.0f;

	return true;
}

update_status ModuleHardware::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleHardware::Update()
{
	int currentRamAvailabeKb;
	int totalRamKb;
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currentRamAvailabeKb);
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalRamKb);

	currentRamAvailabe = currentRamAvailabeKb / 1000.0f;
	totalRam = totalRamKb / 1000.0f;
	ramUsed = totalRam - currentRamAvailabe;

	return UPDATE_CONTINUE;
}

update_status ModuleHardware::PostUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleHardware::CleanUp()
{

	return true;
}