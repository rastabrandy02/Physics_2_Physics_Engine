#pragma once
#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "EntityHandler.h"

class Ent_Enemy_1 : public Module
{
public:
	Ent_Enemy_1(p2Point<float> startPosition, int damage, PhysBody* b);
	virtual ~Ent_Enemy_1();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody* GetPhysbody() const
	{
		return body;
	}

	void OnCollision(PhysBody* body1, PhysBody* body2) override;

	void DoDamage(int damage);

public:

	PhysBody* body;
	int health;
	int damage;

};