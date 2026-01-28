#include <SDL3/SDL.h>
#include <stdexcept>
#pragma once
class Window
{
public:
	Window(const char* title, int w, int h)
	{
		window = SDL_CreateWindow(
			title,
			w, h,
			SDL_WINDOW_RESIZABLE
		);

		if (!window)
		{
			SDL_Log("Could not intialize SDL Window: %s", SDL_GetError());
			throw std::runtime_error(SDL_GetError());
		}
	};
	~Window() 
	{
		if (window) 
		{
			SDL_DestroyWindow(window);
		}
	}

	SDL_Window* get() const { return window; }

private:
	SDL_Window* window = nullptr;
};

