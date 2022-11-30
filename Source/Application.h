#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "TimerNormal.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleCameraEditor;
class ModuleProgram;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleCameraEditor* cameraEditor = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTexture* textures = nullptr;

	TimerNormal* timer = new TimerNormal();
	int frameStart;
	int frameDuration;
	int dt = 0;

private:

	std::list<Module*> modules;


};

extern Application* App;
