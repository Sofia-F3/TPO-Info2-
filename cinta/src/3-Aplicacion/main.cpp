/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include "inicializarInfotronic.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void)
{
	InicializarInfotronic();
	uint32_t color=0;
	g_out0=Gpio::ON;
	g_out1=Gpio::ON;
	g_out2=Gpio::ON;
	//g_out0.SetPin();
	//Sensor.White_calibration();
	//espera.TimerStart(1);
	Start=0;
	Sensor.SetlED(10);
	while(1)
	{
		/*if(Start==1)
		{*/
			color=Sensor.Obtener_color();
			Start=0;
			switch (color)
			{
			case SensorColor::BLUE:
				g_out0=Gpio::ON;
				g_out1=Gpio::OFF;
				g_out2=Gpio::ON;
			break;
			case SensorColor::GREEN:
				g_out0=Gpio::OFF;
				g_out1=Gpio::ON;
				g_out2=Gpio::ON;
			break;
			case SensorColor::RED:
				g_out0=Gpio::ON;
				g_out1=Gpio::ON;
				g_out2=Gpio::OFF;
			break;
			case SensorColor::NADA:
				/*g_out0=Gpio::ON;
				g_out1=Gpio::ON;
				g_out2=Gpio::ON;*/
			break;
			}

		espera.TmrEvent();
	  }
}
