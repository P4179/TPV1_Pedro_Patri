#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"
#include <string.h>
#include <fstream>

using uint = unsigned int;

class Timer : public ArkanoidObject {
private:
	double startTime = 0;
	double time = 0;

	// a partir del tiempo se encuentran los frame de la textura deseados
	void posFrame(char digitTime, uint& rowFrame, uint& colFrame) const;

public:
	Timer(double startTime, Vector2D pos, uint width, uint height, Texture* texture) :
		startTime(startTime), ArkanoidObject(pos, width, height, texture) {}

	// renderizado del contador
	virtual void render() const;

	// se actualiza el tiempo que ha transcurrido desde que comenzó la partida
	virtual void update();

	// getter del tiempo
	double getTime() const;

	// guardar tiempo
	virtual void saveFromFile(ofstream& out) const;

	// cargar tiempo
	virtual void loadFromFile(ifstream& in);

	// redefinido para que deje de ser una clase abstracta
	virtual void handleEvents(const SDL_Event& event) {}

};