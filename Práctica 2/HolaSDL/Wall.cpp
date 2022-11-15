#include "Wall.h"

// Métodos privados

SDL_Rect Wall::getDestRect() const {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = width;
	destRect.h = height;
	return destRect;
}

// Métodos públicos

void Wall::render() const {
	texture->render(getDestRect());
}

bool Wall::collides(SDL_Rect rectBall, Vector2D& colVector) {
	colVector = this->colVector;
	// determina si dos rectángulos han chocado
	// otra forma es hacer los cálculos
	return SDL_HasIntersection(&rectBall, &getDestRect());
}