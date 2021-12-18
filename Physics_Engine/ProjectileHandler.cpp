#include "Globals.h"
#include "Application.h"
#include "ProjectileHandler.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ProjectileHandler::ProjectileHandler(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ProjectileHandler::~ProjectileHandler()
{}

// Load assets
bool ProjectileHandler::Start()
{
	tex_bomb = App->textures->Load("Assets/bomb.png");
	tex_egg = App->textures->Load("Assets/egg.png");

	return UPDATE_CONTINUE;
}

// Unload assets
bool ProjectileHandler::CleanUp()
{
	LOG("Unloading player");

	for (int i = 0; i < eggs.count(); i++)
	{

		Proj_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->CleanUp();
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Proj_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->CleanUp();
	}

	return true;
}

// Update: draw background
update_status ProjectileHandler::PreUpdate(float dt)
{
	for (int i = 0; i < eggs.count(); i++)
	{

		Proj_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->PreUpdate(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Proj_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->PreUpdate(dt);
	}
	
	return UPDATE_CONTINUE;
}
update_status ProjectileHandler::Update(float dt)
{
	LOG("handling projectiles");

	for (int i = 0; i < eggs.count(); i++)
	{

		Proj_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->Update(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Proj_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->Update(dt);
	}
	return UPDATE_CONTINUE;
}
update_status ProjectileHandler::PostUpdate(float dt)
{
	for (int i = 0; i < eggs.count(); i++)
	{

		Proj_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		iteratorEggs->PostUpdate(dt);
	}

	for (int i = 0; i < bombs.count(); i++)
	{

		Proj_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		iteratorBombs->PostUpdate(dt);
	}
	return UPDATE_CONTINUE;
}

void ProjectileHandler::CreateProjectile(ProjectileType type, float x, float y, p2Point<float> startAcc, p2Point<float> startVel)
{

	switch (type)
	{
	case BOMB:
	{
		PhysBody* body = new PhysBody();
		p2Point<float> pos;
		pos.x = x;
		pos.y = y;
		Proj_Bomb* newBomb = new Proj_Bomb(pos, 10, body);
		newBomb->App = App;
		body->acceleration = startAcc;
		body->velocity = startVel;
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
		Proj_Egg* newEgg = new Proj_Egg(pos, 10, body);
		newEgg->App = App;
		body->acceleration = startAcc;
		body->velocity = startVel;
		eggs.add(newEgg);
		App->physics->bodies.add(body);
		newEgg->Start();
	}
	break;
	default:
		break;
	}

}

