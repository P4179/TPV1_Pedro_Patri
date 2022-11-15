#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Block {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	int color = 0;	// saber el frame de la textura
	// posición del bloque en el mapa de bloques
	// no se utilizan
	int rowMap = 0;
	int colMap = 0;
	Texture* texture = nullptr;

	void posFrame(int& rowFrame, int& colFrame) {
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

public:
	// constructor
	Block(Vector2D pos, uint width, uint height, int color, int rowMap, int colMap, Texture* texture) :
		pos(pos), width(width), height(height), color(color), rowMap(rowMap), colMap(colMap), texture(texture) {}

	// dibujarse
	void render() {
		SDL_Rect destRect;
		destRect.x = pos.getX();
		destRect.y = pos.getY();
		destRect.w = width;
		destRect.h = height;

		int rowFrame = 0, colFrame = 0;
		posFrame(rowFrame, colFrame);

		texture->renderFrame(destRect, rowFrame, colFrame);
	}
};
