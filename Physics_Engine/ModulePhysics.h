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
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	p2List<PhysBody*> bodies;
	//PhysBody ground;

private:
	
	bool debug;
	float gravity = 0.1f;
	
	p2Point<float>speedLimit;

	p2Point<float> totalMomentum;
	
};