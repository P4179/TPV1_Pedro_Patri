#pragma once

#include "checkML.h"
#include "Reward.h"

class Game;

class RewardPassLv : public Reward {
public:
	RewardPassLv(Vector2D pos, uint width, uint height, Texture* texture, Game* game, Paddle* paddle) :
		Reward(pos, width, height, texture, game, 0, paddle) {}

	virtual void update();

	virtual void saveFromFile(ofstream& out) const;

	// redefinido para que deje de ser una clase virtual pura
	virtual void handleEvents(const SDL_Event& event) {}
};