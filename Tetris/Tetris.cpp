#include "Game.h"

int main()
{
	Game game;
	std::srand(time(0));

	

	while (game.running())
	{
		game.update();
		game.render();
	}
	return 0;
}