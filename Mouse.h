#include <SDL3/SDL.h>
#pragma once
class Mouse
{
public:
	Mouse() {};
	SDL_FPoint GetMousePos() 
	{
		return { mouseX, mouseY };
	}
	void UpdateMousePos(float x, float y)
	{
		mouseX = x;
		mouseY = y;
	}
	
private:
	float mouseX = 0;
	float mouseY = 0;
};

