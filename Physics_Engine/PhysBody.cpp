#include <math.h>
#include "PhysBody.h"
#include "Application.h"
#include "ModuleRender.h"


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

void PhysBody::ComputeKinematics(float dt)
{
	/*velocity.x = velocity.x + acceleration.x * dt;
	velocity.y = velocity.y + acceleration.y * dt;
	position.x = position.x + velocity.x * dt;
	position.y = position.y + velocity.y * dt;*/

	if (isStatic == false)
	{
		if (velocity.y > 0)
		{
			float counterforce = -liftCoeff * fabs(velocity.x);

			//LOG("lift force %f", counterforce);
			//LOG("acc %f", acceleration.y);
			acceleration.y += counterforce;

			float mult = 0.1;
			if (velocity.x > 0) velocity.x -= mult * counterforce;
			if (velocity.x < 0) velocity.x += mult * counterforce;
		}


		position.x = position.x + velocity.x * dt + (acceleration.x / 2) * pow(dt, 2);
		position.y = position.y + velocity.y * dt + (acceleration.y / 2) * pow(dt, 2);

		velocity.x = velocity.x + acceleration.x * dt;
		velocity.y = velocity.y + acceleration.y * dt;

	}
	else
	{
		velocity.SetToZero();
		acceleration.SetToZero();
	
	
	}


	



	//lift

	



	AdjustSprite();
}
void PhysBody::AdjustSprite()
{
	rec.x = position.x - rec.w / 2;
	rec.y = position.y - rec.h / 2;
}
void PhysBody::ComputeFriction(float frictionCoeff)
{
	///LOG("friction active");
	
	if (velocity.x > 0.0f)
	{
		acceleration.x = -mass * frictionCoeff * 3;
	}
	if (velocity.x < 0.0f)
	{
		acceleration.x = mass * frictionCoeff * 3;
	}
	
	float minV = 2.f;
	if (velocity.x <= minV && velocity.x >= -minV)
	{
		velocity.x = 0.0f;
		acceleration.x = 0.0f;
	}
	

}
void PhysBody::LimitSpeed(float limitX, float limitY)
{
	if (velocity.x > limitX) velocity.x = limitX;
	if (velocity.x < -limitX) velocity.x = -limitX;
	if (velocity.y > limitY) velocity.y = limitY;
	if (velocity.y < -limitY)velocity.y = -limitY;
}

update_status PhysBody::PreUpdate(float dt)
{
	ComputeKinematics(dt);

	return UPDATE_CONTINUE;
}

update_status PhysBody::PostUpdate(float dt)
{

	

	return UPDATE_CONTINUE;
}