#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "map.hpp"

#define WHITE 255, 255, 255, 255

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

static const auto WIDTH = 1280;
static const auto HEIGHT = 720;

const auto TILE_SIZE = 32;
const auto ROWS = 40;
const auto COLUMNS = 40;

extern char mapArray[ROWS][COLUMNS];

struct Color
{
	int r;
	int g;
	int b;
	int a;
};

class Entity
{
public:
	Entity(int _x, int _y, Color _color)
	:m_X(_x),
	 m_Y(_y),
	 m_Color(_color)
	{}

	int getX() const { return m_X; }
	int getY() const { return m_Y; }

	void setX(int _x) { m_Rect.x = _x; }
	void setY(int _y) { m_Rect.y = _y; }

	void render()
	{
		SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
		SDL_RenderFillRect(renderer, &m_Rect);
	}

private:
	int m_X, m_Y;
	Color m_Color;
	SDL_Rect m_Rect = {m_X, m_Y, TILE_SIZE - 3, TILE_SIZE - 3};
};

bool init(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to intialize SDL2, " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(!window)
	{
		std::cout << "Failed to create the window, " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		std::cout << "Failed to create the renderer, " << SDL_GetError() << std::endl;
		return false;
	}	

	return true;
}

int main(void)
{
	bool running = init();
	SDL_Event event;

	Color blue_ = {0, 0, 255, 255};
	Color pink_orange = {255, 69, 78, 255};
	Color dark_grey = {30, 30, 30, 255};

	Entity player(100, 100, pink_orange);

	std::vector<Entity> Walls;

	for(size_t i = 0; i < ROWS; ++i)
	{
		for(size_t j = 0; j < COLUMNS; ++j)
		{
			if(mapArray[i][j] == 'p')
			{
				std::cout << "player is at index: " << i << ", " << j << std::endl;
				player.setX(j * TILE_SIZE);
				player.setY(i * TILE_SIZE);

				std::cout << i * TILE_SIZE << std::endl;
				std::cout << j * TILE_SIZE << std::endl;
			}

			else if(mapArray[i][j] == 'w')
			{
				Walls.emplace_back((j * TILE_SIZE), (i * TILE_SIZE), dark_grey);
			}
		}
	}

	while(running)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			if(event.type == SDL_QUIT) running = false;
		}

		SDL_SetRenderDrawColor(renderer, WHITE);
		SDL_RenderClear(renderer);

		player.render();

		for(auto &i : Walls) 
		{
			i.render();
		}

		for(size_t i = 0; i < Walls.size(); ++i)
		{

			// std::cout << i << ":" << Walls[i].getX() << ", " << Walls[i].getY() << std::endl;
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;
	SDL_Quit();

	return EXIT_SUCCESS;
}
