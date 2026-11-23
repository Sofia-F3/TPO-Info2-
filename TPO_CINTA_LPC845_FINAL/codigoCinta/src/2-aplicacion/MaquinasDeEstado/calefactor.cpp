/*
 * calefactor.cpp
 *
 *  Created on: 23 ago. 2026
 *      Author: sofia
 */

#include <calefactor.h>
#include "inicializarInfotronic.h"

#define calefactor g_out0

bool fTemperatura;
uint8_t temperatura;
uint8_t tMax;
uint8_t tMin;

uint8_t reset(void);
uint8_t standBy(void);
uint8_t calentando(void);
uint8_t enfriando(void);

enum {
	RESET, ENFRIANDO, STANDBY, CALENTANDO
};

enum {
	off, on
};

uint8_t (*VectorCalefactor[])(void) = {reset,enfriando,standBy,calentando,};

uint8_t reset() {
	calefactor = off;
	temperatura = 65;
	tMax = 70;
	tMin = 68;
	return ENFRIANDO;
}

uint8_t enfriando() {
	if (temperatura <= tMin) {
		calefactor = on;
		return CALENTANDO;
	}
	if (fTemperatura == 1) {
		calefactor = off;
		return STANDBY;
	}
	return ENFRIANDO;
}

uint8_t calentando() {
	if (fTemperatura == 1) {
		calefactor = off;
		return STANDBY;
	}
	if (temperatura >= tMax) {
		calefactor = off;
		return ENFRIANDO;
	}
	return CALENTANDO;
}

uint8_t standBy (){
	if (fTemperatura == 0) {
		return ENFRIANDO;
	}
	return STANDBY;
}

void MaquinaDeEstadosCalefactor ( void )
{
	static uint8_t Estado = RESET;
	if ( Estado > CALENTANDO)
		Estado = RESET;
	Estado = VectorCalefactor[Estado]();
}
