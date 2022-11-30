#pragma once

#include "checkML.h"
#include<fstream>
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

using namespace std;

using uint = unsigned int;

class ArkanoidObject : public GameObject {
protected:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Texture* texture = nullptr;

	SDL_Rect getRect() const {
		SDL_Rect destRect;
		destRect.x = pos.getX();
		destRect.y = pos.getY();
		destRect.w = width;
		destRect.h = height;
		return destRect;
	}

	// se necesita un constructor predeterminado porque Wall, que es un hijo de ArkanoidObject,
	// tiene un constructor predeterminado
	ArkanoidObject() {}

	ArkanoidObject(Vector2D pos, uint width, uint height, Texture* texture) : 
		pos(pos), width(width), height(height), texture(texture) {}

public:
	virtual void render() const {
		texture->render(getRect());
	}

	virtual void loadFromFile(ifstream& in) = 0;
	virtual void saveFromFile(ofstream& out) const = 0;
};