#include <math.h>
#include "PhysBody.h"

PhysBody::PhysBody()
{
	position.SetToZero();
	velocity.SetToZero();
	acceleration.SetToZero();
	rec = { 0 };
	mass = 0;
}
PhysBody::PhysBody(BodyType type)
{
	this->type = type;

	position.SetToZero();
	velocity.SetToZero();
	acceleration.SetToZero();
	rec = { 0 };
	mass = 0;
}
PhysBody::~PhysBody()
{
}

void PhysBody::ComputeKinematics()
{
	velocity = velocity + acceleration;
	position = position + velocity;
	AdjustSprite();
}
void PhysBody::AdjustSprite()
{
	rec.x = position.x - rec.w / 2;
	rec.y = position.y - rec.h / 2;
}
void PhysBody::ComputeFriction()
{
	
	if (velocity.x != 0.0f)
	{
		if (velocity.x > 0.0f)
		{
			acceleration.x = -mass * frictionCoeff;
		}
		if (velocity.x < 0.0f)
		{
			acceleration.x = mass * frictionCoeff;
		}
	}
	float minV = 0.9f;
	if (velocity.x <= minV && velocity.x >= -minV)
	{
		velocity.x = 0.0f;
		acceleration.x = 0.0f;
	}
	LOG("velocity x: %f", velocity.x);
	LOG("acceleration x; %f", acceleration.x);
}
void PhysBody::LimitSpeed(float limitX, float limitY)
{
	if (velocity.x > limitX) velocity.x = limitX;
	if (velocity.x < -limitX) velocity.x = -limitX;
	if (velocity.y > limitY) velocity.y = limitY;
	if (velocity.y < -limitY)velocity.y = -limitY;
}