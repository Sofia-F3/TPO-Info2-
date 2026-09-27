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
#include "dr_pll.h"
#include "Gpio.h"
#include "systick.h"
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "Led.h"
#include "uC_Segmentos.h"
#include "uC_Barrido.h"
#include "Teclado.h"
#include "gruposdedigitos.h"
#include "display7Segmentos.h"
#include "intext.h"
#include "Adc.h"

using namespace std;

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

// EXPANCIONES				   EXPANSION 1
extern Gpio g_expansion0 ;	//    Led7
extern Gpio g_expansion1 ;	//    Led6
extern Gpio g_expansion2 ;	//    Led0
extern Gpio g_expansion3 ;	//    Led1
extern Gpio g_expansion4 ;	//    Led2
extern Gpio g_expansion5 ;	//    Led3
extern Gpio g_expansion6 ;	//    Led4
extern Gpio g_expansion7 ;	//    Led5

// RGB
extern Led g_L0 ;
extern Led g_L1 ;
extern Led g_L2 ;

//!< BUZZER
extern Gpio g_buzzer;

// PULSADORES
extern Gpio g_pulsador0 ;
extern Gpio g_pulsador1 ;
extern Gpio g_pulsador2 ;
extern Gpio g_pulsador3 ;

// SALIDAS DIGITALES - RELAYS
extern DigitalOutputs g_relay0;
extern DigitalOutputs g_relay1;
extern DigitalOutputs g_relay2;
extern DigitalOutputs g_relay3;

//!< ENTRADAS DIGITALES
extern DigitalInputs g_in0;
extern DigitalInputs g_in1;
extern DigitalInputs g_in2;

extern Teclado g_Teclado;
extern Display7Segmentos g_Display;

extern Gpio led0, led1, led2;
extern Adc adc0;
/***********************************************************************************************************************************
 *** PROTOTIPOS GLOBALES
 **********************************************************************************************************************************/
void InicializarInfotronic ( void ) ;
void Sheduller(void);
void CallbackLedsGpio ( uint8_t Id , Led::led_t Estado );
#endif /* INICIALIZAR_H_ */
