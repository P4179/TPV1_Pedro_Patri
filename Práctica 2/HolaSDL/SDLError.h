#pragma once

#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"
#include "ArkanoidError.h"

class SDLError : public ArkanoidError {
public:
	// SDL_GetError() y IMG_GetError devuelven un texto con el error de SDL y de la imagen, respectivamente
	// si no hay ningún error devuelven un texto vacío
	SDLError(const string& nomMethod) :
		ArkanoidError(nomMethod + ". " + SDL_GetError() + ". " + IMG_GetError() + ". ") {}
};