#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"



ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	speedLimit.x = 1000.0f;
	speedLimit.y = 2000.0f;
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate(float dt)
{
	for (p2List_item<PhysBody*>* item = bodies.getFirst(); item; item = item->next)
	{
		//---Gravity---
		if (item->data->type != BODY_GROUND)
		{
			if ((item->data->position.y + item->data->rec.h / 2) < App->scene_intro->ground->rec.y)
			{
				item->data->acceleration.y = gravity * item->data->mass;
				
				
			}
			else
			{
				if (item->data->velocity.y > 0.0f)
				{
					item->data->acceleration.y = 0.0f;
					item->data->velocity.y = 0.0f;
				}
				
				item->data->position.y = App->scene_intro->ground->rec.y - item->data->rec.h / 2;
				

			}
			item->data->ComputeFriction();
			item->data->LimitSpeed(speedLimit.x, speedLimit.y);
			item->data->ComputeKinematics(dt);
		}

		//---Collisions---
		
		
		switch (item->data->type)
		{
			case BODY_RECTANGLE:
			{
				for (p2List_item<PhysBody*>* pb = bodies.getFirst(); pb; pb = pb->next)
				{
					switch (pb->data->type)
					{
						case BODY_RECTANGLE:
						{
							//Solve attaching problems
							if ((item->data->position.x < pb->data->position.x) && (item->data->position.x + item->data->rec.w / 2> pb->data->position.x - pb->data->rec.w /2))
							{
								if ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h) &&
									item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h)
								{
									item->data->position.x--;
									pb->data->position.x++;
								}
								
								if ((item->data->position.y < pb->data->position.y) && (item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2))
								{
									item->data->position.y--;
									pb->data->position.y++;
								}
								if ((item->data->position.y > pb->data->position.y) && (item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2))
								{
									item->data->position.y++;
									pb->data->position.y--;
								}
							}
							if ((item->data->position.x > pb->data->position.x) && (item->data->position.x - item->data->rec.w /2< pb->data->position.x + pb->data->rec.w/2))
							{
								if ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h) &&
									item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h)
								{
									item->data->position.x++;
									pb->data->position.x--;
								}
								
								if ((item->data->position.y < pb->data->position.y) && (item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2))
								{
									item->data->position.y--;
									pb->data->position.y++;
								}
								if ((item->data->position.y > pb->data->position.y) && (item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2))
								{
									item->data->position.y++;
									pb->data->position.y--;
								}
							}

							
							// X Axis---
							//Bodies in the same Y position
							if ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
								(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2))
							{
								//item at the left
								if ((item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2) &&
									(item->data->position.x - item->data->rec.w / 2 < pb->data->position.x - pb->data->rec.w / 2))

								{
									totalMomentum.x = item->data->velocity.x * item->data->mass + pb->data->velocity.x * pb->data->mass;
									item->data->velocity.x = (-totalMomentum.x / item->data->mass) * item->data->restitutionCoeff;
									item->data->ComputeKinematics(dt);
									pb->data->velocity.x = (totalMomentum.x / pb->data->mass) * pb->data->restitutionCoeff;
									pb->data->ComputeKinematics(dt);

								}
								//item at the right
								if ((item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
									(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x + pb->data->rec.w / 2))
								{
									totalMomentum.x = item->data->velocity.x + pb->data->velocity.x;
									item->data->velocity.x = (totalMomentum.x / item->data->mass) * item->data->restitutionCoeff;
									item->data->ComputeKinematics(dt);
									pb->data->velocity.x = (-totalMomentum.x / pb->data->mass) * pb->data->restitutionCoeff;
									pb->data->ComputeKinematics(dt);
								}

								// Y Axis---
								//Bodies in the same X position
								if ((item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
									(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2))
								{
									//item at the top
									if ((item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2) &&
										(item->data->position.y - item->data->rec.h / 2 < pb->data->position.y - pb->data->rec.h / 2))

									{
										totalMomentum.y = item->data->velocity.y * item->data->mass + pb->data->velocity.y * pb->data->mass;
										item->data->velocity.y = (-totalMomentum.y / item->data->mass) * item->data->restitutionCoeff;
										item->data->ComputeKinematics(dt);
										pb->data->velocity.y = (totalMomentum.y / pb->data->mass) * pb->data->restitutionCoeff;
										pb->data->ComputeKinematics(dt);

									}
									//item at the bottom
									if ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
										(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y + pb->data->rec.h / 2))
									{
										totalMomentum.y = item->data->velocity.y + pb->data->velocity.y;
										item->data->velocity.y = (totalMomentum.y / item->data->mass) * item->data->restitutionCoeff;
										item->data->ComputeKinematics(dt);
										pb->data->velocity.y = (-totalMomentum.y / pb->data->mass) * pb->data->restitutionCoeff;
										pb->data->ComputeKinematics(dt);
									}
								}
								break;
							}
							
						}
						default:
							break;
					}
				}
				break;
			}
			default:
				break;
		}
		
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate(float dt)
{
	

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	bodies.clear();

	return true;
}
