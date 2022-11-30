#pragma once
#include "checkML.h"
#include "MovingObject.h"
#include <fstream>

class Game;
using uint = unsigned int;

class Ball : public MovingObject {
private:
	Game* game = nullptr;

public:
	// constructor
	Ball(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture, Game* game) :
		MovingObject(pos, width, height, texture, dir), game(game) {}

	// actualizarse
	// moverse de acuerdo a su dirección
	// cambiar de dirección de acuerdo al vector de colisión al rebotar contra un objeto
	void update();

	// redefinido para que deje de ser una clase abstracta
	virtual void handleEvents(const SDL_Event& event) {}
};