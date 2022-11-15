#pragma once
#include "checkML.h"

using uint = unsigned int;

// array sobredimensionado
template <class T>
class ArraySob {
private:
	T* datos = nullptr;
	uint nElems = 0;	// número de elementos que tiene
	uint tam = 0;	// tamaño del array

	void libera() {
		delete[] datos;
	}

	void copy(const ArraySob& other) {
		tam = other.tam;
		nElems = other.nElems;
		datos = new T[tam];
		for (unsigned int i = 0; i < nElems; ++i) {
			datos[i] = other.datos[i];
		}
	}

	void mergeMin(T*& datos, int ini, int mitad, int fin) {
		// se crea una estructura auxiliar donde se guardan los valores del intervalo
		int auxTam = fin - ini;
		T* aux = new T[auxTam];

		int i = ini;
		int j = mitad;
		int k = 0;  // índice que apunta al primer hueco libre en la estructura auxiliar
		// se comparan los elementos de la estructura original [ini,mitad) con [mitad,fin) para guardar los menores
		while (k < auxTam && i < mitad && j < fin) {
			if (datos[i] < datos[j]) {
				aux[k] = datos[i];
				i++;
			}
			else {
				aux[k] = datos[j];
				j++;
			}
			k++;
		}

		// se guardan los elementos restantes del intervalo [ini,mitad)
		for (i; i < mitad; i++) {
			aux[k] = datos[i];
			k++;
		}

		// se guardan los elementos restantes del intervalo [mitad, fin)
		for (j; j < fin; j++) {
			aux[k] = datos[j];
			k++;
		}

		// se copian los elementos de la estructura auxiliar a la original
		for (int i = 0; i < auxTam; i++) {
			datos[ini + i] = aux[i];
		}

		delete[] aux;
	}

	void mergeSort(T*& datos, int ini, int fin) {
		int n = fin - ini;
		if (n <= 1) {
			return;
		}
		else {
			int mitad = (ini + fin) / 2;
			mergeSort(datos, ini, mitad);
			mergeSort(datos, mitad, fin);
			mergeMin(datos, ini, mitad, fin);
		}
	}

public:
	// constructor
	ArraySob(uint tam) {
		this->tam = tam;
		datos = new T[tam];
	}

	// Regla de tres: destructor, constructor por copia y asignación
	// destructor
	~ArraySob() {
		libera();
	}

	// constructor por copia
	ArraySob(const ArraySob& other) {
		copy(other);
	}

	// asignación
	ArraySob& operator=(const ArraySob& other) {
		if (this != &other) {
			libera();
			copy(other);
		}
		return *this;
	}

	void sortMin() {
		mergeSort(datos, 0, nElems);
	}

	int size() {
		return nElems;
	}

	void push(const T& elem) {
		if (nElems >= tam) {
			throw string("El array está lleno");
		}
		datos[nElems] = elem;
		++nElems;
	}

	// como se pasa la dirección de memoria se puede modificar el valor del componente del array
	T& operator[](int index) {
		if (index >= tam) {
			throw string("El índice está fuera del array");
		}
		return datos[index];
	}
};