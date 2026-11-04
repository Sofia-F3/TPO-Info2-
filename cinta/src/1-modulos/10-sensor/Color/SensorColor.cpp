/*
 * SensorColor.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include "SensorColor.h"
#include "swm.h"


SensorColor::SensorColor(uint8_t pines[],uint8_t puertos[]):Comunicacion(I2C::I2C1_,I2C::MASTER,pines,puertos)
{

}

uint8_t SensorColor::SinObjeto(Color Resultado )
{
	//Te fijas si la suma de los tres colores es mayor del umbral mayor(cerca del blanco) o menor al umbral bajo(cerca de negro)
	if((Resultado.ROJO+Resultado.AZUL+Resultado.VERDE)>UMBRALM||(Resultado.ROJO+Resultado.AZUL+Resultado.VERDE)<UMBRALm)
	{
		return NADA;
	}
	return 1;
}

uint8_t SensorColor::Obtener_color(void)
{
	Color Resultado;
	static uint8_t rojo=0, verde=0,azul=0;
	//con la variable color guardas los valores de los tres colores
	Resultado.ROJO=Comunicacion.startRead(DIR_Sensor, DIR_ROJO);
	Resultado.VERDE=Comunicacion.startRead(DIR_Sensor, DIR_VERDE);
	Resultado.AZUL=Comunicacion.startRead(DIR_Sensor, DIR_AZUL);
	//si no estan entre los umbrales se toma como nada
	if(!SinObjeto(Resultado))
	{
		return NADA;
	}
	//si el color es el mas grande de los tres toma al color
	if(Resultado.ROJO>Resultado.AZUL && Resultado.ROJO>Resultado.VERDE)
	{
		//se suma 1 a la variable que suma los colores, para que entre despues de 4 mediciones
		rojo++;
		if(rojo==4)
		{
			verde=0;
			azul=0;
			rojo=0;
			return RED;
		}
	}
	if(Resultado.AZUL>Resultado.ROJO && Resultado.AZUL>Resultado.VERDE)
	{
		azul++;
		if(azul==4)
		{
			verde=0;
			azul=0;
			rojo=0;
		return BLUE;
		}
	}

	if(Resultado.VERDE>Resultado.ROJO && Resultado.VERDE>Resultado.AZUL)
	{
		verde++;
		if(verde==4)
		{
			verde=0;
			azul=0;
			rojo=0;
			return GREEN;
		}
	}

	return NADA;
}

void SensorColor::White_calibration()
{
	Comunicacion.startWrite(DIR_Sensor,DIR_CONFIG,0xA1);
}
void SensorColor::SetlED(uint8_t Intensidad)
{
	uint8_t valor=Intensidad<<4;
	Comunicacion.startWrite(DIR_Sensor, DIR_CONFIG,valor);
}

SensorColor::~SensorColor() {
	// TODO Auto-generated destructor stub
}

