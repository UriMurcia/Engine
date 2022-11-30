#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include <imgui_impl_sdl.h>
#include "ModuleCameraEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderExercise.h"

#define CAM_SPEED 0.02f
#define FAST_CAM_SPEED CAM_SPEED * 2.0f

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
	float dt = (float)App->dt;

	char* droppedFile;

    SDL_Event sdlEvent;
	const Uint8* state = SDL_GetKeyboardState(NULL);

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
			case SDL_MOUSEBUTTONDOWN:
				if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
					mouseRClicked = true;
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
					mouseLClicked = true;
				if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
					mouseMidClicked = true;
				break;
			case SDL_MOUSEBUTTONUP:
				if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
					mouseRClicked = false; 
				if (sdlEvent.button.button == SDL_BUTTON_LEFT)
					mouseLClicked = false;
				if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
					mouseMidClicked = false;
				break;
			case SDL_MOUSEMOTION:
				if (mouseRClicked || mouseLClicked || mouseMidClicked) {
					//SDL_SetRelativeMouseMode(SDL_TRUE);
					if ((mouseLClicked || mouseMidClicked) && !state[SDL_SCANCODE_LALT]) {
						//App->cameraEditor->Translate(vec(-camMoveSpeed * sdlEvent.motion.xrel, -camMoveSpeed * sdlEvent.motion.yrel, 0));
					}
					if (mouseRClicked && !mouseLClicked && !mouseMidClicked && !state[SDL_SCANCODE_LALT]) {
						float rotateAmount = -camRotSpeed * (pi / 180);
						App->cameraEditor->Rotate(float2(sdlEvent.motion.yrel * rotateAmount, 0.f));
						App->cameraEditor->Rotate(float2(0.f, sdlEvent.motion.xrel * rotateAmount));
					}
					/*if (state[SDL_SCANCODE_LALT] && mouseLClicked) {
						App->cameraEditor->Rotate(float3x3::RotateAxisAngle(App->cameraEditor->frustum.WorldRight().Normalized(), camRotSpeed * sdlEvent.motion.xrel));
					}*/
					if (state[SDL_SCANCODE_LALT] && mouseRClicked) {
						App->cameraEditor->Translate(vec(0, 0, camMoveSpeed * sdlEvent.motion.xrel));
					}
				}
				else {
					//SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				break;
			case SDL_DROPFILE:
				droppedFile = sdlEvent.drop.file;
				App->exercise->LoadModel3D(droppedFile);
				SDL_free(droppedFile);
				break;
        }
    }
	


	if (state[SDL_SCANCODE_ESCAPE]) {
		return UPDATE_STOP;
	}
	if (state[SDL_SCANCODE_W]) {
		App->cameraEditor->Translate(vec(0.f, 0.f, camMoveSpeed * dt));
	}
	if (state[SDL_SCANCODE_S]) {
		App->cameraEditor->Translate(vec(0.f, 0.f, -camMoveSpeed * dt));
	}
	if (state[SDL_SCANCODE_A]) {
		App->cameraEditor->Translate(vec(-camMoveSpeed * dt, 0.f, 0.f));
	}
	if (state[SDL_SCANCODE_D]) {
		App->cameraEditor->Translate(vec(camMoveSpeed * dt, 0.f, 0.f));
	}
	if (state[SDL_SCANCODE_Q]) {
		App->cameraEditor->Translate(vec(0.f, camMoveSpeed * dt, 0.f));
	}
	if (state[SDL_SCANCODE_E]) {
		App->cameraEditor->Translate(vec(0.f, -camMoveSpeed * dt, 0.f));
	}

	if (state[SDL_SCANCODE_UP]) {
		App->cameraEditor->Rotate(float2(camRotSpeed, 0.f));
	}
	if (state[SDL_SCANCODE_DOWN]) {
		App->cameraEditor->Rotate(float2(-camRotSpeed, 0.f));
	}
	if (state[SDL_SCANCODE_LEFT]) {
		App->cameraEditor->Rotate(float2(0.f, camRotSpeed));
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		App->cameraEditor->Rotate(float2(0.f, -camRotSpeed));
	}

	if (state[SDL_SCANCODE_LSHIFT]) {
		camMoveSpeed = FAST_CAM_SPEED;
	}
	else {
		camMoveSpeed = CAM_SPEED;
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
