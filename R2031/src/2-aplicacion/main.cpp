/*
 ===============================================================================
 Name        : main.c
 Author      : Ing.Marcelo Trujillo
 Description : Prueba Expansion 1
 ===============================================================================
 */
#include "inicializarInfotronic.h"

int main(void) {
	InicializarInfotronic();
	g_out2 = 0;
	g_out1 = 0;
	g_out0 = 0;

	Gpio rele(Gpio::PORT0, 22, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);

//	Gpio bot1(Gpio::PORT0, 8, Gpio::PULLUP, Gpio::INPUT, Gpio::HIGH);
//	Gpio bot2(Gpio::PORT0, 9, Gpio::PULLUP, Gpio::INPUT, Gpio::HIGH);

	Servo miServo1(0, 0, 8);
	Servo miServo2(0, 0, 9);

	uint32_t max_angulo = 180;

	while (1) {
		if (g_in0 == 1) {
			rele = 1;
			g_out1 = 1;
			miServo1 = max_angulo;
			miServo2 = max_angulo;
		} else {
			rele = 0;
			g_out1 = 0;
			miServo1 = 0;
			miServo2 = 0;
		}
	}

}
