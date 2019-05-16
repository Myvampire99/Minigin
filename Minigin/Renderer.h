#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y,float angle) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const dae::Vector2& DestPos, const dae::Vector2& SrcPos, const dae::Vector2& DestWH, const dae::Vector2& SrcWH,bool flip = false) const;
		void RenderTexture(const Texture2D& texture, const dae::Vector2& DestPos, const dae::Vector2& SrcPos, const dae::Vector2& DestWH, const dae::Vector2& SrcWH, float angle, const dae::Vector2& center, bool flipVert = false, bool flipHor = false, float scale = 1) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

	};
}

