#pragma once

#include "checkML.h"
#include "SDL.h"

class GameObject {
public:
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvents(const SDL_Event& event) = 0;
};