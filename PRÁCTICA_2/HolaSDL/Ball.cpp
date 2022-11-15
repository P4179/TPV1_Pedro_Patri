#include "Ball.h"
#include "Game.h"

// Métodos privados

SDL_Rect Ball::getDestRect() const {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = width;
	destRect.h = height;
	return destRect;
}

// Métodos públicos

void Ball::render() const {
	texture->render(getDestRect());
}

void Ball::update() {
	Vector2D colVector;
	bool isPaddle;
	// se comprueba si la bola ha colisionado con algún objeto
	// entonces, se cambia su dirección
	if (game->collides(getDestRect(), colVector, isPaddle)) {
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

void Ball::saveGame(ofstream& out) const {
	out << pos.getX() << " " << pos.getY() << endl;
	out << dir.getX() << " " << dir.getY();
}