/*
 * Timers.h
 *
 *  Created on: 24 jun 2026
 *      Author: feldman
 */

#ifndef TIMERS_H_
#define TIMERS_H
#include "Timer.h"
#define MAX_TIMERS 7

class Timers{
	Timer* timer[MAX_TIMERS];
	uint8_t longitudActual;
public:
	enum ejecucion_t {OK, ERROR};
	Timers();
	uint8_t cantidad();
	Timers& operator<<(Timer*);
	Timer& operator[](uint8_t);
	virtual ~Timers();
};


#endif /* 2_APLICACION_TIMERS_H_ */
