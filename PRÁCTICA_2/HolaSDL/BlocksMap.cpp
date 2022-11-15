#include "BlocksMap.h"

// Métodos privados

void BlocksMap::cargarFichero(string filename) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		throw string("Error leyendo el mapa");
	}
	else {
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
					map[i][j] = new Block(Vector2D(pos.getX() + widthBlock * j, pos.getY() + heightBlock * i), widthBlock, heightBlock, color, i, j, texture);
					++numBlocks;
				}
			}
		}
		in.close();
	}
}

// Métodos públicos

BlocksMap::BlocksMap(string filename, Vector2D pos, uint widthMap, uint heightMap, Texture* texture) {
	this->pos = pos;
	this->widthMap = widthMap;
	this->heightMap = heightMap;
	this->texture = texture;
	cargarFichero(filename);
}

BlocksMap::~BlocksMap() {
	// se destruyen los punteros a los bloques
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] != nullptr) {
				delete map[i][j];
			}
		}
	}
	// se destruyen las columnas
	for (int i = 0; i < filas; ++i) {
		delete[] map[i];
	}
	// se destruye el inicial que almacenaba las columnas
	delete[] map;
}

void BlocksMap::render() const {
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] != nullptr) {
				map[i][j]->render();
			}
		}
	}
}

int BlocksMap::nBlocks() const {
	return numBlocks;
}

void BlocksMap::destroyBlock(Block*& block) {
	delete block;
	block = nullptr;
	--numBlocks;
}

bool BlocksMap::collides(const SDL_Rect& rectBall, Vector2D& colVector) {
	bool enc = false;
	int i = 0;
	while (i < filas && !enc) {
		int j = 0;
		while (j < cols && !enc) {
			if (map[i][j] != nullptr) {
				enc = map[i][j]->collides(rectBall, colVector);
				if (enc) {
					destroyBlock(map[i][j]);
				}
			}
			++j;
		}
		++i;
	}
	return enc;
}

void BlocksMap::saveGame(ofstream& out, const string& filename) const {
	out << filename;

	// se guarda el mapa en otro archivo distinto
	ofstream outMap(filename);
	outMap << filas << " " << cols << endl;
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] == nullptr) {
				outMap << 0;
			}
			else {
				outMap << map[i][j]->getColor();
			}
			outMap << " ";
		}
		outMap << endl;
	}
	outMap.close();
}