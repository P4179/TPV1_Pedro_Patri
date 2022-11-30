#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"

class Game;

// clase que sirve para mostrar las pantallas de Gameover y Win
class Win : public ArkanoidObject {
private:
	Game* game;
public:
	Win(Vector2D pos, uint width, uint height, Texture* texture, Game* game) :
		ArkanoidObject(pos, width, height, texture), game(game) {}

	virtual void render();

	// redefinido para que deje de ser una clase abstracta
	virtual void update() {}
	virtual void handleEvents(const SDL_Event& event) {}
	virtual void loadFromFile(ifstream& in) {}
	virtual void saveFromFile(ofstream& out) const {}
};