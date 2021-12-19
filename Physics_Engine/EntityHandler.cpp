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
	tex_bomb = App->textures->Load("Assets/bomb.png");
	tex_egg = App->textures->Load("Assets/egg.png");

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

void EntityHandler::CreateProjectile(ProjectileType type, float x, float y, p2Point<float> startAcc, p2Point<float> startVel)
{

	switch (type)
	{
	case BOMB:
	{
		PhysBody* body = new PhysBody();
		p2Point<float> pos;
		pos.x = x;
		pos.y = y;
		Ent_Bomb* newBomb = new Ent_Bomb(pos, 10, body);
		newBomb->App = App;
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->rec.w = 14;
		body->rec.h = 14;
		bombs.add(newBomb);
		App->physics->bodies.add(body);
		newBomb->Start();
	}
	break;
	case EGG:
	{
		PhysBody* body = new PhysBody();
		p2Point<float> pos;
		pos.x = x;
		pos.y = y;
		Ent_Egg* newEgg = new Ent_Egg(pos, 10, body);
		newEgg->App = App;
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->rec.w = 15;
		body->rec.h = 18;

		eggs.add(newEgg);
		App->physics->bodies.add(body);
		newEgg->Start();
	}
	break;
	default:
		break;
	}

}

