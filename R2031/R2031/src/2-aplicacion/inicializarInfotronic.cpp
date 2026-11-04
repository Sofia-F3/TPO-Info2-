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

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/**********************************************************************************
 *** OBJETOS GLOBALES PUBLICOS
 **********************************************************************************/

//!<	ENTRADAS DIGITALES
Gpio g_in0( Gpio::PORT0 , 4 , Gpio::PUSHPULL ,  Gpio::INPUT , Gpio::LOW );
Gpio g_in1( Gpio::PORT0 , 3 , Gpio::PUSHPULL ,  Gpio::INPUT , Gpio::HIGH);

//!< GPIO ENTRADAS SALIDAS DE PROPOSITO GENERAL
Gpio g_out0( Gpio::PORT1 , 0 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );
Gpio g_out1( Gpio::PORT1 , 1 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );
Gpio g_out2( Gpio::PORT1 , 2 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );


void InicializarInfotronic ( void )
{
	Inicializar_PLL( );

	SysTick_InstalarCallBack( Sheduller );
	SysTick_Inicializar(1);
}

