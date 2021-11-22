#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	 ground = new PhysBody(BODY_GROUND);
	 
	 ground->rec = { 0, SCREEN_HEIGHT - 100, SCREEN_WIDTH, 150 };
	 App->physics->bodies.add(ground);

	 test = new PhysBody(BODY_RECTANGLE);
	 test->position.x = 50;
	 test->position.y = 50;
	 test->rec = { (int)test->position.x,(int) test->position.y, 20,20 };
	 App->physics->bodies.add(test);
	/* plantPos.x = 200;
	 plantPos.y = SCREEN_HEIGHT - 175;
	 plant = { plantPos.x, plantPos.y, 10, 75 };*/
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::PreUpdate()
{
	/*if (App->player->position.DistanceTo(plantPos) < 70)
	{
		plant.y = SCREEN_HEIGHT - 185;
	}
	if (App->player->position.DistanceTo(plantPos) < 100 && App->player->position.DistanceTo(plantPos) > 70)
	{
		plant.y = SCREEN_HEIGHT - 180;
	}
	if (App->player->position.DistanceTo(plantPos) >= 100)
	{
		plant.y = SCREEN_HEIGHT - 175;
	}*/
	/*plant.x = plantPos.x;
	plant.y = plantPos.y;*/
	
	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::Update()
{
	
	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate()
{
	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(App->renderer->renderer, &ground->rec);
	SDL_SetRenderDrawColor(App->renderer->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(App->renderer->renderer, &test->rec);
	return UPDATE_CONTINUE;
}
