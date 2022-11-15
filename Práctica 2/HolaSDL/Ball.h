#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include <fstream>

class Game;
using uint = unsigned int;

class Ball {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Vector2D dir;
	Texture* texture = nullptr;
	Game* game = nullptr;

	SDL_Rect getDestRect() const;

public:
	// constructor
	Ball(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture, Game* game) :
		pos(pos), width(width), height(height), dir(dir), texture(texture), game(game) {}

	// renderizado
	void render() const;

	// actualizarse
	// moverse de acuerdo a su dirección
	// cambiar de dirección de acuerdo al vector de colisión al rebotar contra un objeto
	void update();

	// guardar la pos y la dir de la bola
	void saveGame(ofstream& out) const;

	void recolocate(Vector2D pos, Vector2D dir) {
		this->pos = pos;
		this->dir = dir;
	}
};