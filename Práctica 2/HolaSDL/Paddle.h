#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include <fstream>

using uint = unsigned int;

class Paddle {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Vector2D dir;
	Texture* texture = nullptr;
	uint leftBgBorder = 0;
	uint rightBgBorder = 0;

	// determinar si la plataforma ha chocado con las paredes
	// se calcula por posición
	bool borders() const;

	// devolver el rectángulo destino de la plataforma
	SDL_Rect getDestRect() const;

public:
	Paddle(Vector2D pos, uint width, uint height, Vector2D dir, Texture* texture, uint leftBgBorder, uint rightBgBorder) :
		pos(pos), width(width), height(height), dir(dir), texture(texture), leftBgBorder(leftBgBorder), rightBgBorder(rightBgBorder) {}

	// dibujarse
	void render() const;

	// moverse de acuerdo a su dirección
	// hay que controlar que la plataforma no se salga del área de juego
	void update();

	// tratar los eventos
	// controla el movimiento de la plataforma con los cursores izq y dcho
	void handleEvents(const SDL_Event& event);

	// determinar si la bola ha chocado con la plataforma y el vector de colisión que se forma
	bool collides(const SDL_Rect& rectBall, Vector2D& dirBall);

	// guardar pos de la plataforma
	void saveGame(ofstream& out) const;

	void recolocate(Vector2D pos, Vector2D dir) {
		this->pos = pos;
		this->dir = dir;
	}
};