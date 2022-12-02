#include "Win.h"
#include "Game.h"

void Win::render() const {
	if (game->getWin()) {
		ArkanoidObject::render();
	}
}