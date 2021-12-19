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
	rec_egg = { 0,0,16,16 };
	rec_goldenEgg = { 16,0,16,16 };

	tex_pengu = App->textures->Load("Assets/images/pengu.png");
	tex_cannonBall = App->textures->Load("Assets/images/cannon_ball.png");
	tex_cannon = App->textures->Load("Assets/images/cannon.png");
	rec_cannon[0] = { 0,0,44,30 };
	rec_cannon[1] = { 0,0,44,30 };

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

	for (int i = 0; i < enemy_1.count(); i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		iteratorEnemy_1->CleanUp();
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

	for (int i = 0; i < enemy_1.count(); i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		iteratorEnemy_1->PreUpdate(dt);
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

	for (int i = 0; i < enemy_1.count(); i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		iteratorEnemy_1->Update(dt);
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

	for (int i = 0; i < enemy_1.count(); i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		iteratorEnemy_1->PostUpdate(dt);
	}

	return UPDATE_CONTINUE;
}

PhysBody* EntityHandler::CreateEntity(EntityType type, float x, float y, p2Point<float> startAcc, p2Point<float> startVel)
{
	

	switch (type)
	{
	case BOMB:
	{
		PhysBody* body = App->physics->CreateBody(BodyType::BODY_RECTANGLE, x, y, 14, 14, 30);
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->frictionCoeff = 0.9f;
		body->e_type = EntityType::BOMB;


		Ent_Bomb* newBomb = new Ent_Bomb(body->position, 10, body);
		newBomb->App = App;
		bombs.add(newBomb);

		newBomb->Start();
		return body;
	}
	break;

	case EGG:
	{
		PhysBody* body = App->physics->CreateBody(BODY_RECTANGLE, x, y, 15, 18, 20);
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->liftCoeff = 1.f;
		body->frictionCoeff = 0.5f;
		body->e_type = EntityType::EGG;

		Ent_Egg* newEgg = new Ent_Egg(body->position, 10, body);
		newEgg->App = App;
		eggs.add(newEgg);
		
		newEgg->Start();
		return body;
	}
	break;
	case ENEMY_1:
	{
		PhysBody* body = App->physics->CreateBody(BODY_RECTANGLE, x, y, 15, 18, 20);
		body->acceleration = startAcc;
		body->velocity = startVel;
		body->liftCoeff = 1.f;
		body->frictionCoeff = 0.9f;
		body->e_type = EntityType::ENEMY_1;

		Ent_Enemy_1* newEnemy_1 = new Ent_Enemy_1(body->position, 10, body);
		newEnemy_1->App = App;
		enemy_1.add(newEnemy_1);

		newEnemy_1->Start();
		return body;
	}
	default:
		break;
	}

}



void EntityHandler::CollisionFromBody(PhysBody* myself, PhysBody* other) 
{

	bool cont = true;

	for (int i = 0; i < eggs.count() && cont; i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		if (myself == iteratorEggs->body)
		{
			cont = false;
			iteratorEggs->OnCollision(myself, other);
		}
	}

	for (int i = 0; i < bombs.count() && cont; i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		if (myself == iteratorBombs->body)
		{
			cont = false;
			iteratorBombs->OnCollision(myself, other);
		}
	}

	for (int i = 0; i < enemy_1.count() && cont; i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		if (myself == iteratorEnemy_1->body)
		{
			cont = false;
			iteratorEnemy_1->OnCollision(myself, other);
		}
	}
}

void EntityHandler::DamageEntity(PhysBody* body, int damage)
{
	bool cont = true;

	for (int i = 0; i < eggs.count() && cont; i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		if (body == iteratorEggs->body)
		{
			cont = false;
			iteratorEggs->DoDamage(damage);
		}
	}

	for (int i = 0; i < bombs.count() && cont; i++)
	{

		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);

		if (body == iteratorBombs->body)
		{
			cont = false;
			iteratorBombs->DoDamage(damage);
		}
	}

	for (int i = 0; i < enemy_1.count() && cont; i++)
	{

		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);

		if (body == iteratorEnemy_1->body)
		{
			cont = false;
			iteratorEnemy_1->DoDamage(damage);
		}
	}
}

void EntityHandler::DeleteEntity(PhysBody* body)
{
	bool cont = true;

	p2List_item<Ent_Egg*>* delEggs = eggs.getFirst();

	for (int i = 0; i < eggs.count() && cont; i++)
	{

		Ent_Egg* iteratorEggs;
		eggs.at(i, iteratorEggs);

		if (body == iteratorEggs->body)
		{
			cont = false;
			iteratorEggs->body->pendingToDelete = true;
			delete iteratorEggs;
			eggs.del(delEggs);
		}
		delEggs = delEggs->next;
	}

	p2List_item<Ent_Bomb*>* delBombs = bombs.getFirst();
	for (int i = 0; i < bombs.count() && cont; i++)
	{
	
		Ent_Bomb* iteratorBombs;
		bombs.at(i, iteratorBombs);
	
		if (body == iteratorBombs->body)
		{
			cont = false;

			iteratorBombs->body->pendingToDelete = true;
			delete iteratorBombs;
			
			bombs.del(delBombs);
		}
		delBombs = delBombs->next;
	}
	
	p2List_item<Ent_Enemy_1*>* delEnemy_1 = enemy_1.getFirst();
	for (int i = 0; i < enemy_1.count() && cont; i++)
	{
	
		Ent_Enemy_1* iteratorEnemy_1;
		enemy_1.at(i, iteratorEnemy_1);
	
		if (body == iteratorEnemy_1->body)
		{
			cont = false;
			iteratorEnemy_1->body->pendingToDelete = true;
			delete iteratorEnemy_1;

			enemy_1.del(delEnemy_1);
		}
		delEnemy_1 = delEnemy_1->next;
	}
}