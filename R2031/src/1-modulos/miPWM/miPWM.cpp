// ESTO LO TENGO QUE PROBAR, LA OTRA VERSIÓN FUNCIONA PERO ESTA ES MEJOR
/*
 * miPWM.cpp
 *
 *  Created on: 8 oct. 2026
 *      Author: sofia
 */

#include "miPWM.h"

uint8_t miPWM::cantPWM = 0;

const uint8_t canalesSCT[] = { PA_SCT_OUT0, PA_SCT_OUT1, PA_SCT_OUT2,
PA_SCT_OUT3, PA_SCT_OUT4, PA_SCT_OUT5, PA_SCT_OUT6 };

#define MAX_CANALES 7

miPWM::miPWM(uint8_t puerto, uint8_t pin) :
		m_port(puerto), m_pin(pin) {
	cantPWM++;
	idPWM = cantPWM;
	if (idPWM > 7) { //si supero el máximo, sobreescribo el último
		idPWM = 7;
	}
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 8); //el 8 es el SCT, lo habilito
	SYSCON->SCTCLKSEL = 1;       // Selecciona el MAIN CLOCK como fuente del SCT
	SYSCON->SCTCLKDIV = 1; // divisor lo tomo como 1, después paso de µs a ticks
}

void miPWM::inicializar(uint32_t periodo, uint32_t tOn) {
	this->stop(); //por las dudas siempre apago antes de hacer cambios

	PINASSIGN_Config(canalesSCT[idPWM - 1], m_port, m_pin);
	if (idPWM == 1) { //esto es para todos los canales, así que lo hago solo una vez
		SYSCON->PRESETCTRL0 &= ~(1 << 8); // pone el SCT en reset (0 = en reset)
		SYSCON->PRESETCTRL0 |= (1 << 8);  // lo saca del reset (1 = operativo)

		SCT->CONFIG |= (1 << 0); //seteandolo como unified timer (nos interesa un único contador)
		SCT->CONFIG |= (1 << 17); //seteandolo con auto limit (el contador vuelve a cero cuando se ejecuta el evento)

		SCT->EV[0].STATE = 0xFFFFFFFF; //estado = 0 SIEMPRE porque no uso la MdE
		SCT->EV[0].CTRL = (1 << 12); // match 1 condition only = solo se dispara el evento cuando contador = match, sin entradas externas
	}

	//PARTE DEL PERIODO
	SCT->MATCH[0] = periodo * (FREQ_CLOCK / 1000000); //canal 0 del match es el periodo
	SCT->MATCHREL[0] = periodo * (FREQ_CLOCK / 1000000); //registro de reserva

	//PARTE DEL TIEMPO EN ALTO
	SCT->MATCH[idPWM] = tOn * (FREQ_CLOCK / 1000000); //setear tiempo en alto
	SCT->MATCHREL[idPWM] = tOn * (FREQ_CLOCK / 1000000); //registro de reserva

	SCT->EV[idPWM].STATE = 0xFFFFFFFF; //estado = 0 SIEMPRE porque no uso la MdE
	SCT->EV[idPWM].CTRL = (idPWM << 0) | (1 << 12); // match 1 condition only = solo se dispara el evento cuando contador = Ton, sin entradas externas

	//asociar un evento a poner un 1 o un 0
	SCT->OUT[idPWM - 1].SET = (1 << 0); //el evento 0 pone un 1 en el out
	SCT->OUT[idPWM - 1].CLR = (1 << idPWM); //el evento idPWM pone un 0 en el out

	SCT->OUTPUT &= ~(1 << (idPWM - 1)); //default en 0

	SCT->RES &= ~(0b11 << ((idPWM - 1) * 2)); //limpiar el res
	SCT->RES |= (0b10 << ((idPWM - 1) * 2)); //si ocurre un conflicto queda el estado inactivo
	this->start();
}

void miPWM::stop(void) {
	SCT->CTRL |= (1 << 2); //contador en HALT, queda detenido
}

void miPWM::start(void) {
	SCT->CTRL &= ~(1 << 2); //limpia el HALT, lo pone en RUN
}

void miPWM::setPeriod(uint32_t periodo) {
	this->stop();
	SCT->MATCH[0] = periodo * (FREQ_CLOCK / 1000000);
	SCT->MATCHREL[0] = periodo * (FREQ_CLOCK / 1000000);

	SCT->EV[0].STATE = 0xFFFFFFFF;
	SCT->EV[0].CTRL = (1 << 12);
	this->start();
}

void miPWM::setTimeOn(uint32_t tOn) {
	this->stop();
	SCT->MATCH[idPWM] = tOn * (FREQ_CLOCK / 1000000);
	SCT->MATCHREL[idPWM] = tOn * (FREQ_CLOCK / 1000000);
	this->start();
}
