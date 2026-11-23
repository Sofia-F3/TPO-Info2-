/*
 * microbarrido.cpp
 *
 *  Created on: 12 may. 2023
 *      Author: Marcelo
 */

#include "uC_barrido.h"

uC_Barrido::uC_Barrido( Gpio **dgt )
{
	m_indice = 0 ;
	m_dgt = dgt;
	for (uint8_t i = 0 ; i < m_cantidadDeDigitos ; i++)
		m_dgt[i]->ClrPin();
}

void uC_Barrido::SetDigito(void)
{
	for ( uint8_t i = 0 ; i < m_cantidadDeDigitos ; i++ )
		m_dgt[i]->ClrPin();

	m_dgt[m_indice]->SetPin() ;
	m_indice++ ;
	m_indice %= m_cantidadDeDigitos ;
}

void uC_Barrido::SetNDigitos( uint8_t cantidadDeDigitos )
{
	m_cantidadDeDigitos = cantidadDeDigitos;
}

uC_Barrido::~uC_Barrido() {
	// TODO Auto-generated destructor stub
}
