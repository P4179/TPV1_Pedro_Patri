#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Block {
private:
	// posición de cada bloque dentro del mapa de bloques
	Vector2D pos;
	uint width = 0;	// no se utiliza
	uint height = 0;	// no se utiliza
	// saber el frame de la textura
	uint color = 0;	
	// posición del bloque en el mapa de bloques
	int rowMap = 0;	// no se utiliza
	int colMap = 0;	// no se utiliza
	Texture* texture = nullptr;

	// a partir del color del bloque encontrar la posición del frame
	void posFrame(uint color, uint& rowFrame, uint& colFrame) const;

	// devolver el rectángulo destino
	SDL_Rect getDestRect() const;

	// determinar el vector de colisión de la bola con el bloque
	Vector2D detColVector(const SDL_Rect rectBall, const SDL_Rect rectSelf);

public:
	// constructor
	Block(Vector2D pos, uint width, uint height, int color, int rowMap, int colMap, Texture* texture) :
		pos(pos), width(width), height(height), color(color), rowMap(rowMap), colMap(colMap), texture(texture) {}

	// renderizado
	void render() const;

	// colisión de un bloque, dependiendo de en que lado colisione el vector de colisión será uno u otro
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// getter del color
	uint getColor();
};
