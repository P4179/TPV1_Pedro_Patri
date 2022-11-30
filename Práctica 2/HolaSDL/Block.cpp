#include "Block.h"

// Métodos privados

void Block::posFrame(uint color, uint& rowFrame, uint& colFrame) const {
	switch (color) {
	case 1:
		rowFrame = 0;
		colFrame = 0;
		break;
	case 2:
		rowFrame = 0;
		colFrame = 1;
		break;
	case 3:
		rowFrame = 0;
		colFrame = 2;
		break;
	case 4:
		rowFrame = 1;
		colFrame = 0;
		break;
	case 5:
		rowFrame = 1;
		colFrame = 1;
		break;
	case 6:
		rowFrame = 1;
		colFrame = 2;
		break;
	}
}

Vector2D Block::detColVector(const SDL_Rect rectBall, const SDL_Rect rectSelf) {
	Vector2D colVector;
	// esquina superior izquierda del bloque
	if (rectBall.x + rectBall.w == rectSelf.x && rectBall.y + rectBall.h == rectSelf.y) {
		colVector = Vector2D(-1, -1);
	}
	// esquina superior derecha del bloque
	else if (rectBall.x == rectSelf.x + rectSelf.w && rectBall.y + rectBall.h == rectSelf.y) {
		colVector = Vector2D(1, -1);
	}
	// esquina inferior izquierda del bloque
	else if (rectBall.x + rectBall.w == rectSelf.x && rectBall.y == rectSelf.y + rectSelf.h) {
		colVector = Vector2D(-1, 1);
	}
	// esquina inferior derecha del bloque
	else if (rectBall.x == rectSelf.x + rectSelf.w && rectBall.y == rectSelf.y + rectSelf.h) {
		colVector = Vector2D(1, 1);
	}
	// lados izquierdo y derecho del bloque
	else if (rectBall.y + rectBall.h / 2 >= rectSelf.y && rectBall.y + rectBall.h / 2 <= rectSelf.y + rectSelf.h) {
		// no importa el sentido del vector, por lo tanto, para el lado izquierdo y el derecho 
		// se puede utilizar el mismo porque son el mismo vector con sentidos opuestos
		// De modo que se pueden agrupar en un solo caso
		colVector = Vector2D(1, 0);
	}
	// lado superior
	else if (rectBall.y + rectBall.h / 2 < rectSelf.y) {
		colVector = Vector2D(0, -1);
	}
	// lado inferior
	else if (rectBall.y + rectBall.h / 2 > rectSelf.y + rectSelf.h) {
		colVector = Vector2D(0, 1);
	}

	return colVector;
}

// Método público

void Block::render() const {
	uint rowFrame = 0, colFrame = 0;
	posFrame(color, rowFrame, colFrame);

	texture->renderFrame(getRect(), rowFrame, colFrame);
}

bool Block::collides(const SDL_Rect& rectBall, Vector2D& colVector) {
	SDL_Rect rectBlock = getRect();
	colVector = detColVector(rectBall, rectBlock);
	return SDL_HasIntersection(&rectBall, &rectBlock);
}

uint Block::getColor() {
	return color;
}