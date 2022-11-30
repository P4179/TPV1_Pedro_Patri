#include "Ball.h"
#include "Game.h"

// M�todos p�blicos

void Ball::update() {
	Vector2D colVector;
	bool isPaddle;
	// se comprueba si la bola ha colisionado con alg�n objeto
	// entonces, se cambia su direcci�n
	if (game->collides(getRect(), colVector, isPaddle)) {
		colVector.normalize();
		// vector de reflexi�n
		if (isPaddle) {
			dir = colVector;
		}
		else {
			dir = dir - (colVector * (2 * (dir * colVector)));
		}
	}
	dir.normalize();
	dir = dir * 1.5;
	pos = pos + dir;
}

