#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"

class Game;

class Button : public ArkanoidObject {
protected:
	Game* game = nullptr;
	bool clicked = false;

	Button(Vector2D pos, uint width, uint height, Texture* texture, Game* game) :
		ArkanoidObject(pos, width, height, texture), game(game) {}

public:
	virtual void handleEvents(const SDL_Event& event);
};