#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	playerBody = new PhysBody(BODY_RECTANGLE);
	App->physics->bodies.add(playerBody);
	playerBody->position.x = 30;
	playerBody->position.y = SCREEN_HEIGHT - 160;
	playerBody->rec = {((int) playerBody->position.x - 25),((int) playerBody->position.y -25), 50, 50 };
	playerBody->mass = 10;
	playerBody->restitutionCoeff = 0.5f;
	playerBody->frictionCoeff = 0.09f;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		playerBody->velocity.x += speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		playerBody->velocity.x -= speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		playerBody->acceleration.y -= 20.0f;
		
	}
		
	
	return UPDATE_CONTINUE;
}
update_status ModulePlayer::Update()
{
	
	
	
	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate()
{
	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(App->renderer->renderer, &playerBody->rec);
	
	return UPDATE_CONTINUE;
}



