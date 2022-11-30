#include "Ball.h"
#include "Game.h"

// Métodos públicos

void Ball::update() {
	Vector2D colVector;
	bool isPaddle;
	// se comprueba si la bola ha colisionado con algún objeto
	// entonces, se cambia su dirección
	if (game->collides(getRect(), colVector, isPaddle)) {
		colVector.normalize();
		// vector de reflexión
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

