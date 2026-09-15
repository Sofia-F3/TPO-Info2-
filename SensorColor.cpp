/*
 * SensorColor.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include <sensor/Color/SensorColor.h>

uint8_t  pines[2]={
		4,26
};
uint8_t puertos[2]{
	Gpio::PORT0,Gpio::PORT0
};

SensorColor::SensorColor():Comunicacion(I2C::I2C1_,I2C::MASTER,pines,puertos)
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


SensorColor::~SensorColor() {
	// TODO Auto-generated destructor stub
}

