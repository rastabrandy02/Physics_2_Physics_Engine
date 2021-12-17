#pragma once
#include "Application.h"
#include "Globals.h"
#include "Module.h"

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
	

	void ComputeKinematics(float dt);
	void ComputeFriction();

	void AdjustSprite();
	void LimitSpeed(float limitX, float limitY);
	
	int mass;
	float restitutionCoeff;
	float frictionCoeff;

	BodyType type;
	SDL_Rect rec;
	p2Point<float> position;
	p2Point<float> velocity;
	p2Point<float> acceleration;


};