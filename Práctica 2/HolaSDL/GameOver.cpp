#include "GameOver.h"
#include "Game.h"

void GameOver::render() {
	if (game->getGameOver()) {
		ArkanoidObject::render();
	}
}