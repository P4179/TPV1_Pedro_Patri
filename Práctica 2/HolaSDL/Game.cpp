#include "Game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	// se carga la configuración en un vector
	loadConfig("../Config/config.txt");
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, config[Win_Width], config[Win_Height], SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw SDLError("game constructor");
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// crear texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, TEXT_DESC[i].filename, TEXT_DESC[i].hFrames, TEXT_DESC[i].vFrames);
	}

	// menú
	// botón jugar
	buttons.push_back(new Play(Vector2D(config[Win_Width] / 2 - config[Button_width] / 2, config[Win_Height] / 2 - config[Button_height] / 2 - config[Button_offset]), config[Button_width], config[Button_height], textures[_Play], this));
	// botón cargar partida
	buttons.push_back(new Load(Vector2D(config[Win_Width] / 2 - config[Button_width] / 2, config[Win_Height] / 2 - config[Button_height] / 2 + config[Button_offset]), config[Button_width], config[Button_height], textures[_Load], this));

	// objetos estáticos
	// paredes
	// pared izquierda
	gameObjects.push_back(new Wall(Vector2D(0, config[Wall_thickness]), config[Wall_thickness], config[Win_Height] - config[Wall_thickness], textures[_Side], Vector2D(1, 0)));
	// pared de arriba
	gameObjects.push_back(new Wall(Vector2D(0, 0), config[Win_Width], config[Wall_thickness], textures[_Topside], Vector2D(0, 1)));
	// pared derecha
	gameObjects.push_back(new Wall(Vector2D(config[Win_Width] - config[Wall_thickness], config[Wall_thickness]), config[Wall_thickness], config[Win_Height] - config[Wall_thickness], textures[_Side], Vector2D(-1, 0)));

	// mapa de bloques
	gameObjects.push_back(new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(config[Wall_thickness], config[Wall_thickness]), config[Win_Width] - 2 * config[Wall_thickness], config[Win_Height] / 2, textures[_Brick]));

	// vidas del jugador
	gameObjects.push_back(new Lifes(10, Vector2D(config[Win_Width] - config[Digit_width], 0), config[Digit_width], config[Digith_height], textures[_Digits], this));

	// contador
	gameObjects.push_back(new Timer(0, Vector2D(0, 0), config[Digit_width], config[Digith_height], textures[_Digits]));

	// pantalla de victoria
	gameObjects.push_back(new Win(Vector2D(0, 0), config[Win_Width], config[Win_Height], textures[_Youwin], this));

	// pantalla de derrota
	gameObjects.push_back(new GameOver(Vector2D(0, 0), config[Win_Width], config[Win_Height], textures[_Gameover], this));

	// objetos dinámicos
	// plataforma
	movingObjects.push_back(new Paddle(Vector2D(config[Win_Width] / 2 - config[Paddle_width] / 2, config[Win_Height] - 50), config[Paddle_width], config[Paddle_height], Vector2D(0, 0), textures[_Paddle], config[Wall_thickness], config[Win_Width] - config[Wall_thickness]));

	// pelota
	movingObjects.push_back(new Ball(Vector2D(config[Win_Width] / 2 - config[Ball_tam] / 2, config[Win_Height] - 150), config[Ball_tam], config[Ball_tam], Vector2D(0, 1), textures[_Ball], this));
}

Game::~Game() {
	// se destruyen las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete textures[i];
	}
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete* it;
	}
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		delete* it;
	}
	for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
		delete* it;
	}
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
		if (frameTime >= config[Frame_Rate]) {
			update(); // Actualiza el estado de todos los objetos del juego
			startTime = SDL_GetTicks();
		}
		render(); // Renderiza todos los objetos del juego
	}
}

void Game::render() const {
	SDL_RenderClear(renderer);

	if (menu) {
		// se redneriza el menú
		for (auto it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->render();
		}
	}
	else {
		// se rendeerizan los objetos dinámcios y luego, lo estáticos
		for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
			(*it)->render();
		}
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->render();
		}
	}

	SDL_RenderPresent(renderer);

	if (gameover || win) {
		SDL_Delay(config[Screen_wait]);
	}
}

void Game::update() {
	if (menu) {
		for (auto it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->update();
		}
	}
	else {
		if (gameover) {
			restartLevel();
		}
		else if (win) {
			nextLevel();
		}

		for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
			(*it)->update();
		}
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->update();
		}

		destroyMovingObjects();
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
		}

		for (auto it = buttons.begin(); it != buttons.end(); ++it) {
			(*it)->handleEvents(event);
		}
		for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
			(*it)->handleEvents(event);
		}
	}
}

// Gestión del paso de niveles

void Game::newLevel() {
	// se destruye el mapa de bloque antiguo
	bool enc = false;
	auto it = gameObjects.begin();
	while(it != gameObjects.end() && !enc) {
		// dos astéricos delante del iterador para acceder primero al puntero a clase que apunta el iterador
		// y luego, a la propia instancia
		if (typeid(**it) == typeid(BlocksMap)) {
			// se elimina el mapa anterior
			delete* it;
			*it = new BlocksMap("../Maps/level0" + to_string(currentLevel) + ".ark", Vector2D(config[Wall_thickness], config[Wall_thickness]), config[Win_Width] - 2 * config[Wall_thickness], config[Win_Height] / 2, textures[_Brick]);
			enc = true;
		}
		++it;
	}
	
	// se marcan los rewards para borrar, es decir, que apuntan a null
	for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
		if (dynamic_cast<Reward*> (*it) != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	// se borrar los rewards marcados para borrar
	destroyMovingObjects();

	// se recolocan la plataforma y la bola
	// motivo por el que se han hecho dos listas, una de objetos estáticos y otra de dinámicos
	for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
		if (typeid(**it) == typeid(Paddle)) {
			(*it)->recolocate(Vector2D(config[Win_Width] / 2 - config[Paddle_width] / 2, config[Win_Height] - 50), Vector2D(0, 0));
		}
		else if (typeid(**it) == typeid(Ball)) {
			(*it)->recolocate(Vector2D(config[Win_Width] / 2 - config[Ball_tam] / 2, config[Win_Height] - 150), Vector2D(0, 1));
		}
	}
}

void Game::restartLevel() {
	bool enc = false;
	auto it = gameObjects.begin();
	while (it != gameObjects.end() && !enc) {
		if (typeid(**it) == typeid(Lifes)) {
			enc = true;
			// casteo dinámico después de haber comprobado si el puntero a clase es un Lifes
			// porque ArkanoidObject no tiene un método getNumLifes, es propio de la clase Lifes
			if (dynamic_cast<Lifes*>(*it)->getNumLifes() < 0) {
				exit = true;
			}
		}
		++it;
	}
	if (!exit) {
		gameover = false;
		newLevel();
	}
}

void Game::nextLevel() {
	++currentLevel;
	if (currentLevel >= NUM_LEVELS) {
		bool enc = false;
		auto it = gameObjects.begin();
		while (it != gameObjects.end() && !enc) {
			enc = true;
			if (typeid(**it) == typeid(Timer)) {
				TopTimes<double> topTimes = TopTimes<double>("../TopTimes/times.txt", dynamic_cast<Timer*>(*it)->getTime());
				exit = true;
			}
			++it;
		}
	}
	if (!exit) {
		win = false;
		newLevel();
	}
}

// Gestión de información

void Game::saveGame() const {
	int cod = 0;
	cout << "Introduce un codigo numerico: ";
	cin >> cod;

	// nivel actual, mapa de bloques, lifes, timer, paddle, ball
	ofstream out("../SavedGame/" + to_string(cod) + ".txt");
	out << currentLevel << endl;
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		(*it)->saveFromFile(out);
	}
	int contRewards = 0;
	for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
		if (typeid(**it) == typeid(Paddle) || typeid(**it) == typeid(Ball)) {
			(*it)->saveFromFile(out);
		}
		else {
			++contRewards;
		}
	}
	out << contRewards << endl;
	for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
		if (dynamic_cast<Reward*>(*it) != nullptr) {
			(*it)->saveFromFile(out);
		}
	}
	out.close();

	cout << "Se ha guardado correctamente la partida" << endl;
}

void Game::loadGame() {
	int cod = 0;
	cout << "Introduce un codigo numerico: ";
	cin >> cod;

	ifstream in("../SavedGame/" + to_string(cod) + ".txt");
	if (!in.is_open()) {
		throw FileNotFoundError("loadGame", "../SavedGame/" + to_string(cod) + ".txt");
	}
	else {
		in >> currentLevel;
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			(*it)->loadFromFile(in);
		}

		for (auto it = movingObjects.begin(); it != movingObjects.end(); ++it) {
			if (typeid(**it) == typeid(Paddle) || typeid(**it) == typeid(Ball)) {
				(*it)->loadFromFile(in);
			}
		}
		
		int contRewards;
		string r;
		in >> contRewards;
		for (int i = 0; i < contRewards; ++i) {
			in >> r;
			createRewards(stringToRewardType(r));
			movingObjects.back()->loadFromFile(in);
		}
		in.close();
	}
}

RewardType Game::stringToRewardType(string s) {
	RewardType r = (RewardType)0;
	if (s == "PassLv") {
		r = PassLv;
	}
	else if (s == "AddLife") {
		r = AddLife;
	}
	else if (s == "BigPlatform") {
		r = BigPlatform;
	}
	else if (s == "SmallPlatform") {
		r = SmallPlatform;
	}
	return r;
}

void Game::createRewards(RewardType r, Vector2D pos) {
	// se busca el paddle
	Paddle* auxPaddle = nullptr;
	bool enc = false;
	auto it = movingObjects.begin();
	while(it != movingObjects.end() && !enc) {
		if (typeid(**it) == typeid(Paddle)) {
			enc = true;
			auxPaddle = dynamic_cast<Paddle*>(*it);
		}
		++it;
	}

	// se buscan las vidas
	auto it2 = gameObjects.begin();
	Lifes* auxLifes = nullptr;
	enc = false;
	while (it2 != gameObjects.end() && !enc) {
		if (typeid(**it2) == typeid(Lifes)) {
			enc = true;
			auxLifes = dynamic_cast<Lifes*>(*it2);
		}
		++it2;
	}

	switch (r) {
	case 0:
		movingObjects.push_back(new RewardPassLv(pos, config[Reward_width], config[Reward_height], textures[_Rewards], this, auxPaddle));
		break;
	case 1:
		movingObjects.push_back(new RewardAddLife(pos, config[Reward_width], config[Reward_height], textures[_Rewards], this, auxPaddle, auxLifes));
		break;
	case 2:
		movingObjects.push_back(new RewardChangePlatform(pos, config[Reward_width], config[Reward_height], textures[_Rewards], this, 1, auxPaddle, 10));
		break;
	case 3:
		movingObjects.push_back(new RewardChangePlatform(pos, config[Reward_width], config[Reward_height], textures[_Rewards], this, 3, auxPaddle, -10));
		break;
	}
}

void Game::loadConfig(const string& filename) {
	ifstream in(filename);
	if (!in.is_open()) {
		throw FileNotFoundError("loadConfig", filename);
	}
	else {
		string aux;
		while (!in.eof()) {
			in >> aux;
			in >> aux;
			config.push_back(stoi(aux));
		}
		in.close();
	}
}

// Gestión de destrucción de los rewards

void Game::destroyMovingObjects() {
	auto it = movingObjects.begin();
	while (it != movingObjects.end()) {
		if (*it == nullptr) {
			it = movingObjects.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::destroyMe(MovingObject* m) {
	bool enc = false;
	auto it = movingObjects.begin();
	while (it != movingObjects.end() && !enc) {
		if (*it == m) {
			enc = true;
			delete* it;
			*it = nullptr;
		}
		++it;
	}
}

// Colisiones

bool Game::collidesRewards(const SDL_Rect& rect, bool& collidesPaddle) {
	collidesPaddle = false;

	// Rewards - Paddle
	bool enc = false;
	auto it = movingObjects.begin();
	while (it != movingObjects.end() && !enc) {
		if (typeid(**it) == typeid(Paddle)) {
			enc = true;
			if ((*it)->collides(rect)) {
				collidesPaddle = true;
				return true;
			}
		}
		++it;
	}

	// Rewards - DeadLine
	if (rect.y >= config[Win_Height]) {
		return true;
	}

	return false;
}

bool Game::collides(const SDL_Rect& rectBall, Vector2D& colVector, bool& isPaddle) {
	isPaddle = false;

	// Ball - Walls
	// dos opciones: método en Wall que determinar si la bola ha chocado con ella o se pasan los parámetros
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		if (typeid(**it) == typeid(Wall)) {
			if (dynamic_cast<Wall*>(*it)->collidesBall(rectBall, colVector)) {
				return true;
			}
		}
	}

	// Ball - Paddle
	bool enc = false;
	auto it = movingObjects.begin();
	while (it != movingObjects.end() && !enc) {
		if (typeid(**it) == typeid(Paddle)) {
			enc = true;
			if (dynamic_cast<Paddle*>(*it)->collidesBall(rectBall, colVector)) {
				isPaddle = true;
				return true;
			}
		}
		++it;
	}

	// Ball - Blocks
	enc = false;
	auto it2 = gameObjects.begin();
	while (it2 != gameObjects.end() && !enc) {
		if (typeid(**it2) == typeid(BlocksMap)) {
			enc = true;
			SDL_Rect rectBlock;
			if (dynamic_cast<BlocksMap*>(*it2)->collidesBall(rectBall, colVector, rectBlock)) {
				if (rand() % config[Probability] == 0) {
					createRewards((RewardType)(rand() % 4), Vector2D(rectBlock.x, rectBlock.y));
				}
				// si no quedan bloques se ha ganado
				if (dynamic_cast<BlocksMap*>(*it2)->nBlocks() == 0) {
					win = true;
				}
				return true;
			}
		}
		++it2;
	}

	// Ball - DeadLine
	if (rectBall.y >= config[Win_Height]) {
		gameover = true;
	}
	return false;
}