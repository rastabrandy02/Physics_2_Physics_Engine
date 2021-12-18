#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "Proj_Egg.h"
#include "Proj_Bomb.h"

enum ProjectileType
{
		BOMB = 0,
		EGG
};


class ProjectileHandler : public Module
{
public:
	ProjectileHandler(Application* app, bool start_enabled = true);
	virtual ~ProjectileHandler();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void CreateProjectile(ProjectileType type, float x, float y , p2Point<float> startAcc, p2Point<float> startVel);

public:

	p2List<Proj_Egg*> eggs;
	p2List<Proj_Bomb*> bombs;

	SDL_Texture* tex_bomb;
	SDL_Texture* tex_egg;

};