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
	speedLimit.y = 40000.0f;
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate(float dt)
{
	for (p2List_item<PhysBody*>* item = bodies.getFirst(); item; item = item->next)
	{
		int collisionsAttempts = 0;
		bool hasTouchedFloor = false;
		bool onGround = false;

		if (!item->data->isStatic)
			item->data->ComputeKinematics(dt);
			
			item->data->LimitSpeed(speedLimit.x, speedLimit.y);
			
			if (!item->data->isStatic)
				item->data->acceleration.y = gravity * item->data->mass;

		//---Gravity---
		//if (item->data != App->scene_intro->ground)
		//{
		//	//LOG("v %f", App->player->body->position.x);
		//	//LOG("acc %f", App->player->body->acceleration.x);
		//
		//	if (!item->data->isStatic)
		//		item->data->ComputeKinematics(dt);
		//
		//	item->data->LimitSpeed(speedLimit.x, speedLimit.y);
		//
		//	if (!item->data->isStatic)
		//		item->data->acceleration.y = gravity * item->data->mass;
		//	if (App->scene_intro->ground->rec.y - item->data->position.y - item->data->rec.h / 2 <= 2)
		//	{
		//		hasTouchedFloor = true;
		//		onGround = true;
		//	}
		//
		//	if (onGround)
		//		item->data->ComputeFriction(groundFriction);
		//	else
		//		item->data->ComputeFriction(airFriction);
		//
		//	//LOG("dist %f", App->scene_intro->ground->rec.y - item->data->position.y - item->data->rec.h/2);
		//	//LOG("dist %i", item->data->rec.h);
		//
		//	if ((item->data->position.y + item->data->rec.h / 2) > App->scene_intro->ground->rec.y)
		//	{
		//
		//		if (hasTouchedFloor)
		//		{
		//
		//			while ((item->data->position.y + item->data->rec.h / 2) > App->scene_intro->ground->rec.y)
		//			{
		//				item->data->position.y--;
		//			}
		//			while ((item->data->position.y + item->data->rec.h / 2) < App->scene_intro->ground->rec.y)
		//			{
		//				item->data->position.y++;
		//			}
		//
		//		}
		//
		//		item->data->acceleration.y =0 ;
		//		item->data->velocity.y = 0.0f;
		//	}
		//	else
		//	{
		//		if (!item->data->isStatic)
		//			item->data->acceleration.y = gravity * item->data->mass;
		//	}
		//}




		//---Collisions---
		
		bool onTop = false;
		switch (item->data->type)
		{

			case BODY_RECTANGLE:
			{
				for (p2List_item<PhysBody*>* pb = bodies.getFirst(); pb != item; pb = pb->next)
				{
					switch (pb->data->type)
					{
						
						break;

						case BODY_RECTANGLE:
						{

							float distY = fabs(item->data->position.y - pb->data->position.y);
							float distX = fabs(item->data->position.x - pb->data->position.x);

							int marginW = 5;
							int marginH = -10;
							
							
							while (distY < item->data->rec.h / 2 + pb->data->rec.h / 2 &&
								distX < item->data->rec.w /2 + pb->data->rec.w / 2 && 
								!item->data->isStatic && collisionsAttempts < maxCollisionAttempts)
							{
								LOG("%i", (item->data->position.y < pb->data->position.y));

 								while ((item->data->position.y < pb->data->position.y) &&
									distX < item->data->rec.w /2 + pb->data->rec.w / 2 - marginW)
								{
									double item_temp;
									float item_remnant = modf(item->data->position.y, &item_temp);
								
									double pb_temp;
									float pb_remnant = modf(item->data->position.y, &pb_temp);
 									if (!item->data->isStatic)
										item->data->position.y -= (item_remnant + 1);
									if (!pb->data->isStatic)
										pb->data->position.y += (pb_remnant + 1);
								
									distY = (fabs(pb->data->position.y - item->data->position.y));
									float temp = item->data->rec.h / 2 + pb->data->rec.h / 2;
									onTop = true;

									if (!(distY < temp))
										break;
								}
								
								while (item->data->position.y > pb->data->position.y &&
									distX < item->data->rec.w / 2 + pb->data->rec.w / 2 - marginW)
								{
									double item_temp;
									float item_remnant = modf(item->data->position.y, &item_temp);
								
									double pb_temp;
									float pb_remnant = modf(item->data->position.y, &pb_temp);
									if (!item->data->isStatic)
										item->data->position.y += (item_remnant + 1);
									if (!pb->data->isStatic)
										pb->data->position.y -= (pb_remnant + 1);
								
									distY = fabs(item->data->position.y - pb->data->position.y);
									float temp = item->data->rec.h / 2 + pb->data->rec.h / 2;
									onTop = true;

									if (!(distY < temp))
										break;
								}
								
								LOG("on top: %i", onTop);
								while (item->data->position.x < pb->data->position.x && !onTop)
								{
									double item_temp;
									float item_remnant = modf(item->data->position.x, &item_temp);
								
									double pb_temp;
									float pb_remnant = modf(item->data->position.x, &pb_temp);
									if (!item->data->isStatic)
										item->data->position.x -= (item_remnant + 1);
									if (!pb->data->isStatic)
										pb->data->position.x += (pb_remnant + 1);
									distX = fabs(item->data->position.x - pb->data->position.x);
									float temp = item->data->rec.w / 2 + pb->data->rec.w / 2;
									if (!(distX < temp))
										break;
								}
								
								
								while (item->data->position.x > pb->data->position.x && !onTop)
								{
									double item_temp;
									float item_remnant = modf(item->data->position.x, &item_temp);
								
									double pb_temp;
									float pb_remnant = modf(item->data->position.x, &pb_temp);
									if (!item->data->isStatic)
										item->data->position.x += (item_remnant + 1);
									if (!pb->data->isStatic)
										pb->data->position.x -= (pb_remnant + 1);
									distX = fabs(item->data->position.x - pb->data->position.x);
									float temp = item->data->rec.w / 2 + pb->data->rec.w / 2;
									if (!(distX < temp))
										break;
								}

								
								if (onTop)
								{
									item->data->acceleration.y = -item->data->acceleration.y;
									//item->data->position.y = pb->data->position.y - pb->data->rec.h - item->data->rec.h / 2;
									pb->data->acceleration.y = -pb->data->acceleration.y;
									
								}
								
								collisionsAttempts++;
							}

							if (onTop)
								item->data->ComputeFriction(groundFriction);
							else
								item->data->ComputeFriction(airFriction);


							
							//if (((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
							//	(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2) &&
							//	(item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
							//	(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2)
							//	&& item->data->isStatic == false))
							//{
							//
							//	//Solve attaching problems
							//	while ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
							//		(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2)
							//		)
							//	{
							//
							//		if ((item->data->position.y < pb->data->position.y))
							//		{
							//			double item_temp;
							//			float item_remnant = modf(item->data->position.y, &item_temp);
							//
							//			double pb_temp;
							//			float pb_remnant = modf(item->data->position.y, &pb_temp);
							//			if (!item->data->isStatic)
							//				item->data->position.y -= (item_remnant - 1);
							//			if (!pb->data->isStatic)
							//				pb->data->position.y += (pb_remnant + 1);
							//		}
							//		if (item->data->position.y > pb->data->position.y)
							//		{
							//			double item_temp;
							//			float item_remnant = modf(item->data->position.y, &item_temp);
							//
							//			double pb_temp;
							//			float pb_remnant = modf(item->data->position.y, &pb_temp);
							//			if (!item->data->isStatic)
							//				item->data->position.y += (item_remnant + 1);
							//			if (!pb->data->isStatic)
							//				pb->data->position.y -= (pb_remnant - 1);
							//		}
							//	}
							//
							//	while ((item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
							//		(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2)
							//		)
							//	{
							//		if (item->data->position.x < pb->data->position.x)
							//		{
							//			double item_temp;
							//			float item_remnant = modf(item->data->position.x, &item_temp);
							//
							//			double pb_temp;
							//			float pb_remnant = modf(item->data->position.x, &pb_temp);
							//			if (!item->data->isStatic)
							//				item->data->position.x -= (item_remnant - 1);
							//			if (!pb->data->isStatic)
							//				pb->data->position.x += (pb_remnant + 1);
							//		}
							//
							//		LOG("hello");
							//		if (item->data->position.x > pb->data->position.x)
							//		{
							//			double item_temp;
							//			float item_remnant = modf(item->data->position.x, &item_temp);
							//
							//			double pb_temp;
							//			float pb_remnant = modf(item->data->position.x, &pb_temp);
							//			if (!item->data->isStatic)
							//				item->data->position.x += (item_remnant + 1);
							//			if (!pb->data->isStatic)
							//				pb->data->position.x -= (pb_remnant - 1);
							//		}
							//	}
							//
							//}
							
							
							// X Axis---
							//Bodies in the same Y position
							// Y Axis---
							//Bodies in the same X position
							if ((item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
								(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2) &&
								(item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
								(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2))
							{
								
							
								//item at the left
								if ((item->data->position.x + item->data->rec.w / 2 > pb->data->position.x - pb->data->rec.w / 2) &&
									(item->data->position.x - item->data->rec.w / 2 < pb->data->position.x - pb->data->rec.w / 2))
							
								{
									totalMomentum.x = item->data->velocity.x * item->data->mass + pb->data->velocity.x * pb->data->mass;
									if (!item->data->isStatic)
									{
										item->data->velocity.x = (-totalMomentum.x / item->data->mass) * item->data->restitutionCoeff;
										
									}
									//item->data->ComputeKinematics(dt);
									if (!pb->data->isStatic)
									{
										pb->data->velocity.x = (totalMomentum.x / pb->data->mass) * pb->data->restitutionCoeff;
										
									}//pb->data->ComputeKinematics(dt);
							
								}
								//item at the right
								if ((item->data->position.x - item->data->rec.w / 2 < pb->data->position.x + pb->data->rec.w / 2) &&
									(item->data->position.x + item->data->rec.w / 2 > pb->data->position.x + pb->data->rec.w / 2))
								{
									totalMomentum.x = item->data->velocity.x + pb->data->velocity.x;
									if (!item->data->isStatic)
									{
										item->data->velocity.x = (totalMomentum.x / item->data->mass) * item->data->restitutionCoeff;
										item->data->acceleration.x = -item->data->acceleration.x;
									}
									if (!pb->data->isStatic)
									{
										pb->data->velocity.x = (-totalMomentum.x / pb->data->mass) * pb->data->restitutionCoeff;
										
									}
									//pb->data->ComputeKinematics(dt);
								}
							
								//item at the top
								if ((item->data->position.y + item->data->rec.h / 2 > pb->data->position.y - pb->data->rec.h / 2) &&
									(item->data->position.y - item->data->rec.h / 2 < pb->data->position.y - pb->data->rec.h / 2))
							
								{
									totalMomentum.y = item->data->velocity.y * item->data->mass + pb->data->velocity.y * pb->data->mass;
									if (!item->data->isStatic)
									{
 										item->data->velocity.y = (-totalMomentum.y / item->data->mass) * item->data->restitutionCoeff * 2;
										
									}
									//item->data->ComputeKinematics(dt);
									if (!pb->data->isStatic)
									{
										pb->data->velocity.y = (totalMomentum.y / pb->data->mass) * pb->data->restitutionCoeff * 2;
										
									}
									//pb->data->ComputeKinematics(dt);
							
								}
								//item at the bottom
								if ((item->data->position.y - item->data->rec.h / 2 < pb->data->position.y + pb->data->rec.h / 2) &&
									(item->data->position.y + item->data->rec.h / 2 > pb->data->position.y + pb->data->rec.h / 2))
								{
									totalMomentum.y = item->data->velocity.y + pb->data->velocity.y;
									if (!item->data->isStatic)
									{
										item->data->velocity.y = (totalMomentum.y / item->data->mass) * item->data->restitutionCoeff * 2;
										item->data->acceleration.y = 0;
									}
									//item->data->ComputeKinematics(dt);
									if (!pb->data->isStatic)
									{
										pb->data->velocity.y = (-totalMomentum.y / pb->data->mass) * pb->data->restitutionCoeff * 2;
										pb->data->acceleration.y = 0;
									}
									//pb->data->ComputeKinematics(dt);
								}
							
								
							
							}
							break;
							
							
						}
						default:
							break;
					}

					onTop = false;
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
		for (p2List_item<PhysBody*>* item = bodies.getFirst(); item; item = item->next)
		{
			SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 255, 100);

			SDL_Rect tempRect = item->data->rec;

			tempRect.x += App->renderer->camera.x;
			tempRect.y += App->renderer->camera.y;

			SDL_RenderFillRect(App->renderer->renderer, &tempRect);
			SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 100);
			SDL_RenderDrawPoint(App->renderer->renderer,item->data->position.x + App->renderer->camera.x, item->data->position.y + App->renderer->camera.y);
		}
		
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

PhysBody* ModulePhysics::CreateBody(BodyType type, int x, int y, int w, int h, int mass)
{
	PhysBody* b = new PhysBody(type);
	b->position.x = x + w/2;
	b->position.y = y + h/2;
	b->velocity.x = 0;
	b->velocity.y = 0;
	b->rec = { (int)b->position.x - w/2,(int)b->position.y - h/2, w, h }; 
	b->mass = mass;
	b->restitutionCoeff = 0;
	b->liftCoeff = 0;
	bodies.add(b);

	return b;
}