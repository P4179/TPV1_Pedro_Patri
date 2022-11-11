#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

// clase que sirve para mostrar las pantallas de Gameover y Win
class End {
private:
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Texture* texture = nullptr;

public:
	End(Vector2D pos, uint width, uint height, Texture* texture) :
		pos(pos), width(width), height(height), texture(texture) {}

	void render();
};