#pragma once

#include "checkML.h"
#include "Reward.h"

class Game;

class RewardChangePlatform : public Reward {
private:
	uint changeSize = 0;
public:
	RewardChangePlatform(Vector2D pos, uint width, uint height, Texture* texture, Game* game, uint rowSprite, Paddle* paddle, uint changeSize) :
		Reward(pos, width, height, texture, game, rowSprite, paddle), changeSize(changeSize) {}

	virtual void update();

	virtual void saveFromFile(ofstream& out) const;

	// redefinido para que deje de ser una clase virtual pura
	virtual void handleEvents(const SDL_Event& event) {}
};