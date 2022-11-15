#pragma once
#include "checkML.h"
#include "Block.h"
#include "Texture.h"
#include <fstream>

using uint = unsigned int;

class BlocksMap {
private:
	// posición del mapa de bloques
	Vector2D pos;
	// matriz dinámica de punteros
	Block*** map = nullptr;
	int filas = 0;
	int cols = 0;
	// tamaño en píxeles del mapa
	uint widthMap = 0;
	uint heightMap = 0;
	// tamaño en píxeles de cada celda del mapa
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

	// consultar el número de bloques
	int nBlocks() const;

	// se destruye el bloque con el que ha colisionado la bola
	void destroyBlock(Block*& block);

	// determina el bloque de colisión con la pelota
	// determina el vector de colisión de la pelota con el bloque, en caso de producirse colisión
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// guardar el mapa
	void saveGame(ofstream& out, const string& filename) const;
};