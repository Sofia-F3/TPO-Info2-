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
#include <1-modulos/10-LCD/Lcd.h>
#include <1-modulos/miServo/Servo.h>
#include <1-modulos/sensorColor/Color/SensorColor.h>
#include <1-modulos/sensorColor/I2C/I2C.h>
#include "Timer.h"
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "dr_pll.h"
#include "Gpio.h"
#include "systick.h"
#include "led.h"
#include "intext.h"
#include "Timers.h"
#include "pulsador.h"
#include "display7Segmentos.h"
#include "Teclado.h"
#include "adc.h"
#include "dac.h"
#include "Uart.h"
#include "miPWM.h"
#include "miDAC.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	F0		5
#define 	F1		4
#define 	F2		3
#define 	F3		2
#define 	F4		1
#define 	F5		0

extern volatile uint8_t Start;
extern volatile uint8_t Parada;
extern volatile uint8_t Paso;
extern volatile uint8_t control;
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// Entradas digitales
extern Gpio g_in0;
extern Gpio g_in1;
extern Gpio g_in2;

// Salidas digitales
extern Gpio g_out0 ;
extern Gpio g_out1 ;
extern Gpio g_out2 ;
extern led lVerde;
extern led lRojo;
extern led lAzul;

// segmentos - uC_segmentos
extern Gpio g_segmento_a;
extern Gpio g_segmento_b;
extern Gpio g_segmento_c;
extern Gpio g_segmento_d;
extern Gpio g_segmento_e;
extern Gpio g_segmento_f;
extern Gpio g_segmento_g;
extern Gpio g_segmento_dp;
extern Gpio *g_uC_segmentos[];
extern uint8_t TablaDigitosBCD7seg[];
extern uC_Segmentos g_uCSegmentos;
extern Gpio g_dgt0;
extern Gpio g_dgt1;
extern Gpio g_dgt2;
extern Gpio g_dgt3;
extern Gpio g_dgt4;
extern Gpio g_dgt5;
extern Gpio *g_uC_digitos[];
extern uC_Barrido g_uCBarrido;
extern GrupoDeDigitos Grupos[];
extern Display7Segmentos g_Display;
extern Display7Segmentos display7Segmentos;
extern Teclado g_Teclado;
extern Uart uart0,uart1;
extern Lcd miLCD;
extern Timer espera;
void Wait(void);
void Emergencia(void);
extern SensorColor Sensor;

/***********************************************************************************************************************************
 *** PROTOTIPOS GLOBALES
 **********************************************************************************************************************************/
void InicializarInfotronic ( void ) ;

#endif /* INICIALIZAR_H_ */
