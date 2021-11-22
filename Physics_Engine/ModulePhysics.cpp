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

	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	for (p2List_item<PhysBody*>* item = bodies.getFirst(); item; item = item->next)
	{
		//Gravity
		if (item->data->type != BODY_GROUND)
		{
			if ((item->data->position.y + item->data->rec.h / 2) < App->scene_intro->ground->rec.y)
			{
				item->data->acceleration.y = 1.0f;
				
				
			}
			else
			{
				item->data->acceleration.SetToZero();
				item->data->velocity.SetToZero();
				item->data->position.y = App->scene_intro->ground->rec.y - item->data->rec.h / 2;
			}
			item->data->ComputeKinematics();
		}
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	/*
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}*/

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	bodies.clear();

	return true;
}
