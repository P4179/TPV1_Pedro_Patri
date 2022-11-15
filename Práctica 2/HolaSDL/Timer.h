#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include <string.h>
#include <fstream>

using uint = unsigned int;

class Timer {
private:
	double startTime = 0;
	double time = 0;
	Vector2D pos;
	uint width = 0;
	uint height = 0;
	Texture* texture = nullptr;

	// a partir del tiempo se encuentran los frame de la textura deseados
	void posFrame(char digitTime, uint& rowFrame, uint& colFrame) const;

public:
	Timer(double startTime, Vector2D pos, uint width, uint height, Texture* texture) :
		startTime(startTime), pos(pos), width(width), height(height), texture(texture) {}

	// renderizado del contador
	void render() const;

	// se actualiza el tiempo que ha transcurrido desde que comenzó la partida
	void update();

	// getter del tiempo
	double getTime() const;

	// guardar tiempo
	void saveGame(ofstream& out) const;
};