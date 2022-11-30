#pragma once
#include "ArkanoidObject.h"

class MovingObject : public ArkanoidObject {
protected:
	Vector2D dir;

	MovingObject(Vector2D pos, uint width, uint height, Texture* texture, Vector2D dir)
		: ArkanoidObject(pos, width, height, texture), dir(dir) {}

public:
	virtual void loadFromFile(ifstream& in) {
		double x, y;
		// se carga la pos
		in >> x >> y;
		pos = Vector2D(x, y);

		// se carga la dir
		in >> x >> y;
		dir = Vector2D(x, y);
	}

	virtual void saveFromFile(ofstream& out) const {
		out << pos.getX() << " " << pos.getY() << endl;
		out << dir.getX() << " " << dir.getY();
	}

	// recolocar la bola dándole una posición y una dirección nuevas
	virtual void recolocate(Vector2D pos, Vector2D dir) {
		this->pos = pos;
		this->dir = dir;
	}
};