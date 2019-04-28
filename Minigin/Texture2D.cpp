#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}

float dae::Texture2D::GetWidth() const
{
	int w, h;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);
	return float(w);
}

float dae::Texture2D::GetHeight() const
{
	int w, h;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);
	return float(h);
}