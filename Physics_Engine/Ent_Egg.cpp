#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Ent_Egg.h"
#include "PhysBody.h"

Ent_Egg::Ent_Egg(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{

	this->body = b;
	body->position = startPosition;
	this->damage = damage;
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
	App->renderer->Blit(App->entity_handler->tex_egg, body->rec.x, body->rec.y, &App->entity_handler->rec_egg);
	return UPDATE_CONTINUE;
}




void Ent_Egg::OnCollision(PhysBody* body1, PhysBody* body2)
{
	if ((body2->type == BodyType::BODY_RECTANGLE) && body2 != App->player->body && body2 != App->player->body && body2->type != EGG)
	{

		//App->entity_handler->DamageEntity(body2, damage);
		App->entity_handler->DeleteEntity(body);

	}

}