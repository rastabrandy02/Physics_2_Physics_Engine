#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"


class Ent_Egg : public Module
{
public:
	Ent_Egg(p2Point<float> startPosition, int damage, PhysBody* b);
	virtual ~Ent_Egg();

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

	PhysBody* body;


};