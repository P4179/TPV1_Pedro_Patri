#include "Wall.h"

// Métodos públicos
bool Wall::collides(SDL_Rect rectBall, Vector2D& colVector) {
	colVector = this->colVector;
	// determina si dos rectángulos han chocado
	// otra forma es hacer los cálculos
	return SDL_HasIntersection(&rectBall, &getRect());
}