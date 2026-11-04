/*
 * led.cpp
 *
 *  Created on: 24 jun 2026
 *      Author: feldman
 */

#include "led.h"

led::led(uint8_t puerto, uint8_t bit, uint8_t estadoInit):Gpio(puerto, bit, PUSHPULL, OUTPUT, LOW), m_estado(estadoInit),
m_puerto(puerto),
m_bit(bit) {
	if (estadoInit) {
		this->SetPin();
	} else {
		this->ClrPin();
	}
}

void led::On(void) {
	this->SetPin();
}

void led::Off(void) {
	this->ClrPin();
}

void led::Blink(void) { //crear el timer para que entre acá cada tiempo definido
	if (this->GetPin() == OFF) {
		this->SetPin();
	} else {
		this->ClrPin();
	}
}

led::~led() {
	// TODO Auto-generated destructor stub
}

