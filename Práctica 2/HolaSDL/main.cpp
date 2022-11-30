#include "Game.h"

#include "ArkanoidError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h"

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks
	
	Game* game = nullptr;
	try {
		game = new Game();
		game->run();
		delete game;
	}

	catch (FileNotFoundError& e) {
		cout << e.what();
	}
	catch (FileFormatError& e) {
		cout << e.what();
	}
	catch (SDLError& e) {
		cout << e.what();
	}
	catch (ArkanoidError& e) {
		cout << e.what();
	}

	return 0;
}