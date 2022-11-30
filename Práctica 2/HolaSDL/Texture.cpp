#include "Texture.h"
#include <iostream>

using namespace std;

// Métodos privados
// por prevención, antes de crear una nueva textura se destruye por si había alguna guardada
void Texture::libera() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw SDLError("load");
	libera();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == nullptr) throw SDLError("load");
	numRows = nRows;
	numCols = nCols;
	// tamaños del fichero
	w = tempSurface->w;
	h = tempSurface->h;
	// tamaños de cada uno de los frames
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);
}

// Métodos públicos
// dibujar todo
void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	// tres últimos campos - ángulo, ángulo, rotación
	// se le puede pasar SDL_FLIP_NONE y entonces, no rota
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
}

// dibujar un frame
void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;
	srcRect.y = fh * row;
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
}