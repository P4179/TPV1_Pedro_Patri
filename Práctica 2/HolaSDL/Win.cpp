#include "Win.h"
#include "Game.h"

void Win::render() {
	if (game->getWin()) {
		ArkanoidObject::render();
	}
}