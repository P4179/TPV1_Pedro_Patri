#pragma once
#include "checkML.h"
#include "Block.h"
#include <fstream>
#include "Texture.h"

using uint = unsigned int;

class BlocksMap {
private:
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
	Texture* texture = nullptr;	// NO ESTABA EN LA PLANTILLA
	int numBlocks = 0;	// NO ESTABA EN LA PLANTILLA

	void cargarFichero(string filename) {
		ifstream in;
		in.open("../Maps/" + filename + ".dat");
		in >> filas;
		in >> cols;

		widthBlock = widthMap / cols;
		heightBlock = heightMap / filas;

		// matriz dinámica de punteros
		// se crean las filas
		map = new Block * *[filas];
		// se crean las columnas
		for (int i = 0; i < filas; ++i) {
			map[i] = new Block * [cols];
		}
		// se crean los punteros a los bloques
		int color = 0;
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < cols; ++j) {
				in >> color;
				if (color == 0) {
					map[i][j] = nullptr;
				}
				else {
					map[i][j] = new Block(Vector2D(15 + widthBlock * j, 15 + heightBlock * i), widthBlock, heightBlock, color, i, j, texture);
					++numBlocks;
				}
			}
		}
		in.close();
	}

public:
	BlocksMap(string filename, uint widthMap, uint heightMap, Texture* texture) {
		this->widthMap = widthMap;
		this->heightMap = heightMap;
		this->texture = texture;
		cargarFichero(filename);
	}

	~BlocksMap() {
		// se destruyen los punteros a los bloques
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < cols; ++j) {
				delete map[i][j];
			}
		}
		// se destruyen las columnas
		for (int i = 0; i < filas; ++i) {
			delete[] map[i];
		}
		// se destruye el inicial que almacenaba las columnas
		delete[] map;
	}

	void render() const {
		for (int i = 0; i < filas; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (map[i][j] != nullptr) {
					map[i][j]->render();
				}
			}
		}
	}

	int NBlocks() const {
		return numBlocks;
	}

	// determina el bloque de colisión con la pelota
	// determina el vector de colisión de la pelota con el bloque, en caso de producirse colisión
	void colision(Block*& blockCol, Vector2D& vCol) {

	}
};