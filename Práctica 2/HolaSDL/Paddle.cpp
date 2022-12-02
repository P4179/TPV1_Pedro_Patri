#include "Paddle.h"

// Métodos privados

bool Paddle::borders() const {
	SDL_Rect destRect = getRect();
	return destRect.x <= leftBgBorder || destRect.x + destRect.w >= rightBgBorder;
}

// Métodos públicos

void Paddle::update() {
	// primero se desplaza la plataforma para comprobar si va a chocar contra los muros o no
	// se hace de esta forma para que cuando esté chocando contra los muros pueda desplazarse al otro lado
	pos = pos + dir * 2;
	// si ha chocado contra los muros se coloca pegada a ellos
	if (borders()) {
		pos = pos - dir * 2;
	}
}

void Paddle::handleEvents(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			dir = Vector2D(-1, 0);
			break;
		case SDLK_RIGHT:
			dir = Vector2D(1, 0);
			break;
		}
	}
	else {
		dir = Vector2D(0, 0);
	}
}

bool Paddle::collidesBall(const SDL_Rect& rectBall, Vector2D& dirBall) {
	SDL_Rect destRect = getRect();

	int midBall = rectBall.x + rectBall.w / 2;
	int midPaddle = destRect.x + destRect.w / 2;
	int ratio = (midBall - midPaddle) / 10;
	dirBall = Vector2D(ratio, -2.5);

	return collides(rectBall);
}