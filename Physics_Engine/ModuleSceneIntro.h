#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"


class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:

	PhysBody* ground;
	PhysBody* test;
	//SDL_Rect ground;
	SDL_Rect plant;

	p2Point <int> plantPos;
};
