#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "Ent_Egg.h"
#include "Ent_Bomb.h"
#include "Ent_Enemy_1.h"

enum EntityType
{
		BOMB = 0,
		EGG,
		ENEMY_1,
		CANNON_BALL,
		CANNON
};


class EntityHandler : public Module
{
public:
	EntityHandler(Application* app, bool start_enabled = true);
	virtual ~EntityHandler();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody* CreateEntity(EntityType type, float x, float y , p2Point<float> startAcc, p2Point<float> startVel);
	void CollisionFromBody(PhysBody* myself, PhysBody* other);
	void DamageEntity(PhysBody* body, int damage);
	void DeleteEntity(PhysBody* body);
public:

	p2List<Ent_Egg*> eggs;
	p2List<Ent_Bomb*> bombs;
	p2List<Ent_Enemy_1*> enemy_1;

	SDL_Texture* tex_bomb;

	SDL_Texture* tex_egg;
	SDL_Rect rec_egg, rec_goldenEgg;

	SDL_Texture* tex_pengu;
	SDL_Texture* tex_cannon;
	SDL_Texture* tex_cannonBall;
	SDL_Rect rec_cannon[2];


};