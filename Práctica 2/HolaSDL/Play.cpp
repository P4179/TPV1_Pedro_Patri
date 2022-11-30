#include "Play.h"
#include "Game.h"

void Play::update() {
	if (Button::clicked) {
		game->setMenu(false);
	}
}