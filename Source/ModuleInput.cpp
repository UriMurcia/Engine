#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include <imgui_impl_sdl.h>
#include "ModuleCameraEditor.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG_ENGINE("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_ENGINE("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
        }
    }


    keyboard = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		return UPDATE_STOP;
	}

	if (state[SDL_SCANCODE_W]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() + App->cameraEditor->frustum.Front().Normalized() * 0.2f);
	}
	if (state[SDL_SCANCODE_S]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() - App->cameraEditor->frustum.Front().Normalized() * 0.2f);
	}
	if (state[SDL_SCANCODE_A]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() - App->cameraEditor->frustum.WorldRight().Normalized() * 0.2f);
	}
	if (state[SDL_SCANCODE_D]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() + App->cameraEditor->frustum.WorldRight().Normalized() * 0.2f);
	}
	if (state[SDL_SCANCODE_Q]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() - float3(0, 0.1f, 0));
	}
	if (state[SDL_SCANCODE_E]) {
		App->cameraEditor->SetPos(App->cameraEditor->frustum.Pos() + float3(0, 0.1f, 0));
	}
	if (state[SDL_SCANCODE_UP]) {
		App->cameraEditor->Rotate(float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), 0.05f));
	}
	if (state[SDL_SCANCODE_DOWN]) {
		App->cameraEditor->Rotate(float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), -0.05f));
	}
	if (state[SDL_SCANCODE_LEFT]) {
		App->cameraEditor->Rotate(float3x3(Cos(0.05f), 0.0f, Sin(0.05f), 0.0f, 1.0f, 0.0f, -Sin(0.05f), 0.0f, Cos(0.05f)));
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		App->cameraEditor->Rotate(float3x3(Cos(-0.05f), 0.0f, Sin(-0.05f), 0.0f, 1.0f, 0.0f, -Sin(-0.05f), 0.0f, Cos(-0.05f)));
	}
	if (SDL_PollEvent(&event) != 0){
		if (event.type == SDL_MOUSEMOTION && event.motion.state & SDL_BUTTON_RMASK) {
			float rotateAmount = 0.05f * (pi / 180);
			App->cameraEditor->Rotate(float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), event.motion.y * rotateAmount));
			App->cameraEditor->Rotate(float3x3(Cos(event.motion.x * rotateAmount), 0.0f, Sin(event.motion.x * rotateAmount), 0.0f, 1.0f, 0.0f, -Sin(event.motion.x * rotateAmount), 0.0f, Cos(event.motion.x * rotateAmount)));
			
		}
	}

	

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG_ENGINE("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
