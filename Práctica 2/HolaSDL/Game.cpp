#include "Game.h"

// Métodos privados

void Game::render() const {
	SDL_RenderClear(renderer);

	if (menu) {
		play->render();
		load->render();
	}
	else {
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->render();
		}
		/*
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
		// render de la pantalla de derrota, solo se muestra si se ha perdido
		gameoverScreen->render();
		// render de la pantalla de victoria, solo se muestra si se ha ganado
		winScreen->render();
		*/
	}

	SDL_RenderPresent(renderer);

	if (gameover || win) {
		SDL_Delay(SCREEN_WAIT);
	}
}

void Game::update() {
	if (menu) {
		play->update();
		load->update();
	}
	else {
		if (gameover) {
			restartLevel();
		}
		else if (win) {
			nextLevel();
		}

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update();
		}

		/*
		// se actualiza la bola
		ball->update();
		// se actualiza el paddle
		paddle->update();
		// se actualizan las vidas del jugador
		lifes->update();
		// se actualiza el contador
		timer->update();
		*/
	}
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
				saveGame();
			}
			else if (event.key.keysym.sym == SDLK_s) {
				loadGame();
			}
		}

		/*
		paddle->handleEvents(event);
		play->handleEvents(event);
		load->handleEvents(event);
		*/


		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->handleEvents(event);
		}
	}
}

void Game::newLevel() {
	// se destruye el mapa de bloque antiguo
	delete blocksMap;

	// se recolocan la plataforma y la bola

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		if (typeid(*it) == typeid(BlocksMap)) {
			(*it) = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]);
		}
	}

	/*
	paddle->recolocate(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), Vector2D(0, 0));
	ball->recolocate(Vector2D(WIN_WIDTH / 2 - BALL_TAM / 2, WIN_HEIGHT - 150), Vector2D(0, 1));
	// se crea el nuevo mapa de bloques
	blocksMap = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]);
	*/
}

void Game::restartLevel() {
	if (lifes->getNumLifes() < 0) {
		exit = true;
	}
	else {
		gameover = false;
		newLevel();
	}
}

void Game::nextLevel() {
	++currentLevel;
	if (currentLevel >= NUM_LEVELS) {
		TopTimes<double> topTimes = TopTimes<double>("../TopTimes/times.txt", timer->getTime());
		exit = true;
	}
	else {
		win = false;
		newLevel();
	}
}

void Game::saveGame() const {
	int cod = 0;
	cout << "Introduce un codigo numerico: ";
	cin >> cod;

	ofstream out("../SavedGame/" + to_string(cod) + ".txt");
	out << currentLevel << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->saveFromFile(out);
	}
	/*
	timer->saveFromFile(out);
	out << endl;
	lifes->saveFromFile(out);
	out << endl;
	ball->saveFromFile(out);
	out << endl;
	paddle->saveFromFile(out);
	out << endl;
	blocksMap->saveFromFile(out);
	*/
	out.close();

	cout << "Se ha guardado correctamente la partida" << endl;
}

void Game::loadGame() {
	int cod = 0;
	cout << "Introduce un codigo numerico: ";
	cin >> cod;

	ifstream in("../SavedGame/" + to_string(cod) + ".txt");
	if (!in.is_open()) {
		try {
			throw FileNotFoundError("loadGame", "../SavedGame/" + to_string(cod) + ".txt");
		}
		catch (FileNotFoundError& e) {
			cout << e.what() << endl;
		}
	}
	else {
		in >> currentLevel;
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->loadFromFile(in);
		}
		/*
		timer->loadFromFile(in);
		lifes->loadFromFile(in);
		ball->loadFromFile(in);
		paddle->loadFromFile(in);
		blocksMap->loadFromFile(in);
		*/
		in.close();
	}
}

// Métodos públicos

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw SDLError("game constructor");
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// crear texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, TEXT_DESC[i].filename, TEXT_DESC[i].hFrames, TEXT_DESC[i].vFrames);
	}

	// se crean los objetos de juego

	// menú
	// botón de jugar
	play = new Play(Vector2D(WIN_WIDTH / 2 - BUTTON_WIDTH / 2, WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2 - OFFSET), BUTTON_WIDTH, BUTTON_HEIGHT, textures[_Play], this);
	// botón de cargar partida
	load = new Load(Vector2D(WIN_WIDTH / 2 - BUTTON_WIDTH / 2, WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + OFFSET), BUTTON_WIDTH, BUTTON_HEIGHT, textures[_Load], this);

	// paredes
	// pared izquierda
	// walls[0] = new Wall(Vector2D(0, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(1, 0));
	gameObjects.push_back(new Wall(Vector2D(0, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(1, 0)));
	// pared de arriba
	// walls[1] = new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_THICKNESS, textures[_Topside], Vector2D(0, 1));
	gameObjects.push_back(new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_THICKNESS, textures[_Topside], Vector2D(0, 1)));
	// pared derecha
	// walls[2] = new Wall(Vector2D(WIN_WIDTH - WALL_THICKNESS, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(-1, 0));
	gameObjects.push_back(new Wall(Vector2D(WIN_WIDTH - WALL_THICKNESS, WALL_THICKNESS), WALL_THICKNESS, WIN_HEIGHT - WALL_THICKNESS, textures[_Side], Vector2D(-1, 0)));

	// vidas del jugador
	// lifes = new Lifes(10, Vector2D(WIN_WIDTH - DIGIT_WIDTH, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits], this);
	gameObjects.push_back(new Lifes(10, Vector2D(WIN_WIDTH - DIGIT_WIDTH, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits], this));

	// contador
	// timer = new Timer(0, Vector2D(0, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits]);
	gameObjects.push_back(new Timer(0, Vector2D(0, 0), DIGIT_WIDTH, DIGIT_HEIGHT, textures[_Digits]));

	// pantalla de victoria
	// winScreen = new Win(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Youwin], this);
	gameObjects.push_back(new Win(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Youwin], this));

	// pantalla de derrota
	// gameoverScreen = new GameOver(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Gameover], this);
	gameObjects.push_back(new GameOver(Vector2D(0, 0), WIN_WIDTH, WIN_HEIGHT, textures[_Gameover], this));

	// plataforma
	// paddle = new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), textures[_Paddle], WALL_THICKNESS, WIN_WIDTH - WALL_THICKNESS);
	gameObjects.push_back(new Paddle(Vector2D(WIN_WIDTH / 2 - PADDLE_WIDTH / 2, WIN_HEIGHT - 50), PADDLE_WIDTH, PADDLE_HEIGHT, Vector2D(0, 0), textures[_Paddle], WALL_THICKNESS, WIN_WIDTH - WALL_THICKNESS));

	// pelota
	// ball = new Ball(Vector2D(WIN_WIDTH / 2 - BALL_TAM / 2, WIN_HEIGHT - 150), BALL_TAM, BALL_TAM, Vector2D(0, 1), textures[_Ball], this);
	gameObjects.push_back(new Ball(Vector2D(WIN_WIDTH / 2 - BALL_TAM / 2, WIN_HEIGHT - 150), BALL_TAM, BALL_TAM, Vector2D(0, 1), textures[_Ball], this));

	// mapa de bloques
	// blocksMap = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]);
	gameObjects.push_back(blocksMap = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(WALL_THICKNESS, WALL_THICKNESS), WIN_WIDTH - 2 * WALL_THICKNESS, WIN_HEIGHT / 2, textures[_Brick]));
}

Game::~Game() {
	// se destruyen las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
	}
	delete play;
	delete load;

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		delete* it;
	}
	/*
	for (int i = 0; i < NUM_WALLS; ++i) {
		delete walls[i];
	}
	delete blocksMap;
	delete paddle;
	delete ball;
	delete lifes;
	delete timer;
	delete winScreen;
	delete gameoverScreen;
	*/
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	// bucle de juego
	while (!exit) {
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
	}
	return false;
}