#include "GameOver.h"
#include "Game.h"

void GameOver::render() const {
	if (game->getGameOver()) {
		ArkanoidObject::render();
	}
}