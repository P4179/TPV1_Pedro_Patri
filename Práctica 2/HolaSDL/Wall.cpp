#include "Wall.h"

// Métodos públicos
bool Wall::collidesBall(SDL_Rect rectBall, Vector2D& colVector) {
	colVector = this->colVector;
	// determina si dos rectángulos han chocado
	// otra forma es hacer los cálculos
	return collides(rectBall);
}