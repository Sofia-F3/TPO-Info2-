/*
 * pulsador.h
 *
 *  Created on: 30 jun. 2026
 *      Author: sofia
 */

#ifndef PULSADOR_H_
#define PULSADOR_H_
#include "Gpio.h"

class pulsador:public Gpio {
	const uint8_t port;
	const uint8_t bit;
public:
	enum {
		PRESIONADO, SUELTO
	};
	pulsador(uint8_t, uint8_t);
	bool operator==(bool);
	virtual ~pulsador();
};


#endif /* 1_MODULOS_9_PULSADOR_PULSADOR_H_ */
