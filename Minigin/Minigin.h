#pragma once
struct SDL_Window;
namespace dae
{
	class Minigin
	{
		const std::chrono::seconds msPerFrame = std::chrono::seconds(1);//16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() ;
		void Cleanup();
		void Run();
	};
}