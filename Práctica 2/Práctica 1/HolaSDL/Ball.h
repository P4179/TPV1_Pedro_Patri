#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
class Game;
using uint = unsigned int;

class Ball {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Vector2D dir;
	Texture* texture = nullptr;
	// se pone el #include "Game.h" en el Ball.cpp
	// otra forma es utilizar las directivas #ifdef y #ifndef
	// se incluye cuando está sin definir, una vez definido no se incluye
	Game* game = nullptr;

public:
	// constructor
	Ball(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture, Game* game) :
		pos(pos), width(width), height(height), dir(dir), texture(texture), game(game) {}

	// dibujarse
	void render() {
		texture->render(getDestRect());
	}

	// actualizarse
	// moverse de acuerdo a su dirección
	// cambiar de dirección de acuerdo al vector de colisión al rebotar contra un objeto
	void update() {
		Vector2D colVector;
		if (game->collides(getDestRect(), colVector)) {
			dir = dir - (colVector * (2 * (dir * colVector)));
			// dir = Vector2D(0, 0);
		}
		pos = pos + dir;
	}

	SDL_Rect getDestRect() {
		SDL_Rect destRect;
		destRect.x = pos.getX();
		destRect.y = pos.getY();
		destRect.w = width;
		destRect.h = height;
		return destRect;
	}
};

