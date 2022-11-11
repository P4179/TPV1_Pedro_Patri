#include "Lifes.h"

// Métodos privados 
// 
// a partir del número de vidas encontrar el frame de la textura deseado
void Lifes::posFrame(int digitLife, uint& rowFrame, uint& colFrame) const {
	switch (digitLife) {
	case 0:
		rowFrame = 0;
		colFrame = 0;
		break;
	case 1:
		rowFrame = 0;
		colFrame = 1;
		break;
	case 2:
		rowFrame = 0;
		colFrame = 2;
		break;
	case 3:
		rowFrame = 0;
		colFrame = 3;
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
	case 7:
		rowFrame = 1;
		colFrame = 3;
		break;
	case 8:
		rowFrame = 2;
		colFrame = 0;
		break;
	case 9:
		rowFrame = 2;
		colFrame = 1;
		break;
	}
}

void Lifes::render() const {
	int aux = numLifes;
	int digit;
	int offset = 0;
	do {
		digit = aux % 10;
		aux = aux / 10;
		uint rowFrame = 0, colFrame = 0;
		posFrame(digit, rowFrame, colFrame);

		SDL_Rect destRect;
		destRect.x = pos.getX() - width * offset;
		destRect.y = pos.getY();
		destRect.w = width;
		destRect.h = height;
		texture->renderFrame(destRect, rowFrame, colFrame);
		++offset;
	} while (aux > 0);
}

void Lifes::update() {
	if (gameover) {
		--numLifes;
	}
}

int Lifes::getNumLifes() const {
	return numLifes;
}

void Lifes::setGameover(bool gameover) {
	this->gameover = gameover;
}

void Lifes::saveGame(ofstream& out) const {
	out << numLifes;
}