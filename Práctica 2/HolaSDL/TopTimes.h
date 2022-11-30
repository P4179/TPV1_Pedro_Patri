#pragma once
#include "checkML.h"
#include <fstream>
#include <string>
#include "ArraySob.h"
#include "FileNotFoundError.h"

using namespace std;

template<class T>
class TopTimes {
private:
	// selecciona el n�mero con el tiempo entre toda la l�nea
	T numTime(ifstream& in) const {
		T numTime;
		string aux;
		in >> aux >> aux >> numTime;
		return numTime;
	}

	// lee los mejores tiempos del archivo y los guarda en un array sobredimensionado
	ArraySob<T> readTimes(const string& filename) const {
		ifstream in(filename);
		if (!in.is_open()) {
			throw FileNotFoundError("readTimes", filename);
		}
		else {
			ArraySob<T> times = ArraySob<T>(10);

			string line;
			getline(in, line);
			while (!in.eof()) {
				times.push(numTime(in));
			}
			in.close();

			return times;
		}
	}

	// guarda los tiempos en un archivo
	void saveTimes(const string& filename, T newTime) const {
		try {
			ArraySob<T> times = readTimes(filename);
			ofstream out(filename);
			out << "TOP 10 TIMES" << endl;
			try {
				times.push(newTime);
			}
			catch (string e) {
				if (newTime < times[times.size() - 1]) {
					times[times.size() - 1] = newTime;
				}
			}

			times.sortMin();

			for (int i = 0; i < times.size(); ++i) {
				out << "Time " << (i + 1) << ": " << times[i];
				if (i < times.size() - 1) {
					out << endl;
				}
			}
			out.close();
		}
		// no existe ning�n archivo que almacene el top10 tiempos
		catch (FileNotFoundError& e) {
			ofstream out(filename);
			out << "TOP 10 TIMES" << endl;
			out << "Time 1: " << newTime << endl;
			out.close();
		}
	}


public:
	TopTimes(const string& filename, const T& newTime) {
		saveTimes(filename, newTime);
	}
};