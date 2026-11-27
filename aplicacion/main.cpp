/*
 * main.cpp
 *
 *  Created on: 27 sep. 2026
 *      Author: franc
 */

#include "inicializarinfotronic.h"
#include "aplicacion.h"


int main () {

	InicializarInfotronic ();

	uint8_t count_color [3] = {0 , 0, 0};// (ROJO, VERDE, AZUL)
	uint8_t ind_color [2];
	uint8_t estado = CLASIFICACION, color = 0;
	uint8_t mode = APAGADO;
	bool flag_aux = false;

	gpio motor_cinta (); //hay que inicializar lol
	Uart Puerto_serie (Gpio::PORT0, 25, Gpio::PORT0, 24, 0, 9600,	Uart::ocho_bits, Uart::NoParidad, 4, 4); //asigno a los pines involucrados en comunicacion puerto serie como tx y rx

	DigitalInputs boton_on ( 0 , 4 , Gpio::PUSHPULL , Gpio::LOW , MAX_BOUNCE );
	DigitalInputs boton_off ( 0 , 12 , Gpio::PUSHPULL , Gpio::LOW , MAX_BOUNCE );

	SensorColor sensor(); //No se como inicializarlo (?

	servo_config[ 1 ] =  Servo_1_on; //usar enum de sensor color restandole 1
	servo_config[ 2 ] =  Servo_2_on; //sirve para elegir el color que queres para cada servo (puse esos dos pero probalos a gusto)

	while (1) {
		if (boton_on.get())
		{
			mode = ENCENDIDO;
		}
		else if (boton_off.get()) 
		{
			mode = APAGADO;
		}	
		
		switch (mode) {
			case ENCENDIDO:
				motor_cinta.SetPin();
				
		     	if ( flag_aux ) 
				{
					flag_aux = false;
					Puerto_serie.Transmit ( &mode , 4 );//envio modo a la computadora, 4 datos para el formato pero otros 3 no se van a ver
				}
				
				if ( estado == CLASIFICACION && (color = sensor.getcolor()) )
				{		
		  				estado = color;
		  		}
		  		if (estado > CLASIFICACION)
		  		{
		  			if (Servo_1.m_angulo == CERRADO && Servo_2.m_angulo == CERRADO)
		  				Clasific_caja (color);
		  			else if ( timer ) 
		  			{	
		  				timer.TmrEvent ();// se apagan los servos
		  				estado = CLASIFICACION;
		  				count_color [color - 1] ++;
		  			}
		  		}
				break;
			case APAGADO:
				motor_cinta.ClrPin();
				Servos_off();		
				if ( !flag_aux ) 
				{
					flag_aux = true;
					Puerto_serie.Transmit ( &mode , 1 );//envio datos a la computadora para comunicarle que no puede asignar
					Puerto_serie.Transmit ( count_color , 3 );//envio conteo hecho
				}

				if ( Puerto_serie.Message ( ind_color, 2) ) 
				{
					for (int i = 0; i < 3; i++)
						Servo_config [i] = Dejar_pasar;//el que no fue asignado, quedara como "Dejar_pasar"
					
					Servo_config[ ind_color [0] - 1] =  Servo_1_on;
					Servo_config[ ind_color [1] - 1] =  Servo_2_on;
				}
				break;
		}
	}
	return 0;
}

