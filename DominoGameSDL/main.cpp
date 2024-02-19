#include "Game.h"

Game* game = NULL;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char* argv[]) {

	game = new Game();

	game->init("Dominoes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	while (game->isRunning()) {
		game->ttf_init();
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}