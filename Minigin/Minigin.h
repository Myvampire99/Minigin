#pragma once
struct SDL_Window;
namespace dae
{
	class Minigin
	{
		const int msPerFrame = 1;//16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() ;//const
		void Cleanup();
		void Run();

		

		void TestFunction(bool &Continue);
	};
}