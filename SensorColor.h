/*
 * SensorColor.h
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#ifndef _SENSOR_COLOR_SENSORCOLOR_H_
#define _SENSOR_COLOR_SENSORCOLOR_H_

#include "LPC845.h"
#include "I2C.h"
#include "Gpio.h"

#define DIR_Sensor 0x5A
#define DIR_ROJO 0x0C
#define DIR_VERDE 0x0D
#define DIR_AZUL 0x0E
#define DIR_CONFIG 0x10
#define UMBRALM 500
#define UMBRALm 200
extern uint8_t  pines[2];
extern uint8_t puertos[2];


class SensorColor {
private:
	I2C Comunicacion;
	typedef struct{
			uint8_t ROJO;
			uint8_t VERDE;
			uint8_t AZUL;
		}Color;
public:
	enum{
		NADA,RED,GREEN,BLUE
	};
	SensorColor();
	uint8_t Obtener_color(void);
	void White_calibration(void);
	uint8_t SinObjeto( Color Resultado);
	virtual ~SensorColor();
};


#endif /* 1_MODULOS_SENSOR_COLOR_SENSORCOLOR_H_ */
