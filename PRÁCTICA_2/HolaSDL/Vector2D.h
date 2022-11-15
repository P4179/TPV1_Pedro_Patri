#pragma once
#include "checkML.h"
#include <cmath>

class Vector2D {
private:
	double x = 0;
	double y = 0;

public:
	// al crear un nuevo constructor reemplaza al predeterminado
	Vector2D() {}
	// Por lo tanto, si se necesita el predeterminado hay que volver a crearlo
	Vector2D(double x, double y) :x(x), y(y) {}

	// consultar componentes x e y
	double getX() const;
	double getY() const;

	// suma
	Vector2D operator+(const Vector2D& v) const;

	// resta
	Vector2D operator-(const Vector2D& v) const;

	// producto escalar de dos vectores
	double operator*(const Vector2D& v) const;

	// producto vector por un escalar
	Vector2D operator*(double escalar) const;

	// normalizar el vector
	void normalize();
};