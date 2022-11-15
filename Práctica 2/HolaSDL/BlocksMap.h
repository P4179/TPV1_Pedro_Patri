#pragma once
#include "checkML.h"
#include "Block.h"
#include "Texture.h"
#include <fstream>

using uint = unsigned int;

class BlocksMap {
private:
	// posici�n del mapa de bloques
	Vector2D pos;
	// matriz din�mica de punteros
	Block*** map = nullptr;
	int filas = 0;
	int cols = 0;
	// tama�o en p�xeles del mapa
	uint widthMap = 0;
	uint heightMap = 0;
	// tama�o en p�xeles de cada celda del mapa
	uint widthBlock = 0;
	uint heightBlock = 0;
	Texture* texture = nullptr;
	int numBlocks = 0;

	// se carga de un fichero de texto el mapa de bloques
	void cargarFichero(string filename);

public:
	// constructor
	BlocksMap(string filename, Vector2D pos, uint widthMap, uint heightMap, Texture* texture);

	// destructora
	~BlocksMap();

	// rendererizado del mapa de bloques, se delega a cada uno de los bloques
	void render() const;

	// consultar el n�mero de bloques
	int nBlocks() const;

	// se destruye el bloque con el que ha colisionado la bola
	void destroyBlock(Block*& block);

	// determina el bloque de colisi�n con la pelota
	// determina el vector de colisi�n de la pelota con el bloque, en caso de producirse colisi�n
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// guardar el mapa
	void saveGame(ofstream& out, const string& filename) const;
};