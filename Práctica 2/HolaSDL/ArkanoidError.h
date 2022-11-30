#pragma once

#include "checkML.h"
#include <stdexcept>

using namespace std;

class ArkanoidError : public logic_error {
public:
	// el mensaje que se recibe es el nombre del m�todo donde se ha producido el error
	ArkanoidError(const string& m) : logic_error("Game error in method " + m + ". ") {}
};
