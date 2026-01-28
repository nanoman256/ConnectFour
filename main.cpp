#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include "Connect4.h"
#include <Windows.h>
#include "Window.h"
using namespace std;

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) 
	{
		SDL_Log("Could not initialize SDL: %s", SDL_GetError());
	}
	if (!TTF_Init()) 
	{
		SDL_Log("Could not initialize TTF: %s", SDL_GetError());
	}
	Connect4 cnct4;
	cnct4.GameLoop();
	TTF_Quit();
	SDL_Quit();
}