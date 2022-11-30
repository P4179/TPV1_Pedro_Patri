#pragma once

#include "checkML.h"
#include "Button.h"

class Load : public Button {
public:
	Load(Vector2D pos, uint width, uint height, Texture* texture, Game* game) :
		Button(pos, width, height, texture, game) {}

	virtual void update();

	// redefinido para que deje de ser una clase abstracta
	virtual void loadFromFile(ifstream& in) {}
	virtual void saveFromFile(ofstream& out) const {}
};