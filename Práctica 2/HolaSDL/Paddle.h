#pragma once
#include "checkML.h"
#include "MovingObject.h"
#include <fstream>

using uint = unsigned int;

class Paddle : public MovingObject {
private:
	uint leftBgBorder = 0;
	uint rightBgBorder = 0;

	// determinar si la plataforma ha chocado con las paredes
	// se calcula por posici�n
	bool borders() const;

public:
	Paddle(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture, uint leftBgBorder, uint rightBgBorder) :
		MovingObject(pos, width, height, texture, dir), leftBgBorder(leftBgBorder), rightBgBorder(rightBgBorder) {}

	// moverse de acuerdo a su direcci�n
	// hay que controlar que la plataforma no se salga del �rea de juego
	void update();

	// tratar los eventos
	// controla el movimiento de la plataforma con los cursores izq y dcho
	void handleEvents(const SDL_Event& event);

	// determinar si la bola ha chocado con la plataforma y el vector de colisi�n que se forma
	bool collides(const SDL_Rect& rectBall, Vector2D& dirBall);
};