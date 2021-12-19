#include "Globals.h"
#include "Application.h"
#include "EntityHandler.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

EntityHandler::EntityHandler(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

EntityHandler::~EntityHandler()
{}

// Load assets
bool EntityHandler::Start()
{
	tex_bomb = App->textures->Load("Assets/images/bomb.png");
	tex_egg = App->textures->Load("Assets/images/egg.png");

	return UPDATE_CONTINUE;
}

// Unload assets
bool EntityHandler::CleanUp()
{
	LOG("Unloading player");

	for (int i = 0; i < eggs.count(); i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->CleanUp();
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->CleanUp();
	}

	return true;
}

// Update: draw background
update_status EntityHandler::PreUpdate(float dt)
{
	for (int i = 0; i < eggs.count(); i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->PreUpdate(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->PreUpdate(dt);
	}
	
	return UPDATE_CONTINUE;
}
update_status EntityHandler::Update(float dt)
{

	for (int i = 0; i < eggs.count(); i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->Update(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->Update(dt);
	}
	return UPDATE_CONTINUE;
}
update_status EntityHandler::PostUpdate(float dt)
{
	for (int i = 0; i < eggs.count(); i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->PostUpdate(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->PostUpdate(dt);
	}
	return UPDATE_CONTINUE;
}

void EntityHandler::CreateProjectile(EntityType type, float x, float y, p2Point<float> startAcc, p2Point<float> startVel)
{

	switch (type)
	{
	case BOMB:
	{
		PhysBody* body = App->physics->CreateBody(BodyType::BODY_RECTANGLE, x, y, 14, 14, 30);
		body->acceleration = startAcc;
		body->velocity = startVel;
		


		Ent_Bomb* newBomb = new Ent_Bomb(body->position, 10, body);
		newBomb->App = App;
		bombs.add(newBomb);

		newBomb->Start();
	}
	break;

	case EGG:
	{
		PhysBody* body = App->physics->CreateBody(BODY_RECTANGLE, x, y, 15, 18, 20);
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->liftCoeff = 1.f;

		Ent_Egg* newEgg = new Ent_Egg(body->position, 10, body);
		newEgg->App = App;
		eggs.add(newEgg);
		
		newEgg->Start();
	}
	break;
	default:
		break;
	}

}



void EntityHandler::CollisionFromBody(PhysBody* myself, PhysBody* other) 
{

	bool cont = false;

	for (int i = 0; i < eggs.count() && cont; i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		if (myself == iteratorEggs->body)
		{
			cont = true;
			iteratorEggs->OnCollision(myself, other);
		}
	}

	for (int i = 0; i < bombs.count() && cont; i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->OnCollision(myself, other);
	}
}

void EntityHandler::DamageEntity(PhysBody* body, int damage)
{

}

