#include "Wall.h"

// M�todos p�blicos
bool Wall::collidesBall(SDL_Rect rectBall, Vector2D& colVector) {
	colVector = this->colVector;
	// determina si dos rect�ngulos han chocado
	// otra forma es hacer los c�lculos
	return collides(rectBall);
}