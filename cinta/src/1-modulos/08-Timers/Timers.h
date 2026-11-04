/*
 * Timers.h
 *
 *  Created on: 20 jun 2026
 *      Author: martina
 */

#ifndef _TIMERS_TIMERS_H_
#define _TIMERS_TIMERS_H_
#include "tipos.h"
#include "Timer.h"



class Timers {
private:
	Timer*Vector_Timers;
	uint8_t cant;
public:
	 uint8_t Indice;
	Timers(uint8_t cantidad);
	Timers& operator<<(Timer& Temporizador);
	Timer& operator[](uint8_t indice);
	virtual ~Timers();
};


#endif /* 1_MODULOS_08_TIMERS_TIMERS_H_ */
