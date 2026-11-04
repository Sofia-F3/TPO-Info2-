/*
 * portonAuto.cpp
 *
 *  Created on: 23 ago. 2026
 *      Author: sofia
 */

#include "portonAuto.h"
#include "inicializarInfotronic.h"
#include "Timer.h"

#define S1 g_in0
#define S2 g_in1

static uint8_t Reset();
static uint8_t Cero_cero();
static uint8_t Cero_uno();
static uint8_t Uno_uno();
static uint8_t Uno_cero();

enum estados {
	RESET_, CERO_CERO, CERO_UNO, UNO_UNO, UNO_CERO
};

uint8_t (*VectorPorton[])(void) = {Reset,Cero_cero,Cero_uno,Uno_uno,Uno_cero};

int8_t contador = 0;
int8_t autos = 0;

static uint8_t Reset() {
	contador = 0;
	autos = 0;
	return CERO_CERO;
}

static uint8_t Cero_cero() {
	if (contador == -4) {
		autos--;
		contador = 0;
	}
	if (contador == 4) {
		autos++;
		contador = 0;
	}
	if (!S1 && S2) {
		contador++;
		return CERO_UNO;
	}
	if (S1 && !S2) {
		contador--;
		return UNO_CERO;
	}
	return CERO_CERO;
}

static uint8_t Cero_uno () {
	if (S1 && S2) {
		contador++;
		return UNO_UNO;
	}
	if (!S1 && !S2) {
		contador --;
		return CERO_CERO;
	}
	return CERO_UNO;
}

static uint8_t Uno_uno () {
	if (S1 && !S2) {
		contador ++;
		return UNO_CERO;
	}
	if (!S1 && S2) {
		contador--;
		return CERO_UNO;
	}
	return UNO_UNO;
}

static uint8_t Uno_cero() {
	if (!S1 && !S2) {
		contador ++;
		return CERO_CERO;
	}
	if (S1 && S2) {
		contador --;
		return UNO_UNO;
	}
	return UNO_CERO;
}

void MaquinaDeEstadosPorton(void) {
	static uint8_t Estado = RESET_;
	if (Estado > UNO_CERO)
		Estado = RESET_;
	Estado = VectorPorton[Estado]();
}

