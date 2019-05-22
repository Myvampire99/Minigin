#include "MiniginPCH.h"
#include "Minigin.h"
#include "Scene.h"
#include "DigDugLevel.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);


}


void dae::Minigin::LoadGame() 
{
	Scene *scene = new DigDugLevel();
	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetSceneActive("DigDugLevel", true);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		//local Initialize
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = Singleton<InputManager>::GetInstance();
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		double  lag = 0.0f;
		//


		sceneManager.Initialize(); // in loop but check if new

		while (doContinue)
		{
			//Calculate deltaTime and lag
			const auto currentTime = std::chrono::high_resolution_clock::now();
			double  deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			//
			dae::Singleton<ServiceLocator>::GetInstance().SetElapsedTime(float(deltaTime));


			

			doContinue = input.ProcessInput();
			input.HandleInput();

			//while (lag*10 >= msPerFrame) {
				//
				
				//
				sceneManager.Update(float(deltaTime));
				lag -= msPerFrame;
			//}

			
			renderer.Render();

			//TODO: Before everything maybe
			dae::Singleton<CollisionManager>::GetInstance().Update();
		}
	}

	Cleanup();
}
