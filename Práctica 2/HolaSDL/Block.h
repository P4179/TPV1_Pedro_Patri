#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"

using uint = unsigned int;

class Block : public ArkanoidObject {
private:
	// saber el frame de la textura
	uint color = 0;	
	// posición del bloque en el mapa de bloques
	int rowMap = 0;	// no se utiliza
	int colMap = 0;	// no se utiliza

	// a partir del color del bloque encontrar la posición del frame
	void posFrame(uint color, uint& rowFrame, uint& colFrame) const;

	// determinar el vector de colisión de la bola con el bloque
	Vector2D detColVector(const SDL_Rect rectBall, const SDL_Rect rectSelf);

public:
	// constructor
	Block(Vector2D pos, uint width, uint height, int color, int rowMap, int colMap, Texture* texture) :
		ArkanoidObject(pos, width, height, texture), color(color), rowMap(rowMap), colMap(colMap) {}

	// renderizado
	virtual void render() const;

	// colisión de un bloque, dependiendo de en que lado colisione el vector de colisión será uno u otro
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// getter del color
	uint getColor();

	// redefinido para que deje de ser una clase abstracta
	virtual void update() {}
	virtual void handleEvents(const SDL_Event& event) {}
	virtual void loadFromFile(ifstream& in) {}
	virtual void saveFromFile(ofstream& out) const {}
};
