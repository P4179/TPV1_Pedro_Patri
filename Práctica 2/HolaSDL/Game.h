#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Texture.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Ball.h" 
#include "Lifes.h"
#include "Timer.h"
#include "Win.h"
#include "GameOver.h"
#include "TopTimes.h"
#include "Button.h"
#include "Play.h"
#include "Load.h"
#include "RewardPassLv.h"
#include "RewardAddLife.h"
#include "RewardChangePlatform.h"
#include "SDLError.h"
#include "FileNotFoundError.h"

using namespace std;

using uint = unsigned int;

// constantes
const uint NUM_TEXTURES = 11;
const uint NUM_LEVELS = 3;

enum RewardType { PassLv, AddLife, BigPlatform, SmallPlatform };

enum Config{Win_Width, Win_Height, Frame_Rate, Wall_thickness, Paddle_width, Paddle_height, Ball_tam, 
	Digit_width, Digith_height, Screen_wait, Button_width, Button_height, Button_offset, Probability,
	Reward_width, Reward_height};

// enumerado para acceder a las posiciones de un array más fácilmente, 
// de modo que no hace falta recordar que componente está asociada con que gameObject
enum TextureName { _Ball, _Brick, _Digits, _Gameover, _Paddle, _Side, _Topside, _Youwin, _Play, _Load, _Rewards };

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
	{"../images/youwin.png", 1, 1},
	{"../images/play.png", 1, 1},
	{"../images/load.png", 1, 1},
	{"../images/rewards.png", 10, 8}
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	// booleanos de control de juego
	bool exit = false, gameover = false, win = false;
	bool menu = true;
	uint currentLevel = 1;
	// texturas
	Texture* textures[NUM_TEXTURES];	// array estático de punteros a Texture
	// lista con los objetos estáticos de juego
	list<ArkanoidObject*> gameObjects;
	// lista con los botones, que forman el menú
	list<Button*> buttons;
	// lista con los objetos de juego dinámicos
	list<MovingObject*> movingObjects;
	vector<uint> config;

	// renderizado del juego, que delega el renderizado a cada uno de los objetos de juego
	// Es decir, cada objeto llama a su propio método render
	void render() const;

	// actualiza el juego, por ejemplo, el movimiento de objetos
	// Se delega el update a cada uno de los objetos de juego
	void update();

	// gestiona los eventos
	void handleEvents();

	// nuevo nivel, es decir, destruye los objetos de juego anteriores y crea los nuevos
	void newLevel();

	// finaliza el juego si no quedan vidas o restablece el nivel si se ha perdido, pero todavía quedan vidas
	void restartLevel();

	// carga el siguiente nivel
	// si se ha llegado al último se guarda el tiempo en un archivo con los 10 mejores tiempos
	// y se finaliza el juego
	void nextLevel();

	// guardar partida, delega a cada uno de los objetos que deben ser guardados
	void saveGame() const;

	// almacena en un vector los datos de la configuración del juego
	void loadConfig(const string& filename);

	// se destruyen los objetos dinámicos que han sido marcados para destruir
	void destroyMovingObjects();

	RewardType stringToRewardType(string s);

	void createRewards(RewardType r, Vector2D pos = Vector2D(0, 0));

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

	bool collidesRewards(const SDL_Rect& rect, bool& collidesPaddle);

	bool getGameOver() const { return gameover; }

	bool getWin() const { return win; }

	uint getPaddleWidth() const { return config[Paddle_width]; }

	void setWin(bool win) { this->win = win; }

	// necesario que sea público para ambos botones
	void setMenu(bool menu) { this->menu = menu; }

	// necesario que sea público para el botón de load
	// cargar partida, delega a cada uno de los objetos que deben ser guardados
	void loadGame();

	// un movingObject llama a este método para notificarle al Game que deber ser destruido
	// se le marca como que debe destruirse haciendo que apunte a null
	void destroyMe(MovingObject* m);
};