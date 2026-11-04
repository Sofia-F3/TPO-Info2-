/*******************************************************************************************************************************//**
 *
 * @file		inicializar.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INICIALIZAR_H_
#define INICIALIZAR_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Timer.h"
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "dr_pll.h"
#include "Gpio.h"
#include "systick.h"
#include "intext.h"
#include "Timers.h"
#include "Led.h"
#include "SensorColor.h"
#include "swm.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	F0		5
#define 	F1		4
#define 	F2		3
#define 	F3		2
#define 	F4		1
#define 	F5		0

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

extern volatile uint8_t Start;
extern volatile uint8_t Parada;
extern volatile uint8_t Paso;
extern volatile uint8_t control;

// Salidas digitales
extern Gpio g_out0 ;
extern Gpio g_out1 ;
extern Gpio g_out2 ;
// Entradas digitales
extern Gpio g_I0;
extern Gpio g_I1;
extern Gpio g_I2;

/*extern Led Led2;
extern Led Led1;
extern Led Led0;
*/
/*extern Timer Rojo;
extern Timer Amarillo;
extern Timer Verde;
extern Timers T;*/
extern Timer espera;
void Wait(void);

extern Intext Int0;

extern DigitalInputs IN0;
extern DigitalInputs IN1;
void Emergencia(void);

extern SensorColor Sensor;

/*
extern Timer T1;
extern Timer T2;
extern Timer T3;
extern Timer T4;
extern Timer T5;
extern Timer T6;
extern Timer T7;
extern Timer T8;*/




/*extern  DigitalOutputs Out0;
extern  DigitalOutputs Out1;
extern  DigitalOutputs Out2;
*/


/***********************************************************************************************************************************
 *** PROTOTIPOS GLOBALES
 **********************************************************************************************************************************/
void InicializarInfotronic ( void ) ;
#endif /* INICIALIZAR_H_ */
