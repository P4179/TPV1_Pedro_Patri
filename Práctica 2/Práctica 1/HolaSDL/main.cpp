#include "Game.h"

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks
	Game* game = nullptr;
	try {
		game = new Game();
		game->run();
		delete game;
	}
	catch (string e) {
		cout << e;
	}
	return 0;
}