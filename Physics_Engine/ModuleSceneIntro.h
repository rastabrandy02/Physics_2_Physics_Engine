#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"


class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:

	bool freeCam = false;

	SDL_Texture* background;

	PhysBody* ground;
	PhysBody* test01;
	PhysBody* test02;
	//SDL_Rect ground;
	SDL_Rect plant;

	p2Point <int> plantPos;
};
