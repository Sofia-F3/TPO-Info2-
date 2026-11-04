/*
 * led.h
 *
 *  Created on: 24 jun 2026
 *      Author: feldman
 */

#ifndef LED_H_
#define LED_H_

#include "Gpio.h"

class led: public Gpio{
	uint8_t m_estado;
	const uint8_t m_puerto;
	const uint8_t m_bit;
public:
	led(uint8_t, uint8_t, uint8_t estado = 0);
	void On(void);
	void Off(void);
	void Blink(void);
	virtual ~led();
};


#endif /* 1_MODULOS_8_LED_LED_H_ */
