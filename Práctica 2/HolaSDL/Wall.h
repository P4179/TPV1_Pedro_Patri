#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "ArkanoidObject.h"

using uint = unsigned int;

class Wall : public ArkanoidObject {
private:
	// se podría calcular el vector de colisión, pero es mejor definirlo en el constructor
	Vector2D colVector;

public:
	// se necesita un constructor predeterminado para poder crear arrays
	Wall() {}
	Wall(Vector2D pos, uint width, uint height, Texture* texture, Vector2D colVector) :
		ArkanoidObject(pos, width, height, texture), colVector(colVector) {}

	// redefinido para que deje de ser una clase abstracta
	virtual void update() {}
	virtual void handleEvents(const SDL_Event& event) {}
	virtual void loadFromFile(ifstream& in) {}
	virtual void saveFromFile(ofstream& out) const {}

	// colisiones de la pared, en este caso, siempre serán con la bola
	bool collides(SDL_Rect rectBall, Vector2D& colVector);
};