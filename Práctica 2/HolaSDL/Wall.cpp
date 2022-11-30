#include "Wall.h"

// M�todos p�blicos
bool Wall::collides(SDL_Rect rectBall, Vector2D& colVector) {
	colVector = this->colVector;
	// determina si dos rect�ngulos han chocado
	// otra forma es hacer los c�lculos
	return SDL_HasIntersection(&rectBall, &getRect());
}