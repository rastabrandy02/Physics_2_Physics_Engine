#include "Globals.h"
#include "Application.h"
#include "Ent_Bomb.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

Ent_Bomb::Ent_Bomb(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{
	

	this->body = b;
	body->position = startPosition;


	body->rec = { ((int)body->position.x - 25),((int)body->position.y - 25), 50, 50 };
	body->mass = 100;
	body->restitutionCoeff = 0.5f;
	body->liftCoeff = 0.1;


}

Ent_Bomb::~Ent_Bomb()
{

}

// Load assets
bool Ent_Bomb::Start()
{
	return UPDATE_CONTINUE;
}

// Unload assets
bool Ent_Bomb::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Ent_Bomb::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Ent_Bomb::Update(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Ent_Bomb::PostUpdate(float dt)
{
	App->renderer->Blit(App->projectile_handler->tex_bomb, body->rec.x, body->rec.y, NULL);
	//SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 90);
	//SDL_RenderFillRect(App->renderer->renderer, &body->rec);
	return UPDATE_CONTINUE;
}



