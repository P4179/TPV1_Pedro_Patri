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

public:
	Wall();	// se necesita un constructor predeterminado para poder crear arrays
	Wall(Vector2D pos, uint width, uint height, Texture* texture, Vector2D colVector) :
		pos(pos), width(width), height(height), texture(texture), colVector(colVector) {}

	void render() {
		texture->render(getDestRect());
	}

	bool collides(SDL_Rect ballRect, Vector2D& colVector) {
		colVector = this->colVector;
		// determina si dos rectángulos han chocado
		// otra forma es hacer los cálculos
		return SDL_HasIntersection(&ballRect, &getDestRect());
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