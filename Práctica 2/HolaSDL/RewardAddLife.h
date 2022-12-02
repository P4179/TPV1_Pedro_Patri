#pragma once

#include "checkML.h"
#include "Reward.h"
#include "Lifes.h"

class Game;

class RewardAddLife : public Reward {
private:
	Lifes* lifes = nullptr;

public:
	RewardAddLife(Vector2D pos, uint width, uint height, Texture* texture, Game* game, Paddle* paddle, Lifes* lifes) :
		Reward(pos, width, height, texture, game, 4, paddle), lifes(lifes) {}

	virtual void update();

	virtual void saveFromFile(ofstream& out) const;

	// redefinido para que deje de ser una clase virtual pura
	virtual void handleEvents(const SDL_Event& event) {}
};