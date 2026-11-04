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
	g_out1 = 1;
	g_out0 = 0;


	Gpio rele(Gpio::PORT0, 22, Gpio::PUSHPULL, Gpio::OUTPUT, Gpio::LOW);


	Servo miServo1(90, 0, 8);
	Servo miServo2(45, 0, 9);
	miServo1 = 45;
	miServo2 = 90;

	while (1) {
		if (g_in0 == 1) {
			rele = 1;
			g_out1 = 1;
		} else {
			rele = 0;
			g_out1 = 0;
		}
	}
}
