#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Block {
private:
	// posici�n de cada bloque dentro del mapa de bloques
	Vector2D pos;
	uint width = 0;	// no se utiliza
	uint height = 0;	// no se utiliza
	// saber el frame de la textura
	uint color = 0;	
	// posici�n del bloque en el mapa de bloques
	int rowMap = 0;	// no se utiliza
	int colMap = 0;	// no se utiliza
	Texture* texture = nullptr;

	// a partir del color del bloque encontrar la posici�n del frame
	void posFrame(uint color, uint& rowFrame, uint& colFrame) const;

	// devolver el rect�ngulo destino
	SDL_Rect getDestRect() const;

	// determinar el vector de colisi�n de la bola con el bloque
	Vector2D detColVector(const SDL_Rect rectBall, const SDL_Rect rectSelf);

public:
	// constructor
	Block(Vector2D pos, uint width, uint height, int color, int rowMap, int colMap, Texture* texture) :
		pos(pos), width(width), height(height), color(color), rowMap(rowMap), colMap(colMap), texture(texture) {}

	// renderizado
	void render() const;

	// colisi�n de un bloque, dependiendo de en que lado colisione el vector de colisi�n ser� uno u otro
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// getter del color
	uint getColor();
};
