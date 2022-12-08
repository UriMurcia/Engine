#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	update_status Update();
	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	void SetWindowFullScreen();
	void SetWindowResizable();
	void SetWindowBorderless();

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;

	bool fullScreen = FULLSCREEN;
	bool resizableScreen = RESIZABLE_SCREEN;
	bool borderlessScreen = BORDERLESS_SCREEN;
};

#endif // __ModuleWindow_H__