#pragma once
#include "Application.h"
#include "Module.h"
#include "Globals.h"
#include "PhysBody.h"

class PhysBody;
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	p2List<PhysBody*> bodies;
	//PhysBody ground;

	

private:
	
	bool debug;
	float gravity = 20.0f;
	
	p2Point<float>speedLimit;

	p2Point<float> totalMomentum;

	float groundFriction = 0.9f;
	float airFriction = 0.4f;
	
};