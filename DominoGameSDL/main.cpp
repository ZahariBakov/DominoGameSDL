#include "Game.h"
#include "GameConstants.h"

int main(int argc, char* argv[])
{
    Game game;

    auto windowPosition = Vector2D(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    game.Init("Dominoes", windowPosition, GetWindowsWidth(), GetWindowHeight(), 0);

    while(game.IsRunning())
    {
        game.HandleEvents();
        game.Render();
	}

    game.Deinit();

	return 0;
}
