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
	if (aliveTime <= 0)
	{
		App->entity_handler->DeleteEntity(body);
	}
	else
	{
		aliveTime--;

	}

	if (time <= 0)
	{

		if (birdTime && throws > 0)
		{
			throws--;
			p2Point<float> force(3, 10);
			p2Point<float> z(0, 0);

			App->entity_handler->CreateEntity(EntityType::BOMB, body->position.x, body->position.y + 30, z, force);

		}


		time = 40;
		birdTime = true;
	}
	else
	{
		time--;

	}

	if (birdTime)
	{
		p2Point<float> force(1, -25);
		body->acceleration = force;

	}

	return UPDATE_CONTINUE;
}
update_status Ent_Egg::PostUpdate(float dt)
{
	if (birdTime)
	{
		App->renderer->Blit(App->entity_handler->crow, body->rec.x, body->rec.y, NULL);
	}
	else
	{
		App->renderer->Blit(App->entity_handler->tex_egg, body->rec.x, body->rec.y, NULL);
	}
	return UPDATE_CONTINUE;
}




void Ent_Egg::OnCollision(PhysBody* body1, PhysBody* body2)
{
	if ((body2->type == BodyType::BODY_RECTANGLE) && body2 != App->player->body && body2 != App->player->body && body2->type != EGG)
	{
		if (body2->e_type == ENEMY_1)
		{
			App->entity_handler->DamageEntity(body2, damage);
		}

		//App->entity_handler->DamageEntity(body2, damage);
		App->entity_handler->DeleteEntity(body);

	}

}

void Ent_Egg::DoDamage(int damage)
{
	{
		if (health > 0) health -= damage;
		if (health < 0) {
			health = 0;
			App->entity_handler->DeleteEntity(body);
		}
	}
}