#pragma once
#include "checkML.h"

class Vector2D {
private:
	int x = 0;
	int y = 0;

public:
	// al crear un nuevo constructor reemplaza al predeterminado
	Vector2D() {}
	// Por lo tanto, si se necesita el predeterminado hay que volver a crearlo
	Vector2D(int x, int y) :x(x), y(y) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}

	Vector2D operator+(const Vector2D& v) const {
		return Vector2D((this->x + v.x), (this->y + v.y));
	}
};