#pragma once

#include "checkML.h"
#include "MovingObject.h"
#include "Paddle.h"

const uint TIME_PER_FRAME = 50;

class Game;

class Reward : public MovingObject {
private:
	uint row = 0;

protected:
	Game* game = nullptr;
	Paddle* paddle = nullptr;
	bool hasCollided = false;

	Reward(Vector2D pos, uint width, uint height, Texture* texture, Game* game, uint row, Paddle* paddle) :
		MovingObject(pos, width, height, texture, Vector2D(0, 1)), game(game), row(row), paddle(paddle) {}

public:
	virtual void render() const;

	virtual void update();

	// no tiene funcionalidad porque los rewards no se recolocan
	virtual void recolocate() {}
};