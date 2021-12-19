#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleSceneIntro.h"
#include "EntityHandler.h"
#include "Ent_Bomb.h"
#include "Ent_Egg.h"
#include "Ent_Enemy_1.h"
#include "Timer.h"
#include "PerfTimer.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModulePhysics* physics;
	EntityHandler* entity_handler;
	Ent_Bomb* bomb;
	Ent_Egg* egg;
	Ent_Enemy_1* ent_enemy_1;
	
	float dt = 0.0f;
private:

	p2List<Module*> list_modules;


	PerfTimer* perfTimer;
	PerfTimer* frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	uint32 maxFrameRate = 60;

	float averageFps = 0.0f;
	
	
	

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};