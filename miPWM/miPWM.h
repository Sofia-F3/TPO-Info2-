/*
 * miPWM.h
 *
 *  Created on: 8 oct. 2026
 *      Author: sofia
 */

#ifndef MIPWM_H_
#define MIPWM_H_

#include <LPC845.h>

class miPWM {
	uint8_t m_port;
	uint8_t m_pin;
	static uint8_t cantServos;
	uint8_t idServo;
public:
	miPWM(uint8_t, uint8_t);
	void inicializar(uint32_t, uint32_t);
	void stop(void);
	void start(void);
	void setPeriod(uint32_t);
	void setTimeOn(uint32_t);
	void SetSwitchMatrizSCTOUT(uint8_t bit, uint8_t port, uint8_t out_number);

};

#endif /* MIPWM_H_ */
