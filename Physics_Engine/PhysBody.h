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
	

	void ComputeKinematics();
	void AdjustSprite();
	
	int mass;
	BodyType type;
	SDL_Rect rec;
	p2Point<float> position;
	p2Point<float> velocity;
	p2Point<float> acceleration;


};