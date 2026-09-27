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
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** OBJETOS GLOBALES PUBLICOS
 *********************************************************************************************************************************/

// EXPANCIONES																				  EXPANSION 1
Gpio g_expansion0(  Gpio::PORT1 ,   8 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led7 en EXPANSION1
Gpio g_expansion1(  Gpio::PORT1 ,   7 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led6 en EXPANSION1
Gpio g_expansion2(  Gpio::PORT1 ,   6 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led0 en EXPANSION1
Gpio g_expansion3(  Gpio::PORT1 ,  20 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led1 en EXPANSION1
Gpio g_expansion4(  Gpio::PORT1 ,  21 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led2 en EXPANSION1
Gpio g_expansion5(  Gpio::PORT1 ,  16 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led3 en EXPANSION1
Gpio g_expansion6(  Gpio::PORT1 ,  18 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led4 en EXPANSION1
Gpio g_expansion7(  Gpio::PORT0 ,  30 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH );	// Led5 en EXPANSION1

//!< BUZZER
Gpio g_buzzer( Gpio::PORT0 ,  9 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::LOW );

Gpio g_led1(Gpio::PORT1,12,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH);
Gpio g_led0(Gpio::PORT0,28,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH);
Gpio g_led2(Gpio::PORT1,13,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH);

Gpio *VectorDeLeds[] = { &g_led0 , &g_led1 , &g_led2 };

Led g_L0( 0 , CallbackLedsGpio ) ;
Led g_L1( 1 , CallbackLedsGpio ) ;
Led g_L2( 2 , CallbackLedsGpio ) ;

// PULSADORES
Gpio g_pulsador0 ( Gpio::PORT1 ,  10 , Gpio::PULLUP ,  Gpio::INPUT , Gpio::LOW );
Gpio g_pulsador1 ( Gpio::PORT0 ,  27 , Gpio::PULLUP ,  Gpio::INPUT , Gpio::LOW );
Gpio g_pulsador2 ( Gpio::PORT0 ,   8 , Gpio::PULLUP ,  Gpio::INPUT , Gpio::LOW );
Gpio g_pulsador3 ( Gpio::PORT0 ,  31 , Gpio::PULLUP ,  Gpio::INPUT , Gpio::LOW );
Gpio *g_pulsadores[] = {&g_pulsador0 , &g_pulsador1, &g_pulsador2, &g_pulsador3 , nullptr};
Teclado g_Teclado(g_pulsadores);

//!< SALIDAS DIGITALES - RELAYS
DigitalOutputs g_relay0( Gpio::PORT1 , 14 , Gpio::PUSHPULL ,  Gpio::HIGH , Gpio::OFF);
DigitalOutputs g_relay1( Gpio::PORT0 , 25 , Gpio::PUSHPULL ,  Gpio::HIGH , Gpio::OFF);
DigitalOutputs g_relay2( Gpio::PORT0 , 15 , Gpio::PUSHPULL ,  Gpio::HIGH , Gpio::OFF);
DigitalOutputs g_relay3( Gpio::PORT1 ,  4 , Gpio::PUSHPULL ,  Gpio::HIGH , Gpio::OFF);

//!< ENTRADAS DIGITALES
DigitalInputs	g_in0(Gpio::PORT0, 23, Gpio::PULLUP, Gpio::LOW );
DigitalInputs	g_in1(Gpio::PORT1, 17, Gpio::PULLUP, Gpio::LOW );
DigitalInputs	g_in2(Gpio::PORT0, 17, Gpio::PULLUP, Gpio::LOW );

// segmentos - uC_segmentos---------------------------------------------------------
Gpio g_segmento_a(  Gpio::PORT1,18,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_b(  Gpio::PORT0,18,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_c(  Gpio::PORT0,20,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_d(  Gpio::PORT0,22,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_e(  Gpio::PORT0,26,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_f(  Gpio::PORT1,19,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_g(  Gpio::PORT1, 5,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );
Gpio g_segmento_dp( Gpio::PORT0,19,Gpio::PUSHPULL,Gpio::OUTPUT,Gpio::HIGH );

uint8_t TablaDigitosBCD7seg[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
Gpio *g_uC_segmentos[] = { &g_segmento_a,&g_segmento_b,&g_segmento_c,&g_segmento_d,&g_segmento_e,&g_segmento_f,&g_segmento_g,&g_segmento_dp,nullptr};
uC_Segmentos g_uCSegmentos(g_uC_segmentos,TablaDigitosBCD7seg);

// digitos - uC_barrido -------------------------------------------------------------
Gpio g_dgt0( Gpio::PORT1 , 16 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_dgt1( Gpio::PORT1 , 21 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_dgt2( Gpio::PORT1 , 20 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_dgt3( Gpio::PORT1 ,  6 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_dgt4( Gpio::PORT1 ,  7 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio g_dgt5( Gpio::PORT1 ,  8 , Gpio::PUSHPULL , Gpio::OUTPUT , Gpio::HIGH );
Gpio *g_uC_digitos[] = { &g_dgt0,&g_dgt1,&g_dgt2,&g_dgt3,&g_dgt4,&g_dgt5};
uC_Barrido g_uCBarrido( g_uC_digitos );

GrupoDeDigitos Grupos[]=
{
	{ 0 , 3 },
	{ 3 , 3 },
	{-1 , -1 }
};

Display7Segmentos g_Display( &g_uCSegmentos , &g_uCBarrido , Grupos );

Gpio led0( Gpio::PORT1 , 0 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH);
Gpio led1( Gpio::PORT1 , 1 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH);
Gpio led2( Gpio::PORT1 , 2 , Gpio::PUSHPULL ,  Gpio::OUTPUT , Gpio::HIGH);
Adc adc0(0, Adc::PROMEDIO);

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

void InicializarInfotronic ( void )
{
	Inicializar_PLL( );

	g_expansion7.ClrPin( );  //0
	g_expansion6.ClrPin( );	 //1
	g_expansion0.ClrPin( );  //2
	g_expansion1.ClrPin( );  //3
	g_expansion2.ClrPin( );  //4
	g_expansion3.ClrPin( );  //5
	g_expansion4.ClrPin( );  //6
	g_expansion5.ClrPin( );  //7

	g_buzzer.ClrPin( );

	g_relay0.clr();
	g_relay1.clr();
	g_relay2.clr();
	g_relay3.clr();

	SysTick_InstalarCallBack( Sheduller );
	SysTick_Inicializar(1);
}

void CallbackLedsGpio ( uint8_t Id , Led::led_t Estado )
{
	if (Id >= 0 && Id < ( sizeof (VectorDeLeds) / sizeof (Gpio*)))
	{
		if ( Estado )
			VectorDeLeds[ Id ]->SetPin();
		else
			VectorDeLeds[ Id ]->ClrPin();
		}
}
