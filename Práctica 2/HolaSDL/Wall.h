#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Wall {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Texture* texture = nullptr;
	// se podría calcular el vector de colisión, pero es mejor definirlo en el constructor
	Vector2D colVector;

	// devuelve el rectángulo destino de la pared
	SDL_Rect getDestRect() const;

public:
	// se necesita un constructor predeterminado para poder crear arrays
	Wall() {}
	Wall(Vector2D pos, uint width, uint height, Texture* texture, Vector2D colVector) :
		pos(pos), width(width), height(height), texture(texture), colVector(colVector) {}

	// renderizado de la pared
	void render() const;

	// colisiones de la pared, en este caso, siempre serán con la bola
	bool collides(SDL_Rect rectBall, Vector2D& colVector);
};