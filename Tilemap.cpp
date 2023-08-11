#include "Tilemap.hpp"
#include <cstdlib>


//create a new tilemap of width x height tiles (NOT in pixels)
Tilemap::Tilemap(SDL_Renderer* renderer, int width, int height)
	:renderer(renderer), width(width), height(height) {
	generateTilemap(width, height);
}

Tilemap::~Tilemap() {

}

void Tilemap::generateTilemap(int width, int height) {

	//loop through 2d array tileMap and give it a random value of 1-4 to make a random tileset to render
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			
			int sum = 0;
			int count = 0;

			/*look over 5x5 of surrounding tiles, dx = distance relative to current x, dy is distance relative to currrent y
			* nx, ny is the relative distance by coordinate from current x,y (nx = new x, ny = new y)
			*/
			for (int dx = -2; dx <= 2; dx++) {
				for (int dy = -2; dy <= 2; dy++) {
					int nx = x + dx;
					int ny = y + dy;

					//clamp to boundary of main data storage to avoid adding non existant/null values, then add to the current running count
					if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
						sum += tileValues[nx][ny];
						count++;
					}

				}
			}
			//average of 3x3 of tiles based on actual number of valid tiles counted
			int average = sum / count;
			
			if (average > 4) {
				average = 4;
			}
			else if (average < 1) {
				average = 1;
			}

			//sometimes do any number except the average
			if ((rand() % 100 + 1) > 20) {
				average = rand() % 4 + 1;
			}

			

			tileValues[x][y] = average;
			
		}
	}

	//tileMap[x][y] is now the actual tilemap to be rendered to the screen, composed to SDL_Rect objects with accurate(hopefully)
	//x and y coordinates, and a tile width of 32 by 32 pixels, according to our bitmap size

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < width; y++) {
			tilemap[x][y].x = x * 32;
			tilemap[x][y].y = y * 32;
			tilemap[x][y].w = 32;
			tilemap[x][y].h = 32;
		}
	}
}

void Tilemap::renderTilemap(int offsetX, int offsetY)
{
	// Load selected tileset to surface for dividing
	SDL_Surface* tile_map_surface = SDL_LoadBMP("classicTiles.bmp");

	// Convert surface to texture
	SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
	SDL_FreeSurface(tile_map_surface);

	SDL_Rect select_tile_1;
	select_tile_1.x = 0;
	select_tile_1.y = 0;
	select_tile_1.w = 32;
	select_tile_1.h = 32;

	SDL_Rect select_tile_2;
	select_tile_2.x = 32;
	select_tile_2.y = 0;
	select_tile_2.w = 32;
	select_tile_2.h = 32;

	SDL_Rect select_tile_3;
	select_tile_3.x = 0;
	select_tile_3.y = 32;
	select_tile_3.w = 32;
	select_tile_3.h = 32;

	SDL_Rect select_tile_4;
	select_tile_4.x = 32;
	select_tile_4.y = 32;
	select_tile_4.w = 32;
	select_tile_4.h = 32;

	// Render tiles
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int tileX = x + offsetX;
			int tileY = y + offsetY;

			//boundary checks
			if (tileX >= 0 && tileX < width && tileY >= 0 && tileY < height) {
				switch (tileValues[tileX][tileY]) {
				case 1:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_1, &tilemap[x][y]);
					break;
				case 2:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_2, &tilemap[x][y]);
					break;
				case 3:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_3, &tilemap[x][y]);
					break;
				case 4:
					SDL_RenderCopy(renderer, tile_texture, &select_tile_4, &tilemap[x][y]);
					break;
				}
			}
		}
	}
	SDL_DestroyTexture(tile_texture);
}