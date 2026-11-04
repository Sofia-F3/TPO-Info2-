/*
 * miDAC.cpp
 *
 *  Created on: 22 oct. 2026
 *      Author: sofia
 */

#include "miDAC.h"

miDAC::miDAC(uint8_t id) :
		m_idDAC(id) {
	if (this->m_idDAC == 0 || this->m_idDAC == 1) {
		SYSCON->PDRUNCFG &= ~(1 << (13 + m_idDAC)); //Energizar el dispositivo
		if (this->m_idDAC == 0) {
			SYSCON->SYSAHBCLKCTRL0 |= (1 << 27); //Habilitar DAC0 clock
			PINENABLE_Config(PE_DACOUT0, 1); //habilitar lo de SWM
			IOCON->PIO[0] |= (1 << 16); //P0.17 DACMODE enable
		} else if (this->m_idDAC == 1) {
			SYSCON->SYSAHBCLKCTRL1 |= (1 << 1); //Habilitar DAC1 clock
			PINENABLE_Config(PE_DACOUT1, 1); //habilitar lo de SWM
			IOCON->PIO[50] |= (1 << 16); //P0.29 DACMODE enable
		}
	}
}

void miDAC::setValue(uint16_t valor) { //VA_OUT =VALUE  x ((VREFP) / 1024)
	if (this->m_idDAC == 0) {
		DAC0->CR &= ~(0x3FF << 6);
		DAC0->CR |= (valor << 6);
	} else if (this->m_idDAC == 1) {
		DAC1->CR &= ~(0x3FF << 6);
		DAC1->CR |= (valor << 6);
	}
}

void miDAC::setMode(MODOS modo) {
	if (this->m_idDAC == 0) {
		DAC0->CR |= (modo << 16); //en el bit 16 está lo del BIAS (modo de consumo)
	} else if (this->m_idDAC == 1) {
		DAC1->CR |= (modo << 16);
	}
}
