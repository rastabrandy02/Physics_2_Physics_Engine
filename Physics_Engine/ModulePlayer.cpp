#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	body = new PhysBody(BODY_RECTANGLE);
	App->physics->bodies.add(body);
	body->position.x = 30;
	body->position.y = SCREEN_HEIGHT - 500;
	body->rec = { ((int)body->position.x - 25),((int)body->position.y - 25), 50, 50 };
	body->mass = 100;
	body->restitutionCoeff = 0.5f;
	body->liftCoeff = 0.5;

	tex_player = App->textures->Load("Assets/worm.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::PreUpdate(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (fabs(body->velocity.x) < maxVelocity) body->velocity.x += speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (fabs(body->velocity.x) < maxVelocity) body->velocity.x -= speed;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		body->velocity.y = 0;
		body->acceleration.y -= jumpForce;
		
	}
	LOG("v %f", body->velocity.x);
	
	return UPDATE_CONTINUE;
}
update_status ModulePlayer::Update(float dt)
{
	
	//LOG("v y: %f", body->velocity.y);
	//LOG("a y; %f", body->acceleration.y);

	int t = 50;

	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(App->renderer->renderer,
		body->position.x + t,
		body->position.y,
		body->position.x + body->velocity.x + t,
		body->position.y + body->velocity.y);


	

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		p2Point<float> projAcc(0, 0);
		p2Point<float> projVel(100, -500);
		App->projectile_handler->CreateProjectile(BOMB, body->position.x + 20, body->position.y - 20, projAcc, projVel);
	}
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		p2Point<float> projAcc(0, 0);
		p2Point<float> projVel(300, -200);
		App->projectile_handler->CreateProjectile(EGG, body->position.x + 20, body->position.y - 20, projAcc, projVel);
	}


	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate(float dt)
{
	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(App->renderer->renderer, &body->rec);

	App->renderer->Blit(tex_player, body->position.x - 20, body->position.y - 50, NULL);
	
	return UPDATE_CONTINUE;
}



