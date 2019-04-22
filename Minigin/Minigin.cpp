#include "MiniginPCH.h"
#include "Minigin.h"
#include "Scene.h"


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

/**
 * Code constructing the scene world starts here
 */



void dae::Minigin::LoadGame() 
{
	dae::Scene& scene = SceneManager::GetInstance().CreateScene("Demo");
	

	std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//scene.Add(to);
	//to->SetPosition(80, 20);

	txt = std::make_shared<GameObject>();//TEMPORARY, Need Scenes for this
	txt->SetTexture("");
	txt->SetPosition(20, 20);
	txt->AddComponent(new FPSComponent);
	
	txt->AddComponent(new TextRendererComponent("BRRRR", font));
	scene.Add(txt);
	//scene.Add(to);
}

void dae::Minigin::UpdateGame()//TEMPORARY, Need Scenes for this
{
	std::string temp;
	temp = std::to_string(txt->GetComponent<FPSComponent>()->GetFps());
	txt->GetComponent<TextRendererComponent>()->SetText(temp);
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

			doContinue = input.ProcessInput();
			input.HandleInput();

			while (lag*10 >= msPerFrame) {
				UpdateGame();//Temporary//TODO: need to make proper scenes 
				sceneManager.Update(float(msPerFrame));
				lag -= msPerFrame;
			}

			renderer.Render();
		}
	}

	Cleanup();
}
