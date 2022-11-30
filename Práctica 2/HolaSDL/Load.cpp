#include "Load.h"
#include "Game.h"

void Load::update() {
	if (Button::clicked) {
		game->loadGame();
		game->setMenu(false);
	}
}