/*
 * miPWM.cpp
 *
 *  Created on: 8 oct. 2026
 *      Author: sofia
 */

#include "miPWM.h"

uint8_t miPWM::cantServos = 0;

miPWM::miPWM(uint8_t puerto, uint8_t pin) :
		m_port(puerto), m_pin(pin) {
	cantServos++;
	idServo = cantServos;
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 8); //el 7 es el SCT, lo habilito
	SYSCON->SCTCLKSEL = 1;       // Selecciona el MAIN CLOCK como fuente del SCT
	SYSCON->SCTCLKDIV = 1;               // divisor
}

void miPWM::inicializar(uint32_t periodo, uint8_t duty) {
	SetSwitchMatrizSCTOUT(m_pin, m_port, idServo -1);

	SCT->CONFIG |= (1 << 0); //seteandolo como unified timer (nos interesa un único contador)
	SCT->CONFIG |= (1 << 17); //seteandolo con auto limit (el contador vuelve a cero cuando se ejecuta el evento)

	this->setPeriod(periodo);
	this->setDutyCicle(duty);

	/*	By default event1--match1 , event2--match2 , ...*/
	SCT->EV[idServo].STATE = 0xFFFFFFFF;
	SCT->EV[idServo].CTRL = (idServo << 0) | (1 << 12); // match "channel"  only condition

	//asociar un evento a poner un 1 o un 0
	SCT->OUT[idServo - 1].SET = (1 << 0); //el evento 0 pone un 1 en el out
	SCT->OUT[idServo - 1].CLR = (1 << idServo); //el evento 1 pone un 0 en el out

	SCT->OUTPUT &= ~(1 << (idServo - 1)); //default en 0

	SCT->RES &= ~(0b11 << ((idServo - 1) * 2)); //limpiar el res
	SCT->RES |= (0b10 << ((idServo - 1) * 2)); //si ocurre un conflicto queda el estado inactivo
}

void miPWM::stop(void) {
	SCT->CTRL |= (1 << 2); //contador en HALT, queda detenido
}

void miPWM::start(void) {
	SCT->CTRL &= ~(1 << 2); //limpia el HALT, lo pone en RUN
}

void miPWM::setPeriod(uint32_t periodo) {
	SCT->MATCH[0] = periodo * (FREQ_CLOCK / 1000000); //canal 0 del match es el periodo
	SCT->MATCHREL[0] = periodo * (FREQ_CLOCK / 1000000);
	/*	By default event1--match1 , event2--match2 , ...*/
	SCT->EV[0].STATE = 0xFFFFFFFF;
	SCT->EV[0].CTRL = (1 << 12); // match "channel"  only condition
}

void miPWM::setDutyCicle(uint8_t duty) { //duty es un PORCENTAJE
	SCT->MATCH[idServo] = (SCT->MATCH[0] * duty) / 100; //setear tiempo en alto
	SCT->MATCHREL[idServo] = (SCT->MATCH[0] * duty) / 100;

}

void miPWM::SetSwitchMatrizSCTOUT(uint8_t bit, uint8_t port,
		uint8_t out_number) {
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);

	uint8_t aux = ~(bit + port * 0x20); /*	EL REGISTRO POR DEFECTO ESTA EN 0xFF	*/

	switch (out_number) {
	case 0:
		SWM->PINASSIGN_DATA[7] &= ~(aux << 24);
		break;
	case 1:
		SWM->PINASSIGN_DATA[8] &= ~(aux << 0);
		break;
	case 2:
		SWM->PINASSIGN_DATA[8] &= ~(aux << 8);
		break;
	case 3:
		SWM->PINASSIGN_DATA[8] &= ~(aux << 16);
		break;
	case 4:
		SWM->PINASSIGN_DATA[8] &= ~(aux << 24);
		break;
	case 5:
		SWM->PINASSIGN_DATA[9] &= ~(aux << 0);
		break;
	case 6:
		SWM->PINASSIGN_DATA[9] &= ~(aux << 8);
		break;
	}
	SYSCON->PRESETCTRL0 |= (1 << 8);	//Reset of SCT CONTROL
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);

}

