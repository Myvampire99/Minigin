#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//
	m_TestSprite = new Sprite{ "Resources/Sprites/character.png",2,8,16,1 };
	//

}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();
	//
	m_TestSprite->Update(float(1));
	m_TestSprite->Draw({ 10,10 }, 0);
	//
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture,const dae::Vector2& DestPos, const dae::Vector2& SrcPos, const dae::Vector2& DestWH, const dae::Vector2& SrcWH) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(DestPos.x);
	dst.y = static_cast<int>(DestPos.y);
	dst.w = static_cast<int>(DestWH.x);
	dst.h = static_cast<int>(DestWH.y);

	SDL_Rect src;
	src.x = static_cast<int>(SrcPos.x);
	src.y = static_cast<int>(SrcPos.y);
	src.w = static_cast<int>(SrcWH.x);
	src.h = static_cast<int>(SrcWH.y);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

