#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Ent_Egg.h"
#include "PhysBody.h"

Ent_Egg::Ent_Egg(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{

	this->body = b;
	body->position = startPosition;


	body->rec = { ((int)body->position.x - 25),((int)body->position.y - 25), 50, 50 };
	body->mass = 100;
	body->restitutionCoeff = 0.5f;
	body->liftCoeff = 0.3f;
}

Ent_Egg::~Ent_Egg()
{}

// Load assets
bool Ent_Egg::Start()
{

	return UPDATE_CONTINUE;
}

// Unload assets
bool Ent_Egg::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Ent_Egg::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Ent_Egg::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}
update_status Ent_Egg::PostUpdate(float dt)
{
	App->renderer->Blit(App->projectile_handler->tex_egg, body->rec.x, body->rec.y, NULL);
	return UPDATE_CONTINUE;
}



