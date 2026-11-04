/*
 * pulsador.cpp
 *
 *  Created on: 30 jun. 2026
 *      Author: sofia
 */

#include <1-modulos/9-Pulsador/pulsador.h>

pulsador::pulsador(uint8_t port, uint8_t bit):Gpio(port, bit, PULLUP, INPUT, LOW),
port(port),
bit(bit) {
}

pulsador::~pulsador() {
	// TODO Auto-generated destructor stub
}

