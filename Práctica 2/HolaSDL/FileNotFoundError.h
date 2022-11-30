#pragma once

#include "checkML.h"
#include "ArkanoidError.h"

class FileNotFoundError : public ArkanoidError {
public:
	// nombre del m�todo y el fichero donde se produce el error
	FileNotFoundError(const string& nomMethod, const string& file) :
		ArkanoidError(nomMethod + ". File " + file + " not found") {}
};