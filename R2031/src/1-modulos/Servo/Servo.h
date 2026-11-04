/*
 * Servo.h
 *
 *  Created on: 20 sep. 2026
 *      Author: sofia
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "miPWM.h"

class Servo: public miPWM {
private:
	uint8_t m_angulo;
public:
	Servo(uint8_t, uint8_t, uint8_t);
	void setAngulo(uint8_t);
	Servo& operator=(uint8_t);
};


#endif /* SERVO_H_ */
