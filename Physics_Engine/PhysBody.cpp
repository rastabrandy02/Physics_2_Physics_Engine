
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