#pragma once

#include "checkML.h"
#include "SDLError.h"
#include "SDL_ttf.h"

using uint = unsigned int;

struct color {
	uint red = 0;
	uint green = 0;
	uint blue = 0;
};

// No conseguimos cargar la librería
// Si creamos una instancia de Font o inicializamos (TTF_Init) se produce un error
class Font {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0;
	uint h = 0;

	// por prevención, antes de crear una nueva textura se destruye por si había alguna guardada
	void libera() {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		w = h = 0;
	}

	void load(char* filename, string text, uint size, color col) {
		// se abre la fuente
		TTF_Font* font = TTF_OpenFont(filename, size);
		if (font == nullptr) throw SDLError("load");

		// color de la fuente
		SDL_Color color = { col.red, col.green, col.blue };

		// se convierte la fuente en un surface
		SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (tempSurface == nullptr) throw SDLError("load");
		libera();
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (texture == nullptr) throw SDLError("load");
		// tamaños del fichero
		w = tempSurface->w;
		h = tempSurface->h;

		TTF_CloseFont(font);
		SDL_FreeSurface(tempSurface);
	}

public:
	Font(SDL_Renderer* r, char* filename, string text, uint size, color col) :
		renderer(r) {
		load(filename, text, size, col);
	};
	~Font() { libera(); };

	// dibujar todo
	void render(const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) const {
		SDL_Rect srcRect;
		srcRect.x = 0; srcRect.y = 0;
		srcRect.w = w; srcRect.h = h;
		// tres últimos campos - ángulo, ángulo, rotación
		// se le puede pasar SDL_FLIP_NONE y entonces, no rota
		SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);
	}
};