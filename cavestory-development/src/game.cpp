#include "SDL.h"

#include <algorithm>
#include "game.h"
#include "graphics.h"
#include "input.h"

/* Game Class
*  This class holds all information for our main game loop.
*/

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}
Game::~Game()
{
}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	this->_player = Player(graphics, 100, 100);

	int last_update_time = SDL_GetTicks();
	//Start game loop
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {  // means we have a new key i.e (Not Repeating)
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks(); // const because it us used just for the first run through
		int elapsed_time_ms = CURRENT_TIME_MS - last_update_time;
		this->update(std::min(elapsed_time_ms, MAX_FRAME_TIME));
		last_update_time = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();
	this->_player.draw(graphics);
	graphics.flip();

}

void Game::update(float elapsedTime)
{
	this->_player.update(elapsedTime);
}