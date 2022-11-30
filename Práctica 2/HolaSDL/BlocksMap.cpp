#include "BlocksMap.h"

// Métodos privados

void BlocksMap::cargarFichero(string filename) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		throw FileNotFoundError("cargarFichero", filename);
	}
	else {
		loadMap(in);
		in.close();
	}
}

void BlocksMap::loadMap(ifstream& in) {
	in >> filas;
	in >> cols;

	// tamaño de mapa incorrecto
	if (filas < 0 || cols < 0) {
		throw FileFormatError("loadMap", filas, cols);
	}

	widthBlock = width / cols;
	heightBlock = height / filas;

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
			// bloque incorrecto
			else if (color < 0 || color > 6) {
				throw FileFormatError("loadMap", color);
			}
			else {
				map[i][j] = new Block(Vector2D(pos.getX() + widthBlock * j, pos.getY() + heightBlock * i), widthBlock, heightBlock, color, i, j, texture);
				++numBlocks;
			}
		}
	}

	// mapa vacío
	if (numBlocks <= 0) {
		throw FileFormatError("loadMap");
	}
}

void BlocksMap::libera() {
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

// Métodos públicos

BlocksMap::BlocksMap(string filename, Vector2D pos, uint widthMap, uint heightMap, Texture* texture) :
	ArkanoidObject(pos, widthMap, heightMap, texture) {
	cargarFichero(filename);
}

BlocksMap::~BlocksMap() {
	libera();
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

void BlocksMap::saveFromFile(ofstream& out) const {
	// se guarda el mapa en otro archivo distinto
	out << filas << " " << cols << endl;
	for (int i = 0; i < filas; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (map[i][j] == nullptr) {
				out << 0;
			}
			else {
				out << map[i][j]->getColor();
			}
			out << " ";
		}
		out << endl;
	}
}

void BlocksMap::loadFromFile(ifstream& in) {
	// se elimina el mapa actual, es decir, se elimina la matriz dinámica de punteros a bloques
	libera();
	// se carga el nuevo mapa, es decir, se crea una nueva matriz dinámica de punteros a bloques
	loadMap(in);
}