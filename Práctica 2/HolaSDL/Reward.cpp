#include "Reward.h"
#include "Game.h"

void Reward::render() const {
	uint textFrameW = texture->getW() / texture->getNumCols();
	uint col = (textFrameW * int(((SDL_GetTicks() / TIME_PER_FRAME) % texture->getNumCols()))) / textFrameW;
	texture->renderFrame(getRect(), row, col);
}

void Reward::update() {
	pos = pos + dir;
	if (game->collidesRewards(getRect(), hasCollided)) {
		paddle->setWidth(game->getPaddleWidth());
	}
}