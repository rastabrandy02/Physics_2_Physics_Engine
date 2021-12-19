#pragma once
#include "ModuleRender.h"
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePhysics.h"
#include "EntityHandler.h"

class Ent_Bomb : public Module
{
public:
	Ent_Bomb(p2Point<float> startPosition, int damage, PhysBody* b);
	virtual ~Ent_Bomb();

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

	void DoDamage(int damage)
	{
		if (health > 0) health -= damage;
		if (health < 0) health = 0;
	}

public:

	PhysBody* body;
	int health;
	int damage;



};