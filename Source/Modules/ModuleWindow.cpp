#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG_ENGINE("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ENGINE("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
			fullScreen = true;
		}
		if (BORDERLESS_SCREEN == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
			borderlessScreen = true;
		}
		if (RESIZABLE_SCREEN == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
			resizableScreen = true;
		}
		if (FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}



		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		

		if(window == NULL)
		{
			LOG_ENGINE("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}



update_status ModuleWindow::Update()
{

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG_ENGINE("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}



void ModuleWindow::SetWindowFullScreen() {
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	resizableScreen = false;
	fullScreen = true;
	borderlessScreen = false;
}

void  ModuleWindow::SetWindowResizable() {
	SDL_SetWindowResizable(window, SDL_TRUE);
	SDL_SetWindowFullscreen(window, SDL_FALSE);
	SDL_SetWindowBordered(window, SDL_TRUE);
	resizableScreen = true;
	fullScreen = false;
	borderlessScreen = false;
}

void  ModuleWindow::SetWindowBorderless() {
	SDL_SetWindowBordered(window, SDL_FALSE);
	resizableScreen = false;
	fullScreen = false;
	borderlessScreen = true;
}