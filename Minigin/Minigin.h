#pragma once
#include "GameObject.h"
struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() ;//const
		void Cleanup();
		void Run();
		void UpdateGame();//TEMPORARY, Need Scenes for this

		//GameObject* txt;//TEMPORARY, Need Scenes for this
		std::shared_ptr<GameObject> txt;
	};
}