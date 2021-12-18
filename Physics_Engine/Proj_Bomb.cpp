#include "Globals.h"
#include "Application.h"
#include "Proj_Bomb.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

Proj_Bomb::Proj_Bomb(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{
	

	this->body = b;
	body->position = startPosition;


	body->rec = { ((int)body->position.x - 25),((int)body->position.y - 25), 50, 50 };
	body->mass = 100;
	body->restitutionCoeff = 0.5f;
	body->liftCoeff = 0.1;


}

Proj_Bomb::~Proj_Bomb()
{

}

// Load assets
bool Proj_Bomb::Start()
{
	return UPDATE_CONTINUE;
}

// Unload assets
bool Proj_Bomb::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Proj_Bomb::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Proj_Bomb::Update(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Proj_Bomb::PostUpdate(float dt)
{
	App->renderer->Blit(App->projectile_handler->tex_bomb, body->rec.x, body->rec.y, NULL);
	//SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 90);
	//SDL_RenderFillRect(App->renderer->renderer, &body->rec);
	return UPDATE_CONTINUE;
}



