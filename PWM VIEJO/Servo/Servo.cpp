/*
 * Servo.cpp
 *
 *  Created on: 20 sep. 2026
 *      Author: sofia
 */

#include "Servo.h"

Servo::Servo(uint8_t angulo, uint32_t periodo, uint8_t puerto, uint8_t pin, uint8_t actividad,
		pwm_channel_t canal) :
		Pwm(puerto, pin, actividad, canal) {
	this->Off();
	this->Initialize(1000 + (uint32_t(angulo) * 1000) / 180, periodo, MICRO_SEG);
	this->On();
}

void Servo::setPeriodo(uint32_t periodo) {
	this->SetPeriod(periodo, MICRO_SEG);
}
void Servo::setAngulo(uint8_t angulo) {
	this->Off();
	uint32_t tiempoAlto = 1000 + (uint32_t(angulo) * 1000) / 180;
	this->SetTon(tiempoAlto, MICRO_SEG);
	this->On();

}
Servo& Servo::operator=(uint8_t angulo) {
	this->setAngulo(angulo);
	return *this;
}
