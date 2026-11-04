/*******************************************************************************************************************************//**
 *
 * @file		inicializar.cpp
 * @brief		Descripcion del modulo
 * @date		5 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "inicializarInfotronic.h"
#include "aplicacion.h"
#include "Timers.h"
#include "swm.h"
#include "I2C.h"


/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/**********************************************************************************
 *** OBJETOS GLOBALES PUBLICOS
 **********************************************************************************/
//!<	ENTRADAS DIGITALES
Gpio g_I0( Gpio::PORT0 , 4 , Gpio::PUSHPULL ,  Gpio::INPUT , Gpio::LOW );
Gpio g_I1( Gpio::PORT0 , 3 , Gpio::PUSHPULL ,  Gpio::INPUT , Gpio::HIGH);

/*
Timer T1 (Timer::DEC,Ev_T1);
Timer T2 (Timer::DEC,Ev_T2);
Timer T3 (Timer::DEC,Ev_T3);
Timer T4 (Timer::DEC,Ev_T4);
Timer T5 (Timer::DEC,Ev_T5);
Timer T6 (Timer::DEC,Ev_T6);
Timer T7 (Timer::DEC,Ev_T7);
Timer T8 (Timer::DEC,Ev_T8);

*//*
Timer Rojo (Timer::SEG,RED);
Timer Amarillo(Timer::SEG,YELLOW);
Timer Verde(Timer::SEG,GREEN);
Timer espera(Timer::DEC,Wait);
Timers T(4);*/
//Timers T(5);
Timer espera(Timer::DEC,Wait);


//!< GPIO ENTRADAS SALIDAS DE PROPOSITO GENERAL
Gpio g_out0( Gpio::PORT1 , 0 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );
Gpio g_out1( Gpio::PORT1 , 1 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH);
Gpio g_out2( Gpio::PORT1 , 2 , Gpio::PUSHPULL,  Gpio::OUTPUT , Gpio::HIGH );
/*
Led Led2(g_out2);
Led Led1(g_out1);
Led Led0(g_out0);*/

volatile uint8_t Start;
volatile uint8_t Parada;
volatile uint8_t Paso;
volatile uint8_t control;
void Wait(void)
{
	Start=1;
	espera.TimerStart(1);
}
/*
void Emergencia(void)
{
	Led0.Off();
	Led1.Off();
	Led2.Off();
	for(int i=0;i<4;i++)
	{
		T[i].TimerStop();
	}
	Start=0;
	Parada=0;
}*/
//Intext Int0(0,Gpio::PORT0,12,Emergencia);

DigitalInputs IN0(Gpio::PORT0,4,Gpio::INACTIVE,Gpio::LOW,MAX_BOUNCE);
//DigitalInputs IN1(Gpio::PORT0,12,0,Gpio::LOW,MAX_BOUNCE);


/*DigitalOutputs Out0(Gpio::PORT1,0,0,Gpio::HIGH,Gpio::OFF);
DigitalOutputs Out1(Gpio::PORT1,1,0,Gpio::HIGH,Gpio::OFF);
DigitalOutputs Out2(Gpio::PORT1,2,0,Gpio::HIGH,Gpio::OFF);
*/


uint8_t  pines[2]={
		29,6
};
uint8_t puertos[2]{
	Gpio::PORT0,Gpio::PORT0
};

SensorColor Sensor(pines,puertos);

void InicializarInfotronic ( void )
{
	Inicializar_PLL( );

	SysTick_InstalarCallBack( Sheduller );
	SysTick_Inicializar(1);
}

