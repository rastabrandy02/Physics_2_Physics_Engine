#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Ent_Enemy_1.h"
#include "PhysBody.h"

Ent_Enemy_1::Ent_Enemy_1(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{

	this->body = b;
	body->position = startPosition;
	this->damage = damage;
}

Ent_Enemy_1::~Ent_Enemy_1()
{}

// Load assets
bool Ent_Enemy_1::Start()
{

	return UPDATE_CONTINUE;
}

// Unload assets
bool Ent_Enemy_1::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status Ent_Enemy_1::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
update_status Ent_Enemy_1::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}
update_status Ent_Enemy_1::PostUpdate(float dt)
{
	App->renderer->Blit(App->entity_handler->tex_pengu, body->rec.x, body->rec.y, NULL);
	return UPDATE_CONTINUE;
}

void Ent_Enemy_1::OnCollision(PhysBody* body1, PhysBody* body2)
{

}

