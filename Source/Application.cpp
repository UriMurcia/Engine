#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "ModuleCameraEditor.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"
#include "ModuleHardware.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(input = new ModuleInput());
	modules.push_back(exercise = new ModuleRenderExercise());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(cameraEditor = new ModuleCameraEditor());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(textures = new ModuleTexture());
	modules.push_back(hardware = new ModuleHardware());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }

	delete timer;
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Start();

	timer->Start();
	frameStart = timer->Read();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	int timePreviousFrame = frameStart;
	frameStart = timer->Read();
	dt = frameStart - timePreviousFrame;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	frameDuration = timer->Read() - frameStart;


	if (timer->limitTimeFrame > frameDuration) {
		SDL_Delay(timer->limitTimeFrame - frameDuration);
	}
	
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
