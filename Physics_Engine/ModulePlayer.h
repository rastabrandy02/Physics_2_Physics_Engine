#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "EntityHandler.h"


#define PI 3.14159265359

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody* GetPhysbody() const
	{
		return body;
	}

	

public:

	SDL_Texture* tex_player;
	PhysBody* body = nullptr;
	int speed = 8;
	int jumpForce = 40000;

	float maxVelocity = 200;

	p2Point<float> startPos; 

	SDL_Texture* Arrow;
	float angle;

	int weaponNumber = 0;

	SDL_Texture* UI;


	int shootTimer = 90;
	int shootTime = 0;

	float gameTime = 60 * 60 * 2;
	float pos0 = 0;
	float bar_v = SCREEN_WIDTH / gameTime;

	SDL_Texture* win;
	SDL_Texture* lose;



};