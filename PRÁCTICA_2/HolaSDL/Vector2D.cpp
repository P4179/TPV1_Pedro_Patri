#include "Vector2D.h"

// Métodos públicos
double Vector2D::getX() const {
	return x;
}
double Vector2D::getY() const {
	return y;
}

Vector2D Vector2D::operator+(const Vector2D& v) const {
	return Vector2D((this->x + v.x), (this->y + v.y));
}

Vector2D Vector2D::operator-(const Vector2D& v) const {
	return Vector2D((this->x - v.x), (this->y - v.y));
}

double Vector2D::operator*(const Vector2D& v) const {
	return this->x * v.x + this->y * v.y;
}

Vector2D Vector2D::operator*(double escalar) const {
	return Vector2D(escalar * this->x, escalar * this->y);
}

void Vector2D::normalize() {
	// el módulo de un vector es la raíz cuadrada de la suma de los cuadrados de las componentes
	double modulo = sqrt(pow(x, 2) + pow(y, 2));
	x /= modulo;
	y /= modulo;
}