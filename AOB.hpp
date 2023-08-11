#pragma once

#include <SDL.h>

class AOB
{
public:
	AOB(int window_width, int window_height);
	~AOB() = default;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;


	void gameLoop();

private:
	SDL_Window*		game_window;
	SDL_Event		game_window_event;
	SDL_Renderer*	game_window_renderer;

};