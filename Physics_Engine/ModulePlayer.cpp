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
	body->position.x = 48 * 3;
	body->position.y = 48 * 5;
	startPos = body->position;


	body->rec = { ((int)body->position.x - 15),((int)body->position.y - 15),30, 40 };
	body->mass = 100;
	body->restitutionCoeff = 1.f;
	body->liftCoeff = 0.2f;
	body->frictionCoeff = 0.9f;

	tex_player = App->textures->Load("Assets/images/worm.png");
	Arrow = App->textures->Load("Assets/images/arrow.png");
	angle = 0;

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

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		body->position = startPos;
		body->velocity.SetToZero();
		body->acceleration.SetToZero();
	}
	//560, 750
	if (body->position.x > 560 && body->position.x < 560 + 74 && body->position.y + body->rec.h / 2 > 750)
	{
		p2Point<float> i(0, -40000);
		body->ApplyImpulse(i);
	}

	float angleSpeed = 3;

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT)
	{
		angle += angleSpeed;
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		angle -= angleSpeed;
	}

	//LOG("v %f", body->velocity.y);
	//LOG("a %f", body->acceleration.y);
	//LOG("pos %f, %f", body->position.x, body->position.y);
	
	return UPDATE_CONTINUE;
}
update_status ModulePlayer::Update(float dt)
{
	
	//LOG("v y: %f", body->velocity.y);
	//LOG("a y; %f", body->acceleration.y);

	int t = 50;

	SDL_SetRenderDrawColor(App->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(App->renderer->renderer,
		body->position.x + t + App->renderer->camera.x,
		body->position.y + App->renderer->camera.y,
		body->position.x + body->velocity.x + t + App->renderer->camera.x,
		body->position.y + body->velocity.y + App->renderer->camera.y);


	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		weaponNumber--;
	}if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		weaponNumber++;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{

		int force = 800;

		switch (weaponNumber)
		{
		case -1:
		{
			weaponNumber = 1;


		}
		break;
		case 0:
		{
			p2Point<float> projAcc(0, 0);
			p2Point<float> projVel(force * cos(angle * PI / 180), force * sin(angle * PI / 180));
			App->entity_handler->CreateEntity(BOMB, body->position.x + 20, body->position.y - 20, projAcc, projVel);


		}
		break;
		case 1:
		{
			p2Point<float> projAcc(0, 0);
			p2Point<float> projVel(force * cos(angle * PI / 180), force * sin(angle * PI / 180));
			App->entity_handler->CreateEntity(EGG, body->position.x + 20, body->position.y - 20, projAcc, projVel);


		}
		break;
		case 2:
		{
			weaponNumber = 0;


		}
		break;

		default:
			break;
		}

	}
	LOG("%i", weaponNumber);

	return UPDATE_CONTINUE;
}
update_status ModulePlayer::PostUpdate(float dt)
{

	App->renderer->Blit(tex_player, body->position.x - 15, body->position.y - 12, NULL);

	App->renderer->Blit(
		Arrow,
		body->position.x + 50,
		body->position.y,
		NULL, 1, angle,
		- 50,
		6
	);
	switch (weaponNumber)
	{
	case -1:
	{
		weaponNumber = 1;


	}
	case 0:
	{
	
		App->renderer->Blit(App->entity_handler->tex_bomb, 100, 100, NULL, 0);
	}
	break;
	case 1:
	{
		App->renderer->Blit(App->entity_handler->tex_egg, 100, 100, &App->entity_handler->rec_egg, 0);

	}
	break;
	case 2:
	{
		weaponNumber = 0;


	}
	break;

	default:
		break;
	}
	
	return UPDATE_CONTINUE;
}



