#include "RewardPassLv.h"
#include "Game.h"

void RewardPassLv::update() {
	Reward::update();
	if (game->collidesRewards(getRect(), hasCollided)) {
		if (hasCollided) {
			game->setWin(true);
		}
		game->destroyMe(this);
	}
}

void RewardPassLv::saveFromFile(ofstream& out) const {
	out << "PassLv" << endl;
	MovingObject::saveFromFile(out);
}