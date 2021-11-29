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

	 test01 = new PhysBody(BODY_RECTANGLE);
	 test01->position.x = 120;
	 test01->position.y = 50;
	 test01->rec = { (int)test01->position.x,(int) test01->position.y, 20,20 };
	 test01->mass = 3;
	 test01->restitutionCoeff = 0.7f;
	 test01->frictionCoeff = .09f;
	 App->physics->bodies.add(test01);

	 test02 = new PhysBody(BODY_RECTANGLE);
	 test02->position.x = 400;
	 test02->position.y = 50;
	 test02->rec = { (int)test02->position.x,(int)test02->position.y, 80,80 };
	 test02->mass = 15;
	 test02->restitutionCoeff = 0.5f;
	 test02->frictionCoeff = .09f;
	 App->physics->bodies.add(test02);
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
	SDL_RenderFillRect(App->renderer->renderer, &test01->rec);
	SDL_SetRenderDrawColor(App->renderer->renderer, 135, 0, 100, 255);
	SDL_RenderFillRect(App->renderer->renderer, &test02->rec);
	return UPDATE_CONTINUE;
}