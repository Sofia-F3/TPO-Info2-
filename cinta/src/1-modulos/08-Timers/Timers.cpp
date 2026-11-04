/*
 * Timers.cpp
 *
 *  Created on: 20 jun 2026
 *      Author: martina
 */

#include "Timers.h"

Timers::Timers(uint8_t cantidad) {

	cant=cantidad;
	Vector_Timers=new Timer[cant];
	Indice=0;
}
Timers& Timers::operator<<(Timer& Temporizador)
{
	if(cant<Indice)
	{
		return *this;
	}
	this->Vector_Timers[Indice]=Temporizador;
	Indice++;
	return *this;

}

Timer& Timers::operator [](uint8_t index)
{
	if(Indice<index)
	{
		return Vector_Timers[cant-1];
	}
	return Vector_Timers[index];
}

Timers::~Timers() {
	delete[] Vector_Timers;
}

