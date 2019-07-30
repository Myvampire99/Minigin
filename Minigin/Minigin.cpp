#include "MiniginPCH.h"
#include "Minigin.h"
#include "Scene.h"
#include "DebugScene.h"
#include "ClassicLevel.h"
#include "CoopLevel.h"
#include "VersusLevel.h"

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

	m_CurrentLevel = Level::Classic;
}


void dae::Minigin::LoadGame() 
{
	m_Subject = new Subject();
	Singleton<SceneManager>::GetInstance().AddSubject(m_Subject);
	m_Subject->AddObserver(&dae::Singleton<CollisionManager>::GetInstance());

	Scene *scene = new CoopLevel("CoopLevel");
	Singleton<SceneManager>::GetInstance().AddScene(scene);
	
	Scene *sceneC = new ClassicLevel("ClassicLevel");
	Singleton<SceneManager>::GetInstance().AddScene(sceneC);

	Scene *sceneD = new VersusLevel("VersusLevel");
	Singleton<SceneManager>::GetInstance().AddScene(sceneD);

	Singleton<SceneManager>::GetInstance().SetSceneActive("ClassicLevel", true);

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
		// Initialize
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = Singleton<SceneManager>::GetInstance();
		auto& input = Singleton<InputManager>::GetInstance();
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		std::chrono::seconds lag = std::chrono::seconds(0);
		//


		sceneManager.Initialize();

		while (doContinue)
		{
			//Calculate deltaTime and lag
			const auto currentTime = std::chrono::high_resolution_clock::now();
			double deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime);
			//

			dae::Singleton<ServiceLocator>::GetInstance().SetElapsedTime(float(deltaTime));

			
			

			doContinue = input.ProcessInput();
			if (!doContinue) {
				
				switch (m_CurrentLevel)
				{
				case dae::Minigin::Classic:
					Singleton<SceneManager>::GetInstance().SetSceneActive("ClassicLevel", false);
					Singleton<SceneManager>::GetInstance().SetSceneActive("CoopLevel", true);
					m_CurrentLevel = dae::Minigin::Coop;
					break;
				case dae::Minigin::Coop:
					Singleton<SceneManager>::GetInstance().SetSceneActive("CoopLevel", false);
					Singleton<SceneManager>::GetInstance().SetSceneActive("VersusLevel", true);
					m_CurrentLevel = dae::Minigin::Versus;
					break;
				case dae::Minigin::Versus:
					Singleton<SceneManager>::GetInstance().SetSceneActive("VersusLevel", false);
					Singleton<SceneManager>::GetInstance().SetSceneActive("ClassicLevel", true);
					m_CurrentLevel = dae::Minigin::Classic;
					break;
				default:
					break;
				}
			}

			input.HandleInput();

			sceneManager.Update(float(deltaTime));
			dae::Singleton<CollisionManager>::GetInstance().Update();

			while (lag >= msPerFrame) {
				sceneManager.Update(float(deltaTime));
				dae::Singleton<CollisionManager>::GetInstance().Update();
				lag -= msPerFrame;
			}
			
			renderer.Render();


			doContinue = true;//===================
		}
	}

	Cleanup();
}
