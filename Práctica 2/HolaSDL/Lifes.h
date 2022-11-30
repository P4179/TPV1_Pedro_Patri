#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"
#include <fstream>

using uint = unsigned int;
class Game;

class Lifes : public ArkanoidObject {
private:
	int numLifes = 0;
	Game* game = nullptr;

	// a partir del número de vidas se encuentran los frames de la textura deseados
	void posFrame(int digitLife, uint& rowFrame, uint& colFrame) const;

public:
	Lifes(int numLifes, Vector2D pos, uint width, uint height, Texture* texture, Game* game) :
		numLifes(numLifes), ArkanoidObject(pos, width, height, texture), game(game) {}

	// renderizado del número de vidas
	virtual void render() const;

	// se actualiza el número de vidas si se ha perdido un nivel
	virtual void update();

	// getter del número de vidas
	int getNumLifes() const;

	// guardar vidas del jugador
	virtual void saveFromFile(ofstream& out) const;

	virtual void loadFromFile(ifstream& in);

	// redefinido para que deje de ser una clase abstracta
	virtual void handleEvents(const SDL_Event& event) {}
};