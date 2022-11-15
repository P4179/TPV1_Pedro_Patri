#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include <fstream>

using uint = unsigned int;

class Lifes {
private:
	int numLifes = 0;
	// es necesario conocer cuando se ha perdido para poder restar una vida
	bool gameover = false;
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Texture* texture = nullptr;

	// a partir del n�mero de vidas se encuentran los frames de la textura deseados
	void posFrame(int digitLife, uint& rowFrame, uint& colFrame) const;

public:
	Lifes(int numLifes, Vector2D pos, uint width, uint height, Texture* texture) :
		numLifes(numLifes), pos(pos), width(width), height(height), texture(texture) {}

	// renderizado del n�mero de vidas
	void render() const;

	// se actualiza el n�mero de vidas si se ha perdido un nivel
	void update();

	// getter del n�mero de vidas
	int getNumLifes() const;

	// setter del gameover
	void setGameover(bool gameover);

	// guardar vidas del jugador
	void saveGame(ofstream& out) const;
};