#include "TextLabel.h"
void TextLabel::SetLabel(SDL_Renderer* renderer, TTF_Font* font, const std::string& label)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, label.c_str(), 0, { 255, 255, 255, 255 }/*white*/);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
}

void TextLabel::Draw(SDL_Renderer* renderer)
{
	SDL_RenderTexture(renderer, texture, nullptr, &destRect);
}

void TextLabel::DrawTo(SDL_Renderer* renderer, int x, int y, int l, int w) 
{
	SetRect(x, y, l, w);
	Draw(renderer);
}

SDL_FRect TextLabel::GetRect() 
{
	return destRect;
}

void TextLabel::SetRect(float x, float y, float h, float w) 
{
	destRect = { x, y, h, w };
}