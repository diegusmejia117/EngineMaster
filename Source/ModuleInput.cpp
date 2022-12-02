#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "ModuleCamera.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	//LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		//LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	Uint32 SDL_GetMouseState(int* x, int* y);
	float3 deltaPos = float3::zero;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
			//keyboard = SDL_GetKeyboardState(NULL);
            case SDL_QUIT:
                return UPDATE_STOP;

				break;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
				
		

			//case SDL_MOUSEWHEEL:

			//	if (sdlEvent.wheel.y > 0) // scroll up
			//	{
			//		deltaPos.z -= 0.2f;
			//	}

			//	else if (sdlEvent.wheel.y < 0) // scroll down
			//	{
			//		deltaPos.z += 0.2f;
			//	}
        }
		
		
    }
	
	if (keyboard[SDL_SCANCODE_W]) {
		deltaPos.z -= 0.2f;
	}
	if (keyboard[SDL_SCANCODE_S]) {
		deltaPos.z += 0.2f;
	}
	if (keyboard[SDL_SCANCODE_Q]) {
		deltaPos.y += 0.2f;
	}
	if (keyboard[SDL_SCANCODE_E]) {
		deltaPos.y -= 0.2f;
	}
	if (keyboard[SDL_SCANCODE_D]) {
		deltaPos.x += 0.2f;
	}
	if (keyboard[SDL_SCANCODE_A]) {
		deltaPos.x -= 0.2f;
	}

	if (keyboard[SDL_SCANCODE_F]) {
		App->camera->Focus();
	}
	App->camera->Translate(deltaPos);

	//rotate camera
	float3 deltaRot = float3::zero;
	float deltaAngle = 0.001f;
	/*float deltaAngle = deltaSpeed * deltaTime;*/

	if (SDL_MOUSEBUTTONDOWN) {
		if (keyboard[SDL_SCANCODE_LEFT]) {
			deltaRot.y += deltaAngle;
		}
		if (keyboard[SDL_SCANCODE_RIGHT]) {
			deltaRot.y -= deltaAngle;
		}
		if (keyboard[SDL_SCANCODE_UP]) {
			deltaRot.x += deltaAngle;
		}
		if (keyboard[SDL_SCANCODE_DOWN]) {
			deltaRot.x -= deltaAngle;
		}
	}
	App->camera->Rotate(deltaRot);

	
    return UPDATE_CONTINUE;
}


bool ModuleInput::CleanUp()
{
	//LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
