#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include "Texture.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Ball.h" 
#include "Lifes.h"
#include "Timer.h"
#include "End.h"

using namespace std;

using uint = unsigned int;

// constantes
const uint NUM_TEXTURES = 8;
const uint NUM_WALLS = 3;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 5;
const uint WALL_THICKNESS = 15;	// grosor de las paredes
const uint PADDLE_WIDTH = 125;
const uint PADDLE_HEIGHT = 15;
const uint BALL_TAM = 20;
const uint NUM_LEVELS = 3;
const uint DIGIT_WIDTH = 20;
const uint DIGIT_HEIGHT = 35;
const uint SCREEN_WAIT = 1000;

// enumerado para acceder a las posiciones de un array más fácilmente, 
// de modo que no hace falta recordar que componente está asociada con que gameObject
enum TextureName { _Ball, _Brick, _Digits, _Gameover, _Paddle, _Side, _Topside, _Youwin };

// información de la textura
struct TextureDescription {
	string filename;
	uint hFrames, vFrames;
};

template <class T>
// array sobredimensionado
struct arSob {
	T* datos = nullptr;
	uint cont = 0;	// número de elementos que tiene
	uint tam = 0;	// tamaño del array
	// constructor
	arSob(uint tam) {
		this->tam = tam;
		datos = new T[tam];
	}
	// destructor
	// se invoca automáticamente cuando la estructura sale del ámbito donde se ha creado
	~arSob() {
		delete[] datos;
	}
};

// inicialización homogénea
const TextureDescription TEXT_DESC[NUM_TEXTURES]{
	{"../images/ball2.png", 1, 1},
	{"../images/bricks2.png", 2, 3},
	{"../images/digits2.jpeg", 3, 4},
	{"../images/gameover1.png", 1, 1},
	{"../images/paddle2.png", 1, 1},
	{"../images/side2.png", 1, 1},
	{"../images/topside.png", 1, 1},
	{"../images/youwin.png", 1, 1}
};

const string LEVELS[NUM_LEVELS]{
	"../Maps/level01.dat", "../Maps/level02.dat", "../Maps/level03.dat"
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	// booleanos de control de juego
	bool exit = false, gameover = false, win = false;
	// texturas
	Texture* textures[NUM_TEXTURES];	// array estático de punteros a Texture
	// objetos de juego
	Wall* walls[NUM_WALLS];	// array estático de punteros a Wall
	BlocksMap* blocksMap = nullptr;
	Paddle* paddle = nullptr;
	Ball* ball = nullptr;
	uint currentLevel = 0;
	Lifes* lifes = nullptr;
	Timer* timer = nullptr;
	End* winScreen = nullptr;
	End* gameoverScreen = nullptr;


	// renderizado del juego, que delega el renderizado a cada uno de los objetos de juego
	// Es decir, cada objeto llama a su propio método render
	void render() const;

	// actualiza el juego, por ejemplo, el movimiento de objetos
	// Se delega el update a cada uno de los objetos de juego
	void update();

	// gestiona los eventos
	void handleEvents();

	// crea los objetos de juego: plataforma, bola y mapa
	void createGameObjects();

	// destruye los objetos de juego
	// sirve para destruir los objetos que ya había antes de cargar un nuevo nivel
	void destroyGameObjects();

	// nuevo nivel, es decir, destruye los objetos de juego anteriores y crea los nuevos
	void newLevel();

	// finaliza el juego si no quedan vidas o restablece el nivel si se ha perdido, pero todavía quedan vidas
	void restartLevel();

	// carga el siguiente nivel
	// si se ha llegado al último se guarda el tiempo en un archivo con los 10 mejores tiempos
	// y se finaliza el juego
	void nextLevel();

	// ordenar de menor a mayor los 10 mejores tiempos
	// se utiliza el método de mergeSort
	void mergeMin(arSob<double>& datos, int ini, int mid, int fin) const;
	void mergeSort(arSob<double>& datos, int ini, int fin) const;
	void sortMin(arSob<double>& datos) const;

	// selecciona el número con el tiempo entre toda la línea
	double numTime(ifstream& in) const;

	// lee los mejores tiempos del archivo y los guarda en un array sobredimensionado
	void readTimes(const string& filename, arSob<double>& times) const;

	// guarda los tiempos en un archivo
	void saveTimes(const string& filename, double newTime) const;

	// guardar partida, delega a cada uno de los objetos que deben ser guardados
	void saveGame(string filename) const;


public:
	// constructora de game, inicializa SDL y los gameObjects
	Game();

	// destructora de game, cierra SDL y destruye los punteros a gameObjects
	~Game();

	// bucle de juego
	void run();

	// maneja las colisiones de la pelota con el entorno, como con la plataforma, las paredes, los bloques y la deadline
	// la clase Game es quien gestiona las colisiones de la bola porque tiene información de los demás objetos
	bool collides(const SDL_Rect& rectBall, Vector2D& colVector, bool& isPaddle);
};