#pragma once
#include "checkML.h"
#include "Block.h"
#include "ArkanoidObject.h"
#include <fstream>
#include "FileNotFoundError.h"
#include "FileFormatError.h"

using uint = unsigned int;

class BlocksMap : public ArkanoidObject {
private:
	// matriz dinámica de punteros
	Block*** map = nullptr;
	int filas = 0;
	int cols = 0;
	// tamaño en píxeles de cada celda del mapa
	uint widthBlock = 0;
	uint heightBlock = 0;
	int numBlocks = 0;

	// se carga de un fichero de texto el mapa de bloques
	void cargarFichero(string filename);

	// cargar mapa
	void loadMap(ifstream& in);

	void libera();

public:
	// constructor
	BlocksMap(string filename, Vector2D pos, uint widthMap, uint heightMap, Texture* texture);

	// destructora
	~BlocksMap();

	// rendererizado del mapa de bloques, se delega a cada uno de los bloques
	virtual void render() const;

	// consultar el número de bloques
	int nBlocks() const;

	// se destruye el bloque con el que ha colisionado la bola
	void destroyBlock(Block*& block);

	// determina el bloque de colisión con la pelota
	// determina el vector de colisión de la pelota con el bloque, en caso de producirse colisión
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector);

	// guardar el mapa
	virtual void saveFromFile(ofstream& out) const;

	// cargar mapa
	virtual void loadFromFile(ifstream& in);

	// redefinido para que deje de ser una clase abstracta
	virtual void update() {}
	virtual void handleEvents(const SDL_Event& event) {}
};