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

int main(void) {
	InicializarInfotronic();
	g_out0 = Gpio::OFF;
	g_out1 = Gpio::OFF;
	g_out2 = Gpio::OFF;

	DigitalInputs bot1(Gpio::PORT0, 1, Gpio::PULLUP, Gpio::LOW);
	DigitalInputs bot0(Gpio::PORT0, 0, Gpio::PULLUP, Gpio::LOW);

	//Gpio rele(Gpio::PORT0, 3, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

	uint32_t color = 0;

	Servo servo1(0, 0, 9);
	Servo servo2(0, 0, 8);

	//g_out0.SetPin();
	//Sensor.White_calibration();
	//espera.TimerStart(1);

	Start = 0;
	Sensor.SetlED(10);
	servo2 = 180;
	servo1 = 180;
	while (1) {

		color = Sensor.Obtener_color();
		Start = 0;
		switch (color) {
		case SensorColor::BLUE:
			g_out0 = Gpio::OFF;
			g_out1 = Gpio::ON;
			g_out2 = Gpio::OFF;
			break;
		case SensorColor::GREEN:
			g_out0 = Gpio::ON;
			g_out1 = Gpio::OFF;
			g_out2 = Gpio::OFF;
			break;
		case SensorColor::RED:
			g_out0 = Gpio::OFF;
			g_out1 = Gpio::OFF;
			g_out2 = Gpio::ON;
			break;
		case SensorColor::NADA:
			g_out0 = Gpio::OFF;
			g_out1 = Gpio::OFF;
			g_out2 = Gpio::OFF;
			break;
		}

		espera.TmrEvent();
	}
}
