/*
 * Servo.h
 *
 *  Created on: 20 sep. 2026
 *      Author: sofia
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "pwm.h"


class Servo: public Pwm {
private:
	uint32_t m_periodo;
	uint8_t m_angulo;
public:
	Servo(uint8_t, uint32_t, uint8_t, uint8_t , uint8_t , pwm_channel_t);
	void setPeriodo(uint32_t);
	void setAngulo(uint8_t);
	Servo& operator=(uint8_t);
};


#endif /* SERVO_H_ */
