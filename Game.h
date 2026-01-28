
#include "SDL3_ttf/SDL_ttf.h"
#include <vector>
#include "constants.h"
#include <memory>
#include "Mouse.h"
#include "IGameState.h"
#include "Player.h"

#pragma once

class Game : public IGameState
{
public:
	Game(SDL_Renderer* renderer, std::shared_ptr<Mouse> mouse, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
	bool PlacePog(int xPos);
	bool CheckAdjacent(int xPos, int yPos);

	void DrawGrid();
	void DrawHoverPog();
	void DrawPog(int cX, int cY);

	bool PlayerMakeMove();
	void HandleMouseMotion();
	void HandleMouseClick();
	void TogglePlayer();

	void CheckGrid();
	void ClearGrid();
	
	int GetAvailableLocation(int x);
	const SDL_Point GridToPixel(int x, int y);
	
	void Render();
	void Update();
	void HandleInput();
	GameState GetNextGameState();
	void SetNextGameState(GameState state);

	void OnStart();
	void OnClose();

private:
	//SDL Objects
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;

	//Grid
	std::vector<std::vector<int>> m_grid;
	// Player1 if false; Player2 if true;
	bool togglePlayer = false;
	std::shared_ptr<Player> m_player1 = nullptr;
	std::shared_ptr<Player> m_player2 = nullptr;

	bool running = true;

	std::shared_ptr<Mouse> m_mouse = nullptr;
	float mouseX = 0;
	float mouseY = 0;

	float hoverPogX = 0;
	float hoverPogY = 0;

	bool mouseOnGrid = false;
	int highlightX = -1;
	int highlightY = -1;
	GameState nextGameState = GameState::Game;
};

