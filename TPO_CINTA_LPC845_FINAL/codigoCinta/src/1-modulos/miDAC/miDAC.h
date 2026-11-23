/*
 * miDAC.h
 *
 *  Created on: 22 oct. 2026
 *      Author: sofia
 */

#ifndef MIDAC_H_
#define MIDAC_H_

#include <LPC845.h>
#include "swm.h"

class miDAC {
	uint8_t m_idDAC;
public:
	enum MODOS {
		MAX, MIN
	};
	miDAC(uint8_t id);
	void setValue(uint16_t valor);
	void setMode(MODOS modo);
};

#endif /* 1_MODULOS_MIDAC_H_ */
