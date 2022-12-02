#include "RewardChangePlatform.h"
#include "Game.h"

void RewardChangePlatform::update() {
	Reward::update();
	if (game->collidesRewards(getRect(), hasCollided)) {
		if (hasCollided) {
			paddle->setWidth(paddle->getWidth() + changeSize);
		}
		game->destroyMe(this);
	}
}

void RewardChangePlatform::saveFromFile(ofstream& out) const {
	out << "BigPlatform" << endl;
	MovingObject::saveFromFile(out);
}