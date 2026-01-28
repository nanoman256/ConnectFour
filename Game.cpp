#include "Game.h"
#include <string>

Game::Game(SDL_Renderer* renderer, std::shared_ptr<Mouse> mouse, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) :
	m_renderer(renderer), m_grid(gridHeight, std::vector<int>(gridWidth, 0)), m_font(TTF_OpenFont("font.ttf", 18.0f)), m_player1(p1), m_player2(p2)
{
	m_mouse = mouse;
}

void Game::DrawGrid()
{
	int dY = gridOffsetY;
	for (int i = 0; i < m_grid.size(); i++)
	{
		int dX = gridOffsetX;
		dY = gridOffsetY + (i * squareHeight);
		for (int j = 0; j < m_grid[0].size(); j++)
		{
			dX = gridOffsetX + (j * squareLength);
			SDL_FRect square;
			square.h = squareHeight;
			square.w = squareLength;
			square.x = dX;
			square.y = dY;
			int pogOffsetX = squareLength / 2 + dX;
			int pogOffsetY = squareHeight / 2 + dY;
			if (m_grid[i][j] == 1)
			{
				SDL_SetRenderDrawColor(m_renderer, RED.r, RED.g, RED.b, RED.a);
				DrawPog(pogOffsetX, pogOffsetY);
			}
			if (m_grid[i][j] == 2)
			{
				SDL_SetRenderDrawColor(m_renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
				DrawPog(pogOffsetX, pogOffsetY);
			}
			if (mouseOnGrid && highlightX == j && m_grid[i][j] == 0)
			{
				if (m_player1->isTurn())
					SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 125);
				else
					SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
			}
			else
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

			SDL_RenderRect(m_renderer, &square);
		}
	}
}

const SDL_Point Game::GridToPixel(int x, int y)
{
	int xPos = gridOffsetX + x * squareLength;
	int yPos = gridOffsetY + y * squareHeight;
	return { xPos, yPos };
}

void Game::DrawPog(int cX, int cY)
{
	std::vector<SDL_Point> points;
	float radius = (squareLength - 10) / 2;
	float diameter = (radius * 2);
	while (radius != 0)
	{
		float x = radius - 1;
		float y = 0;
		float tx = 1;
		float ty = 1;
		float error = (tx - diameter);
		while (x >= y)
		{
			SDL_RenderPoint(m_renderer, cX + x, cY + y);
			SDL_RenderPoint(m_renderer, cX - x, cY + y);
			SDL_RenderPoint(m_renderer, cX + x, cY - y);
			SDL_RenderPoint(m_renderer, cX - x, cY - y);
			SDL_RenderPoint(m_renderer, cX + y, cY + x);
			SDL_RenderPoint(m_renderer, cX - y, cY + x);
			SDL_RenderPoint(m_renderer, cX + y, cY - x);
			SDL_RenderPoint(m_renderer, cX - y, cY - x);
			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
		radius--;
	}
}

bool Game::CheckAdjacent(int x, int y)
{
	std::vector<std::vector<std::pair<int, int>>> directions = {
		{ {1,  0}, { -1,  0} }, //up down 
		{ {0,  1}, {  0, -1} }, //left right
		{ {1, -1}, { -1,  1} }, //diagonal up-right
		{ {1,  1}, { -1, -1} } //diagonal up-left
	};
	std::vector<int> counts(4, 1);
	int playerID;
	if (m_player1->isTurn())
		playerID = 1;
	else
		playerID = 2;

	for (int direction = 0; direction < directions.size(); direction++)
	{
		for (int pair = 0; pair < directions[0].size(); pair++)
		{
			int dX = directions[direction][pair].first;
			int dY = directions[direction][pair].second;
			int cX = x + dX;
			int cY = y + dY;
			while (cY >= 0 && cX >= 0 && cY < m_grid.size() && cX < m_grid[0].size() && m_grid[cY][cX] == playerID)
			{
				counts[direction]++;
				cX += dX;
				cY += dY;
			}
		}
	}
	for (int i = 0; i < counts.size(); i++)
	{
		if (counts[i] >= 4)
		{
			SetNextGameState(GameState::GameOver);
			if (m_player1->isTurn()) m_player1->addWin();
			else m_player2->addWin();
			return true;
		}
	}
	return false;
}

void Game::TogglePlayer()
{
	if (togglePlayer)
	{
		m_player1->toggleTurn();
		m_player2->toggleTurn();
		togglePlayer = false;
	}
}

bool Game::PlacePog(int xPos)
{
	int yPos = GetAvailableLocation(xPos);
	if (xPos >= 0 && yPos >= 0)
	{
		m_grid[yPos][xPos] = m_player2->isTurn() ? 2 : 1;
		if (CheckAdjacent(xPos, yPos))
			return true;
		togglePlayer = true;
		return false;
	}
	//togglePlayer = false;
	return false;
}

bool Game::PlayerMakeMove()
{
	int pog = 0;
	if (m_player2->isTurn())
		pog = 1;
	else
		pog = 2;
	int decision = 4;
	bool isWin = PlacePog(decision);
	if (isWin)
	{
		return true;
	}
	if (decision == -1)
		return false;
}

GameState Game::GetNextGameState() 
{
	return nextGameState;
}

void Game::SetNextGameState(GameState state) 
{
	nextGameState = state;
}

void Game::HandleMouseMotion()
{
	//when the mouse moves we want to check which coordinates it is on
	CheckGrid();
}

void Game::HandleMouseClick()
{
	if (mouseOnGrid && PlacePog(highlightX))
		running = false;
}

void Game::HandleInput() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT) 
			SetNextGameState(GameState::Exit);
		if (event.type == SDL_EVENT_MOUSE_MOTION)
		{
			m_mouse->UpdateMousePos(event.motion.x, event.motion.y);
			HandleMouseMotion();
		}
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			HandleMouseClick();
		}
	}
}

void Game::Render() 
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	DrawGrid();
	DrawHoverPog();
	int playerID = m_player2->isTurn() ? 2 : 1;
	std::string playerString = "Player" + std::to_string(playerID);
	SDL_Surface* solidText = TTF_RenderText_Solid(m_font, playerString.c_str(), 0, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, solidText);
	SDL_DestroySurface(solidText);

	SDL_FRect destRect = { 300, 100, 150, 50 };
	SDL_RenderTexture(m_renderer, texture, NULL, &destRect);
	SDL_RenderPresent(m_renderer);
}

void Game::Update() 
{
	TogglePlayer();
}
//added comment
void Game::CheckGrid()
{
	int totalLength = squareLength * gridWidth;
	int totalHeight = squareHeight * gridHeight;

	SDL_FPoint mouseCoords = m_mouse->GetMousePos();

	int mousePtX = mouseCoords.x - gridOffsetX;
	int mousePtY = mouseCoords.y - gridOffsetY;

	int mouseCoordX = mousePtX / squareLength;
	int mouseCoordY = mousePtY / squareHeight;

	if (mousePtX > 0 &&
		totalLength > mousePtX &&
		mousePtY > 0 &&
		totalHeight > mousePtY) 
	{
		mouseOnGrid = true;
		highlightX = mouseCoordX;
		highlightY = mouseCoordY;
		int openPosition = GetAvailableLocation(mouseCoordX);
		auto pixel = GridToPixel(mouseCoordX, openPosition);
		hoverPogX = pixel.x;
		hoverPogY = pixel.y;
	}
	else
	{
		highlightX = -1;
		highlightY = -1;
		mouseOnGrid = false;
	}
}

int Game::GetAvailableLocation(int x)
{
	int position = -1;
	for (int i = 0; i < m_grid.size(); i++)
	{
		if (m_grid[i][x] == 0)
		{
			position++;
		}
	}
	return position;
}

void Game::DrawHoverPog()
{
	if (m_player1->isTurn())
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0);
	else
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 0);

	if (mouseOnGrid)
	{
		DrawPog(hoverPogX + squareLength / 2, hoverPogY + squareHeight / 2);
	}
}

void Game::ClearGrid() 
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		for (int j = 0; j < m_grid[0].size(); j++)
		{
			m_grid[i][j] = 0;
		}
	}
}

void Game::OnClose() //on state end
{
	ClearGrid();
}

void Game::OnStart() //on state start
{
	SetNextGameState(GameState::Game);
	togglePlayer = true;
	TogglePlayer();
}