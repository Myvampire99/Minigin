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

	

}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

//	SceneManager::GetInstanceScene()->Render();
	Singleton<SceneManager>::GetInstance().Render();

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


void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y,float angle) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	//Done automaticly if nullptr
	//SDL_Point center;
	//center.x = dst.x + dst.w / 2.f;
	//center.x = dst.y + dst.h / 2.f;

	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, double(angle), nullptr, SDL_FLIP_NONE);
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

void dae::Renderer::RenderTexture(const Texture2D& texture,const dae::Vector2& DestPos, const dae::Vector2& SrcPos, const dae::Vector2& DestWH, const dae::Vector2& SrcWH,bool flip) const
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

	if(!flip)
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	else
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0, nullptr, SDL_FLIP_VERTICAL);
	//TODO: Make Vertical and Horizontal
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const dae::Vector2& DestPos, const dae::Vector2& SrcPos, const dae::Vector2& DestWH, const dae::Vector2& SrcWH, float angle, const dae::Vector2& center, bool flipVert,bool flipHor,float scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(DestPos.x);
	dst.y = static_cast<int>(DestPos.y);
	dst.w = static_cast<int>(DestWH.x)*(int)scale;
	dst.h = static_cast<int>(DestWH.y)*(int)scale;

	SDL_Rect src;
	src.x = static_cast<int>(SrcPos.x);
	src.y = static_cast<int>(SrcPos.y);
	src.w = static_cast<int>(SrcWH.x);
	src.h = static_cast<int>(SrcWH.y);


	SDL_Point point;
	point.x = (int)center.x*(int)scale;
	point.y = (int)center.y*(int)scale;

	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(angle);
	UNREFERENCED_PARAMETER(center);

	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);


	//TODO: Cant do 2 flips at once
	if(!flipVert && !flipHor)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, double(angle), &point, SDL_FLIP_NONE);
	else if (flipVert) {
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, double(angle), &point, SDL_FLIP_VERTICAL);
	}
	else {
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, double(angle), &point, SDL_FLIP_HORIZONTAL);
	}
}

