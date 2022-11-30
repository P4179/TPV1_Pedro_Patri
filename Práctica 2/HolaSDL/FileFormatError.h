#pragma once

#include "checkML.h"
#include <string>
#include "ArkanoidError.h"

class FileFormatError : public ArkanoidError {
public:
	FileFormatError(const string& nomMethod, int mapWidth, int mapHeight) : ArkanoidError(nomMethod + ". Wrong map size. Map width: " + to_string(mapWidth) + ". Map height: " + to_string(mapHeight)) {}

	FileFormatError(const string& nomMethod, int color) : ArkanoidError(nomMethod + ". Wrong color block: " + to_string(color)) {}

	FileFormatError(const string& nomMethod) : ArkanoidError(nomMethod + ". Empty map") {}
};