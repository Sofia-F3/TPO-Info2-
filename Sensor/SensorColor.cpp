/*
 * SensorColor.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include "SensorColor.h"



SensorColor::SensorColor(uint8_t pines[],uint8_t puertos[]):Comunicacion(I2C::I2C1_,I2C::MASTER,pines,puertos)
{

}

uint8_t SensorColor::SinObjeto(Color Resultado )
{
	if((Resultado.ROJO+Resultado.AZUL+Resultado.VERDE)>UMBRALM||(Resultado.ROJO+Resultado.AZUL+Resultado.VERDE)<UMBRALm)
	{
		return NADA;
	}
	return 1;
}

uint8_t SensorColor::Obtener_color(void)
{
	Color Resultado;
	Resultado.ROJO=Comunicacion.startRead(DIR_Sensor, DIR_ROJO);
	Resultado.VERDE=Comunicacion.startRead(DIR_Sensor, DIR_VERDE);
	Resultado.AZUL=Comunicacion.startRead(DIR_Sensor, DIR_AZUL);
	if(!SinObjeto(Resultado))
	{
		return NADA;
	}
	if(Resultado.ROJO>Resultado.AZUL && Resultado.ROJO>Resultado.VERDE)
	{
		return RED;
	}
	if(Resultado.AZUL>Resultado.ROJO && Resultado.AZUL>Resultado.VERDE)
	{
		return BLUE;
	}
	if(Resultado.VERDE>Resultado.ROJO && Resultado.VERDE>Resultado.AZUL)
	{
		return GREEN;
	}
	return NADA;
}

void SensorColor::White_calibration()
{
	Comunicacion.startWrite(DIR_Sensor,DIR_CONFIG,1);
}
void SensorColor::SetlED(uint8_t Intensidad)
{
	uint8_t valor=Intensidad<<4;
	Comunicacion.startWrite(DIR_Sensor, DIR_CONFIG,valor);
}

SensorColor::~SensorColor() {
	// TODO Auto-generated destructor stub
}

