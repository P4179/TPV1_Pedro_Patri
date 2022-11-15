#include "Game.h"

// Métodos privados

void Game::render() const {
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

	// render de las vidas del jugador
	lifes->render();

	// render del contador
	timer->render();

	if (gameover) {
		gameoverScreen->render();
	}

	if (win) {
		winScreen->render();
	}

	SDL_RenderPresent(renderer);

	if (gameover || win) {
		SDL_Delay(SCREEN_WAIT);
	}
}

void Game::update() {
	// se actualiza la bola
	ball->update();
	// se actualiza el paddle
	paddle->update();
	// se actualizan las vidas del jugador
	lifes->update();
	// se actualiza el contador
	timer->update();
}

void Game::handleEvents() {
	SDL_Event event;
	// cola de eventos
	while (SDL_PollEvent(&event) && !exit && !gameover && !win) {
		// cerrar ventana
		if (event.type == SDL_QUIT) {
			exit = true;
		}
		// cuando se pulsa 'G' se guarda la partida
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_g) {
				saveGame("../SavedGame/save.txt");
				cout << "Se ha guardado la partida" << endl;
			}
		}
		paddle->handleEvents(event);
	}
}

void Game::newLevel() {
	// se destruye el mapa de bloque antiguo
	delete blocksMap;

	// se recolocan la plataforma y la bola
	paddle->recolocate(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), Vector2D(0, 0));
	ball->recolocate(Vector2D(WIN_WIDTH / 2 - BALL_TAM / 2, WIN_HEIGHT - 150), Vector2D(0, 1));
	// se crea el nuevo mapa de bloques
	blocksMap = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]);
}

void Game::restartLevel() {
	if (lifes->getNumLifes() < 0) {
		saveTimes("../TopTimes/times.txt", timer->getTime());
		exit = true;
	}
	else {
		gameover = false;
		lifes->setGameover(gameover);
		newLevel();
	}
}

void Game::nextLevel() {
	++currentLevel;
	if (currentLevel >= NUM_LEVELS) {
		exit = true;
	}
	else {
		win = false;
		newLevel();
	}
}

void Game::mergeMin(arSob<double>& d, int ini, int mitad, int fin) const {
	// se crea una estructura auxiliar donde se guardan los valores del intervalo
	arSob<double> aux = arSob<double>(fin - ini);

	int i = ini;
	int j = mitad;
	int k = 0;  // índice que apunta al primer hueco libre en la estructura auxiliar
	// se comparan los elementos de la estructura original [ini,mitad) con [mitad,fin) para guardar los menores
	while (k < aux.tam && i < mitad && j < fin) {
		if (d.datos[i] < d.datos[j]) {
			aux.datos[k] = d.datos[i];
			i++;
		}
		else {
			aux.datos[k] = d.datos[j];
			j++;
		}
		k++;
	}

	// se guardan los elementos restantes del intervalo [ini,mitad)
	for (i; i < mitad; i++) {
		aux.datos[k] = d.datos[i];
		k++;
	}

	// se guardan los elementos restantes del intervalo [mitad, fin)
	for (j; j < fin; j++) {
		aux.datos[k] = d.datos[j];
		k++;
	}

	// se copian los elementos de la estructura auxiliar a la original
	for (int i = 0; i < aux.tam; i++) {
		d.datos[ini + i] = aux.datos[i];
	}
}

void Game::mergeSort(arSob<double>& d, int ini, int fin) const {
	int n = fin - ini;
	if (n <= 1) {
		return;
	}
	else {
		int mitad = (ini + fin) / 2;
		mergeSort(d, ini, mitad);
		mergeSort(d, mitad, fin);
		mergeMin(d, ini, mitad, fin);
	}
}

void Game::sortMin(arSob<double>& d) const {
	mergeSort(d, 0, d.cont);
}

double Game::numTime(ifstream& in) const {
	double numTime;
	string aux;
	in >> aux >> aux >> numTime;
	return numTime;
}

void Game::readTimes(const string& filename, arSob<double>& times) const {
	ifstream in(filename);
	if (!in.is_open()) {
		throw string("Error leyendo el archivo con los mejores tiempos");
	}
	else {
		string line;
		getline(in, line);
		while (!in.eof()) {
			times.datos[times.cont] = numTime(in);
			++times.cont;
		}
		in.close();
	}
}

void Game::saveTimes(const string& filename, double newTime) const {
	try {
		arSob<double> times = arSob<double>(10);
		readTimes(filename, times);
		ofstream out(filename);
		out << "TOP 10 TIMES" << endl;
		if (times.cont < times.tam) {
			times.datos[times.cont] = newTime;
			++times.cont;
		}
		else {
			if (newTime < times.datos[times.cont - 1]) {
				times.datos[times.cont - 1] = newTime;
			}
		}

		sortMin(times);

		for (int i = 0; i < times.cont; ++i) {
			out << "Time " << (i + 1) << ": " << times.datos[i];
			if (i < times.cont - 1) {
				out << endl;
			}
		}
		out.close();
	}
	catch (string e) {
		ofstream out(filename);
		out << "TOP 10 TIMES" << endl;
		out << "Time 1: " << newTime << endl;
		out.close();
	}
}

void Game::saveGame(string filename) const {
	ofstream out(filename);
	out << currentLevel << endl;
	timer->saveGame(out);
	out << endl;
	lifes->saveGame(out);
	out << endl;
	ball->saveGame(out);
	out << endl;
	paddle->saveGame(out);
	out << endl;
	blocksMap->saveGame(out, "../SavedGame/map.txt");
	out.close();
}

// Métodos públicos

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw string("Error cargando SDL");
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// crear texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, TEXT_DESC[i].filename, TEXT_DESC[i].hFrames, TEXT_DESC[i].vFrames);
	}

	// paredes
	// pared izquierda
	walls[0] = new Wall(Vector2D(0, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(1, 0));
	// pared de arriba
	walls[1] = new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_THICKNESS, textures[_Topside], Vector2D(0, 1));
	// pared derecha
	walls[2] = new Wall(Vector2D(WIN_WIDTH - WALL_THICKNESS, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(-1, 0));

	// vidas del jugador
	lifes = new Lifes(10, Vector2D(WIN_WIDTH - DIGIT_WIDTH, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits]);

	// contador
	timer = new Timer(0, Vector2D(0, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits]);

	winScreen = new End(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Youwin]);

	gameoverScreen = new End(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Gameover]);

	// plataforma
	paddle = new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), textures[_Paddle], WALL_THICKNESS, WIN_WIDTH - WALL_THICKNESS);

	// ball
	ball = new Ball(Vector2D(WIN_WIDTH / 2 - BALL_TAM / 2, WIN_HEIGHT - 150), BALL_TAM, BALL_TAM, Vector2D(0, 1), textures[_Ball], this);

	// mapa de bloques
	blocksMap = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]);
}

Game::~Game() {
	// se destruyen las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
	}
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

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	// bucle con los niveles
	while (!exit) {
		while (!exit && !gameover && !win) { // Bucle del juego
			handleEvents();
			frameTime = SDL_GetTicks() - startTime; // Tiempo desde última actualización
			// no se para el programa en ningún momento, solo se actualiza cuando han pasado los frames necesarios
			if (frameTime >= FRAME_RATE) {
				update(); // Actualiza el estado de todos los objetos del juego
				startTime = SDL_GetTicks();
			}
			render(); // Renderiza todos los objetos del juego
		}

		if (gameover) {
			restartLevel();
		}
		else if (win) {
			nextLevel();
		}
	}
}

bool Game::collides(const SDL_Rect& rectBall, Vector2D& colVector, bool& isPaddle) {
	isPaddle = false;

	// Ball - Walls
	// dos opciones: método en Wall que determinar si la bola ha chocado con ella o se pasan los parámetros
	for (int i = 0; i < NUM_WALLS; ++i) {
		if (walls[i]->collides(rectBall, colVector)) {
			return true;
		}
	}

	// Ball - Paddle
	if (paddle->collides(rectBall, colVector)) {
		isPaddle = true;
		return true;
	}

	// Ball - Blocks
	if (blocksMap->collides(rectBall, colVector)) {
		// si no quedan bloques se ha ganado
		if (blocksMap->nBlocks() == 0) {
			win = true;
		}
		return true;
	}

	// Ball - DeadLine
	if (rectBall.y >= WIN_HEIGHT) {
		gameover = true;
		lifes->setGameover(gameover);
	}
	return false;
}