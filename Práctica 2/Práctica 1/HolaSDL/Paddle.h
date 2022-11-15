#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Paddle {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Vector2D dir;
	Texture* texture = nullptr;

public:
	Paddle(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture) :
		pos(pos), width(width), height(height), dir(dir), texture(texture) {}

	// dibujarse
	void render() {
		SDL_Rect destRect;
		destRect.x = pos.getX();
		destRect.y = pos.getY();
		destRect.w = width;
		destRect.h = height;
		texture->render(destRect);
	}
	// moverse de acuerdo a su direcci�n/velocidad
	// controlar que el Paddle no se salga a trav�s del motor de f�sicas o a trav�s de la posici�n
	// posici�n + ancho paddle + ancho pared < ancho ventana
	void update() {

	}
	// tratar los eventos
	// controla el movimiento de la plataforma con los cursores izq y dcho
	// determina el vector de colisi�n con la pelota
	void handleEventes() {

	}
};