/*
 * Led.h
 *
 *  Created on: 20 jun 2026
 *      Author: martina
 */

#ifndef MODULOS_5_LED_LED_H_
#define MODULOS_5_LED_LED_H_
#include "Gpio.h"
#include "perifericotemporizado.h"
#include "tipos.h"

class Led :public PerifericoTemporizado {
private:
	Gpio buffer;
	uint32_t ticks;
	__IO uint8_t m_estado;
	uint32_t m_SemiPeriodo;
public:
	enum estados{
		OFF,ON,BLINK
	};
	enum Vel{
		RAPIDO=100,MEDIO=1000,LENTO=10000
	};
	Led(Gpio& g_led);
	void On(void);
	void Off(void);
	void Blink(void);
	void SemiPeriodo(uint32_t periodo);
	void HandlerDelPeriferico(void);
	virtual ~Led();
};

#endif /* MODULOS_5_LED_LED_H_ */
