#include "Ball.h"
#include "Game.h"

// M�todos privados

SDL_Rect Ball::getDestRect() const {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = width;
	destRect.h = height;
	return destRect;
}

// M�todos p�blicos

void Ball::render() const {
	texture->render(getDestRect());
}

void Ball::update() {
	Vector2D colVector;
	bool isPaddle;
	// se comprueba si la bola ha colisionado con alg�n objeto
	// entonces, se cambia su direcci�n
	if (game->collides(getDestRect(), colVector, isPaddle)) {
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

void Ball::saveGame(ofstream& out) const {
	out << pos.getX() << " " << pos.getY() << endl;
	out << dir.getX() << " " << dir.getY();
}