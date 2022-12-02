#include "RewardAddLife.h"
#include "Game.h"

void RewardAddLife::update() {
	Reward::update();
	if (game->collidesRewards(getRect(), hasCollided)) {
		if (hasCollided) {
			lifes->addLife();
		}
		game->destroyMe(this);
	}
}

void RewardAddLife::saveFromFile(ofstream& out) const {
	out << "AddLife" << endl;
	MovingObject::saveFromFile(out);
}