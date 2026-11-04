/*
 * Timers.cpp
 *
 *  Created on: 24 jun 2026
 *      Author: feldman
 */

#include <Timers.h>

Timers::Timers() {
	this->longitudActual = 0;
}

uint8_t Timers::cantidad() {
	return this->longitudActual;
}

Timers& Timers::operator<<(Timer* recibido) {
	if (this->longitudActual < MAX_TIMERS) {
		this->timer[longitudActual] = recibido;
		this->longitudActual++;
	}
	return *this;
}

Timer& Timers::operator[](uint8_t indice) {
	if (indice < this->longitudActual) {
		return *this->timer[indice];
	} else {
		static Timer error;
		return error;
	}
}

Timers::~Timers() {
}

