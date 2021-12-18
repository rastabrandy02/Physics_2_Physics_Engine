#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "p2Point.h"




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
	 
	 ground->rec = { 0, SCREEN_HEIGHT - 150, SCREEN_WIDTH, 150 };
	 App->physics->bodies.add(ground);

	 test01 = new PhysBody(BODY_RECTANGLE);
	 test01->position.x = 10;
	 test01->position.y = 50;
	 test01->velocity.x = 200;

	 test01->rec = { (int)test01->position.x,(int) test01->position.y, 20,20 };
	 test01->mass = 30;
	 test01->restitutionCoeff = 0.7f;
	 test01->liftCoeff = 2.f;
	 App->physics->bodies.add(test01);

	 test02 = new PhysBody(BODY_RECTANGLE);
	 test02->position.x = 400;
	 test02->position.y = 50;
	 test02->rec = { (int)test02->position.x,(int)test02->position.y, 80,80 };
	 test02->mass = 150;
	 test02->restitutionCoeff = 0.5f;
	 App->physics->bodies.add(test02);
	/* plantPos.x = 200;
	 plantPos.y = SCREEN_HEIGHT - 175;
	 plant = { plantPos.x, plantPos.y, 10, 75 };*/
	

	 background = App->textures->Load("Images/background.png");
	 

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	
	
	return UPDATE_CONTINUE;
}
update_status ModuleSceneIntro::Update(float dt)
{
	App->renderer->Blit(background, 0, 0);
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
	{
		p2Point<float> force;
		force.x = 0;
		force.y = -20000;
		App->player->GetPhysbody()->acceleration = force;
	}

	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(App->renderer->renderer, &ground->rec);
	SDL_SetRenderDrawColor(App->renderer->renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(App->renderer->renderer, &test01->rec);
	SDL_SetRenderDrawColor(App->renderer->renderer, 135, 0, 100, 255);
	SDL_RenderFillRect(App->renderer->renderer, &test02->rec);
	return UPDATE_CONTINUE;
}
