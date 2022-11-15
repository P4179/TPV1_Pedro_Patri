#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Ball.h"

using namespace std;

using uint = unsigned int;

// constantes
const uint NUM_TEXTURES = 8;
const uint NUM_WALLS = 3;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 5;
const uint WALL_THICKNESS = 15;
const uint PADDLE_WIDTH = 125;
const uint PADDLE_HEIGHT = 15;
const uint BALL_TAM = 20;

// enumerado para acceder a las posiciones de un array más fácilmente, 
// de modo que no hace falta recordar que componente está asociada con que gameObject
enum TextureName { _Ball, _Brick, _Digits, _Gameover, _Paddle, _Side, _Topside, _Youwin };

// información de la textura
struct TextureDescription {
	string filename;
	uint hFrames, vFrames;
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


	// renderizado del juego, que delega el renderizado a cada uno de los objetos de juego
	// Es decir, cada objeto llama a su propio método render
	void render() const {
		SDL_RenderClear(renderer);

		// render de las paredes
		for (int i = 0; i < NUM_WALLS; ++i) {
			walls[i]->render();
		}
		// render de la plataforma
		paddle->render();
		// render de la pelota
		ball->render();

		// render del blocksMap
		blocksMap->render();

		SDL_RenderPresent(renderer);
	}
	// actualiza el juego, por ejemplo, el movimiento de objetos
	void update() {
		// Ball
		ball->update();
		// Paddle
	}
	// gestiona los eventos
	void handleEvents() {
		SDL_Event event;
		// cola de eventos
		while (SDL_PollEvent(&event) && !exit) {
			// cerrar ventana
			if (event.type == SDL_QUIT) {
				exit = true;
			}
		}
	}

public:
	// constructora de game, inicializa SDL y los gameObjects
	Game() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (window == nullptr || renderer == nullptr) {
			throw new string("Error cargando SDL");
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// crear texturas
		for (int i = 0; i < NUM_TEXTURES; ++i) {
			textures[i] = new Texture(renderer, TEXT_DESC[i].filename, TEXT_DESC[i].hFrames, TEXT_DESC[i].vFrames);
		}
		// crear objetos de juego
		// paredes
		// pared izquierda
		walls[0] = new Wall(Vector2D(0, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(1,0));
		// pared de arriba
		walls[1] = new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_THICKNESS, textures[_Topside], Vector2D(0,1));
		// pared derecha
		walls[2] = new Wall(Vector2D(WIN_WIDTH - WALL_THICKNESS, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(-1,0));

		// plataforma
		paddle = new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), textures[_Paddle]);

		// ball
		// otra forma es definir el tamaño de la pelota relativo al tamaño de los bloques
		ball = new Ball(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT - 150), BALL_TAM, BALL_TAM, Vector2D(1, -1), textures[_Ball], this);

		// mapa de bloques
		blocksMap = new BlocksMap("level03", WIN_WIDTH - 30, WIN_HEIGHT / 2, textures[_Brick]);
	}
	// destructora de game, cierra SDL y destruye los punteros a gameObjects
	~Game() {
		// se destruyen las texturas
		for (int i = 0; i < NUM_TEXTURES; ++i) {
			delete textures[i];
		}
		// se destruyen los objetos de juego
		for (int i = 0; i < NUM_WALLS; ++i) {
			delete walls[i];
		}
		delete blocksMap;
		delete paddle;
		delete ball;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	// bucle de juego
	void run() {
		uint32_t startTime, frameTime;
		startTime = SDL_GetTicks();

		while (!exit) { // Bucle del juego
			handleEvents();
			frameTime = SDL_GetTicks() - startTime; // Tiempo desde última actualización
			// no se para el programa en ningún momento, solo se actualiza cuando han pasado los frames necesarios
			if (frameTime >= FRAME_RATE) {
				update(); // Actualiza el estado de todos los objetos del juego
				startTime = SDL_GetTicks();
			}
			render(); // Renderiza todos los objetos del juego
		}
	}
	// maneja las colisiones de la pelota con el entorno, como con la plataforma, las paredes o los bloques
	// dos opciones: argumento con los parámetros de la pos de la bola o rectángulo destino
	bool collides(SDL_Rect rectBall, Vector2D& colVector) {

		// Ball - Walls
		// dos opciones: método en Wall que determinar si la bola ha chocado con ella o se pasan los parámetros
		for (int i = 0; i < NUM_WALLS; ++i) {
			if (walls[i]->collides(rectBall, colVector)) {
				return true;
			}
		}

		// Ball - Paddle

		// Ball - Blocks

		// Ball - DeadLine
		if (rectBall.y + rectBall.h >= WIN_HEIGHT) {
			return true;
		}
		return false;
	}
};