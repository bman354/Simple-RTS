#pragma once

#include <SDL.h>


class Tilemap
{
public:
	Tilemap(SDL_Renderer* renderer, int width, int height);
	~Tilemap();

	void generateTilemap(int width, int height);
	void renderTilemap(int offsetX, int offsetY);

private:

	SDL_Renderer* renderer;

	//map of SDL_Rects that hold x and y values of each tile
	SDL_Rect tilemap[40][40];
	//map of tile IDs accessed by tilemap[row][column]
	int tileValues[40][40];

	int width;
	int height;
};

