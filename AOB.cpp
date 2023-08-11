#include "AOB.hpp"
#include "Tilemap.hpp"

#include <string>
#include <iostream>



AOB::AOB(int window_width, int window_height)
{	
	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;

	SDL_CreateWindowAndRenderer(window_width, window_height,SDL_WINDOW_RESIZABLE, &game_window, &game_window_renderer);

	SDL_RenderSetLogicalSize(game_window_renderer, window_width, window_height);
}

void AOB::gameLoop() {
	bool running = true;
	Tilemap tilemap(game_window_renderer, 40, 40);



	//get pointer to keys for SDL keyboard input and basic camera manipulation
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	//static variables for keeping track of how far away from 0,0 the camera is
	static int offsetY = 0;
	static int offsetX = 0;

	while (running) {
		while (SDL_PollEvent(&game_window_event) > 0) {
			// Event handler
			if (game_window_event.type == SDL_QUIT) {
				running = false;
			}
		}

		// Clear the renderer
		SDL_RenderClear(game_window_renderer);


		//TODO change clamp to be affected by tileset size instead of 39
		if (keys[SDL_SCANCODE_D]) {
			offsetX++;
		}
		if (keys[SDL_SCANCODE_A]) {
			offsetX--;
		}
		if (keys[SDL_SCANCODE_W]) {
			offsetY--;
		}
		if (keys[SDL_SCANCODE_S]) {
			offsetY++;
		}
		if (offsetX > 20) {
			offsetX = 20;
		}
		if (offsetX < 0) {
			offsetX = 0;
		}
		if (offsetY > 20) {
			offsetY = 20;
		}
		if (offsetY < 0) {
			offsetY = 0;
		}



		tilemap.renderTilemap(offsetX, offsetY);


		// Update screen
		SDL_RenderPresent(game_window_renderer);

		// Delay to control frame rate
		SDL_Delay(30); // Adjust the delay as needed for your desired frame rate
	}
}