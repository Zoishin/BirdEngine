#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"

Game::Game()
{
	isRunning = false;
	
	Logger::Log("Game constructor called!");
}

Game::~Game()
{
	//TODO:
	Logger::Log("Game destructor called!");
}

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = 800;// displayMode.w;
	windowHeight = 600;//displayMode.h;

	window = SDL_CreateWindow(
		"BirdEngine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		Logger::Error("Error initializing SDL");
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		Logger::Error("Error creating SDL renderer");
		return;
	}

	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	isRunning = true;
}


void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			break;
		default:
			break;
		}
	}
}


void Game::Run()
{
	Setup();
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup()
{
	//TODO: Initialize game objects
	//Entity tank = registry.CreateEntity();
	//tank.AddComponent<TransformComponent>();
	//tank.AddComponent<BoxColliderComponent>();
	//tank.AddComponent<SpriteComponent>("./assets/image/tank.png");

}

void Game::Update()
{
	//TODO: if we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
	//while(!SDL_TICKS_PASSED(SDL_GetTicks(), millisecsPreviousFrame + MILLISECS_PER_FRAME));

	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	
	if(timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
		SDL_Delay(timeToWait);


	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

	//Store the current frame time
	millisecsPreviousFrame = SDL_GetTicks();

	//TODO:Update game objects
	//MovementSystem.Update();
	//CollisionSystem.Update();
	//DamageSystem.Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	//TODO: Render all game object

	SDL_RenderPresent(renderer);

}


void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

