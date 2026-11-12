/*
 * Servo.cpp
 *
 *  Created on: 20 sep. 2026
 *      Author: sofia
 */

#include "Servo.h"

uint32_t PERIODO_SERVO = 20000;

Servo::Servo(uint32_t angulo, uint8_t puerto, uint8_t pin) :
		miPWM(puerto, pin) {
	uint32_t tOn = 1000 + (angulo* 1000) / 180;
	this->inicializar(PERIODO_SERVO, tOn);
}

void Servo::setAngulo(uint32_t angulo) {
	if (angulo != m_angulo) {
		uint32_t tOn = 500 + (angulo * 1900) / 180;
		this->setTimeOn(tOn);
		m_angulo = angulo;
	}
}
Servo& Servo::operator=(uint32_t angulo) {
	this->setAngulo(angulo);
	return *this;
}
