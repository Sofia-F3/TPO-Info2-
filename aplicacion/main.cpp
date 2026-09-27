/*
 * main.cpp
 *
 *  Created on: 27 sep. 2026
 *      Author: franc
 */

#include "aplicacion.h"

int main () {

	inicializarinfotronic ();

	uint8_t count_color [3] = {0 , 0, 0}; // (ROJO, VERDE, AZUL)
	uint8_t estado = 0, color = 0;

	servo_config[0] = NULL;     //configurar color asignado a cada rampa
	servo_config[0] = NULL;		//(inicializo en cero por prevencion)

	timer.TimerStart (DURACION);
	SensorColor sensor(); //No se como inicializarlo (?

	while (1) {
		if (estado == CLASIFICACION) {
			if (color = sensor.getcolor()) {
				estado = color;
			}
		}
		if (estado > CLASIFICACION)
		{
			Clasific_Color ();
			if (timer.TmerEvent ())
			{
				estado = CLASIFICACION;
				count_color [color - 1] ++;
			}
		}
	}
	return 0;
}


