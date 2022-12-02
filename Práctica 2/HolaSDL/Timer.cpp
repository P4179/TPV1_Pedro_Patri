#include "Timer.h"

void Timer::posFrame(char digitTime, uint& rowFrame, uint& colFrame) const {
	switch (digitTime) {
	case '0':
		rowFrame = 0;
		colFrame = 0;
		break;
	case '1':
		rowFrame = 0;
		colFrame = 1;
		break;
	case '2':
		rowFrame = 0;
		colFrame = 2;
		break;
	case '3':
		rowFrame = 0;
		colFrame = 3;
		break;
	case '4':
		rowFrame = 1;
		colFrame = 0;
		break;
	case '5':
		rowFrame = 1;
		colFrame = 1;
		break;
	case '6':
		rowFrame = 1;
		colFrame = 2;
		break;
	case '7':
		rowFrame = 1;
		colFrame = 3;
		break;
	case '8':
		rowFrame = 2;
		colFrame = 0;
		break;
	case '9':
		rowFrame = 2;
		colFrame = 1;
		break;
	case '.':
		rowFrame = 2;
		colFrame = 2;
		break;
	}
}

void Timer::render() const {
	string timeString = to_string(time);
	int i = 0;
	// se renderiza la parte entera del número
	while (timeString[i] != '.') {
		uint rowFrame = 0, colFrame = 0;
		posFrame(timeString[i], rowFrame, colFrame);

		SDL_Rect destRect = getRect();
		destRect.x = pos.getX() + width * i;
		texture->renderFrame(destRect, rowFrame, colFrame);
		++i;
	}
	// se renderiza el punto y la parte decimal del número
	int j = i + 3;
	for (i; i < j; ++i) {
		uint rowFrame = 0, colFrame = 0;
		posFrame(timeString[i], rowFrame, colFrame);

		SDL_Rect destRect = getRect();
		destRect.x = pos.getX() + width * i;
		texture->renderFrame(destRect, rowFrame, colFrame);
	}
}

void Timer::update() {
	time = startTime + SDL_GetTicks();
	time = time / 1000;
}

double Timer::getTime() const {
	return time;
}

void Timer::saveFromFile(ofstream& out) const {
	out << time << endl;
}

void Timer::loadFromFile(ifstream& in) {
	in >> startTime;
}