#pragma once
#include "Application.h"
#include "Globals.h"
#include "Module.h"
#include "EntityHandler.h"

enum BodyType
{
	BODY_GROUND = 0,
	BODY_RECTANGLE,
	BODY_CIRCLE

};
class PhysBody
{
public:
	PhysBody();
	
	PhysBody(BodyType type);
	
	~PhysBody();

	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);

	void ComputeKinematics(float dt);
	void ComputeFriction(float frictionCoeff);

	void AdjustSprite();
	void LimitSpeed(float limitX, float limitY);
	void ApplyImpulse(p2Point<float> force)
	{
		if (this)
		{
			acceleration.x = force.x;
			acceleration.y = force.y;
		}
		
	}


	

	int mass;
	float restitutionCoeff;
	float liftCoeff;
	float frictionCoeff;

	BodyType type;
	EntityType e_type;
	SDL_Rect rec;
	p2Point<float> position;
	p2Point<float> velocity;
	p2Point<float> acceleration;

	bool pendingToDelete = false;
	bool isStatic = false;
	bool onGround = false;


};