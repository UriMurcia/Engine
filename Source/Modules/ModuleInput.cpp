#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include <imgui_impl_sdl.h>
#include "ModuleCameraEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"


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
	char* droppedFile;

    SDL_Event sdlEvent;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	float dt = (float)App->dt;

	float finalCamVelocity = dt * camMoveSpeed;
	if (state[SDL_SCANCODE_LSHIFT])
		finalCamVelocity *= 2;


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
				if (!App->editor->editorWindowsFocused){
					if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
						mouseRClicked = true;
					if (sdlEvent.button.button == SDL_BUTTON_LEFT)
						mouseLClicked = true;
					if (sdlEvent.button.button == SDL_BUTTON_MIDDLE)
						mouseMidClicked = true;
				}
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
					//Rotate camera with RClick
					if (mouseRClicked && !mouseLClicked && !mouseMidClicked && !state[SDL_SCANCODE_LALT]) {
						float rotateAmount = -camRotSpeed * dt * (pi / 180);
						App->cameraEditor->Rotate(float2(sdlEvent.motion.xrel * rotateAmount, sdlEvent.motion.yrel * rotateAmount));
					}
					//Zoom camera with Alt+RClick
					if (state[SDL_SCANCODE_LALT] && mouseRClicked && !mouseLClicked) {
						App->cameraEditor->Translate(vec(0, 0, finalCamVelocity * sdlEvent.motion.xrel));
					}
					//Orbit camera around object with Alt+LClick
					if (state[SDL_SCANCODE_LALT] && mouseLClicked && !mouseRClicked) {
						float rotateAmount = -camRotSpeed * dt * (pi / 180);
						App->cameraEditor->Orbit(sdlEvent.motion.xrel * rotateAmount, sdlEvent.motion.yrel * rotateAmount, App->exercise->models3d[0]->position);
					}
				}
				break;
			case SDL_MOUSEWHEEL:
				//Zoom camera with Mouse Wheel
				if (!App->editor->editorWindowsFocused) {
					if (sdlEvent.wheel.y > 0)
						App->cameraEditor->Translate(vec(0, 0, zoomSpeed * dt));
					if (sdlEvent.wheel.y < 0)
						App->cameraEditor->Translate(vec(0, 0, -zoomSpeed * dt));
				}
				break;
			case SDL_DROPFILE:
				//Load 3D Models (.fbx) Dropped on the screen
				droppedFile = sdlEvent.drop.file;
				App->exercise->LoadModel3D(droppedFile);
				SDL_free(droppedFile);
				break;
        }
    }

	//Move camera
	if (state[SDL_SCANCODE_W] && mouseRClicked) {
		App->cameraEditor->Translate(vec(0.f, 0.f, finalCamVelocity));
	}
	if (state[SDL_SCANCODE_S] && mouseRClicked) {
		App->cameraEditor->Translate(vec(0.f, 0.f, -finalCamVelocity));
	}
	if (state[SDL_SCANCODE_A] && mouseRClicked) {
		App->cameraEditor->Translate(vec(-finalCamVelocity, 0.f, 0.f));
	}
	if (state[SDL_SCANCODE_D] && mouseRClicked) {
		App->cameraEditor->Translate(vec(finalCamVelocity, 0.f, 0.f));
	}
	if (state[SDL_SCANCODE_Q] && mouseRClicked) {
		App->cameraEditor->Translate(vec(0.f, finalCamVelocity, 0.f));
	}
	if (state[SDL_SCANCODE_E] && mouseRClicked) {
		App->cameraEditor->Translate(vec(0.f, -finalCamVelocity, 0.f));
	}

	//Rotate camera
	if (state[SDL_SCANCODE_UP]) {
		App->cameraEditor->Rotate(float2(0.f, camRotSpeed * dt));
	}
	if (state[SDL_SCANCODE_DOWN]) {
		App->cameraEditor->Rotate(float2(0.f, -camRotSpeed * dt));
	}
	if (state[SDL_SCANCODE_LEFT]) {
		App->cameraEditor->Rotate(float2(camRotSpeed * dt, 0.f));
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		App->cameraEditor->Rotate(float2(-camRotSpeed * dt, 0.f));
	}

	//Focus object
	if (state[SDL_SCANCODE_F]) {
		App->cameraEditor->FocusCamera(*App->exercise->models3d[0]->boundingBox);
	}

	//Quit
	if (state[SDL_SCANCODE_ESCAPE]) {
		return UPDATE_STOP;
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
