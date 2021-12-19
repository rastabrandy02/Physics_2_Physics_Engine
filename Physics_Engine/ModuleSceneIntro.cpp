#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "p2Point.h"
#include "PhysBody.h"




ModuleSceneIntro::ModuleSceneIntro(Application* App, bool start_enabled) : Module(App, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	terrain = App->textures->Load("Assets/images/terrain.png");
	meta = App->textures->Load("Assets/images/meta.png");


	App->renderer->camera.x = App->renderer->camera.y = 0;
	
	ground = App->physics->CreateBody(BodyType::BODY_RECTANGLE, 48, 48 * 16, 48 * 10, 48 * 2, 0);
	ground->isStatic = true;
	wall_1 = App->physics->CreateBody(BodyType::BODY_RECTANGLE, 0, 0, 48, 48 * 16, 0);
	wall_1->isStatic = true;
	wall_2 = App->physics->CreateBody(BodyType::BODY_RECTANGLE, 48 * 9, 48 * 11, 48 * 2, 48 * 8, 0);
	wall_2->isStatic = true;


	//wall_2 = App->physics->CreateBody(BodyType::BODY_RECTANGLE, 48 * 11, 48 * 9, 48 * 12, 48 * 8, 0);
	//wall_2->isStatic = true;
	 
	 //ground->rec = { 48,48 * 17 , 48 * 12, 48 * 2};
	 //App->physics->bodies.add(ground);

	 //test01 = new PhysBody(BODY_RECTANGLE);
	 //test01->position.x = 30;
	 //test01->position.y = 100;
	 //test01->velocity.x = 100;
	 //test01->velocity.y = -100;
	 //test01->rec = { (int)test01->position.x,(int) test01->position.y, 20,20 };
	 //test01->mass = 30;
	 //test01->restitutionCoeff = 0.7f;
	 //test01->liftCoeff = 0.5f;
	 //App->physics->bodies.add(test01);
	 //
	 //test02 = new PhysBody(BODY_RECTANGLE);
	 //test02->position.x = 400;
	 //test02->position.y = 50;
	 //test02->rec = { (int)test02->position.x,(int)test02->position.y, 80,80 };
	 //test02->mass = 150;
	 //test02->restitutionCoeff = 0.5f;
	 //App->physics->bodies.add(test02);
	/* plantPos.x = 200;
	 plantPos.y = SCREEN_HEIGHT - 175;
	 plant = { plantPos.x, plantPos.y, 10, 75 };*/

	 background = App->textures->Load("Images/background.png");

	 App->renderer->camera.x = 0;
	 App->renderer->camera.y = 0;

	 

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

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		freeCam = !freeCam;
	}

	
	if (!freeCam)
	{
		int w, h;

		w = SCREEN_WIDTH;
		h = SCREEN_HEIGHT;

		
		float playerX = App->player->body->position.x;
		float playerY = App->player->body->position.y;

		int marginX = 48 * 10;
		int marginY = 48 * 11;
		
		//App->renderer->camera.x = -(playerX );

		if (playerX > marginX)
		{
			App->renderer->camera.x = -(playerX - marginX);
		}


		if (playerX >= 48 * 100 - w + marginX)
		{

			App->renderer->camera.x = -(48 * 100 - (w));
		}

		if (playerY > marginY)
		{
			App->renderer->camera.y = -(playerY - marginY);
		}


		if (playerY >= 30 * 48 - h + marginY)
		{

			App->renderer->camera.y = -(30 * 48 - (h));
		}


		//if (playerX > marginX && playerX < 100 * 48)
		//{
		//	App->renderer->camera.x = -playerX * 48 * 1.042f + marginX * 48;
		//}



	}
	else
	{

		int cameraSpeed = 10;
		if ((App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))
				App->renderer->camera.y += cameraSpeed;
			


		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)	
				App->renderer->camera.y -= cameraSpeed;
			



		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
				App->renderer->camera.x += cameraSpeed;
			



		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
				App->renderer->camera.x -= cameraSpeed;
			

	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(App->renderer->renderer, &ground->rec);
	//SDL_SetRenderDrawColor(App->renderer->renderer, 0, 255, 0, 255);
	//SDL_RenderFillRect(App->renderer->renderer, &test01->rec);
	//SDL_SetRenderDrawColor(App->renderer->renderer, 135, 0, 100, 255);
	//SDL_RenderFillRect(App->renderer->renderer, &test02->rec);

	SDL_Rect groundRect = { 2 * 48,0,12 * 48,2 * 48 };


	App->renderer->Blit(terrain, 0, 0, NULL);

	return UPDATE_CONTINUE;
}
