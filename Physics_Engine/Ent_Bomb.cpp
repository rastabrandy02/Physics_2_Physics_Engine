#include "Globals.h"
#include "Application.h"
#include "Ent_Bomb.h"
#include "ModulePlayer.h"
#include "PhysBody.h"
#include "ModulePhysics.h"

Ent_Bomb::Ent_Bomb(p2Point<float> startPosition, int damage, PhysBody* b) : Module()
{
	

	this->body = b;
	body->position = startPosition;
	this->damage = damage;


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
	App->renderer->Blit(App->entity_handler->tex_bomb, body->rec.x, body->rec.y, NULL);
	//SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 90);
	//SDL_RenderFillRect(App->renderer->renderer, &body->rec);
	return UPDATE_CONTINUE;
}

void Ent_Bomb::OnCollision(PhysBody* body1, PhysBody* body2)
{

	if ((body2->type == BodyType::BODY_RECTANGLE) && body2 != App->player->body && body2->type != BOMB)
	{

		//App->entity_handler->DamageEntity(body2, damage);
		App->entity_handler->DeleteEntity(body);
		
	}

}

