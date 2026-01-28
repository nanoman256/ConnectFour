
#include<SDL3_ttf/SDL_ttf.h>
#include<String>
#pragma once
class TextLabel
{
public:
	TextLabel() {}
	TextLabel(int x, int y, int h, int w)
	{
		SetRect(x, y, h, w);
	};
	void SetLabel(SDL_Renderer* renderer, TTF_Font* font, const std::string &label);
	void Draw(SDL_Renderer* renderer);
	void DrawTo(SDL_Renderer* renderer, int x, int y, int l, int w);
	void SetRect(float x, float y, float h, float w);
	SDL_FRect GetRect();
	~TextLabel() 
	{
		if (texture) SDL_DestroyTexture(texture);
	}

private:
	SDL_Texture* texture = nullptr;
	SDL_FRect destRect = {0, 0, 0, 0};
};

