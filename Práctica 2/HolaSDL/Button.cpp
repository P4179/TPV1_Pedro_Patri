#include "Button.h"

void Button::handleEvents(const SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX = 0, mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_Rect destRect = getRect();
		// se ha clicado en el botón
		if (mouseX >= destRect.x && mouseX <= destRect.x + destRect.w &&
			mouseY >= destRect.y && mouseY <= destRect.y + destRect.h) {
			clicked = true;
		}
	}
}