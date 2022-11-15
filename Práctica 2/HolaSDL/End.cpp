#include "End.h"

// M�todos p�blicos

void End::render() {
	SDL_Rect destRect;
	destRect.x = pos.getX();
	destRect.y = pos.getY();
	destRect.w = width;
	destRect.h = height;
	texture->render(destRect);
}