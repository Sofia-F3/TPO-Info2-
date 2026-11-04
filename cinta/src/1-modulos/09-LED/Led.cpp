/*
 * Led.cpp
 *
 *  Created on: 20 jun 2026
 *      Author: martina
 */

#include "Led.h"
Led::Led( Gpio& g_led):buffer(g_led)
{
	InstalarPerifericoTemporizado(this);
}


Led::~Led() {
	// TODO Auto-generated destructor stub
}

void Led:: On(void)
{
	m_estado=ON;
}
void Led::Off(void)
{
	m_estado=OFF;
}
void Led::SemiPeriodo(uint32_t periodo)
{
	m_SemiPeriodo=periodo;
	if(!ticks)
	{
		ticks=m_SemiPeriodo;
	}
}

void Led:: Blink(void)
{
	m_estado=BLINK;
}

void Led::HandlerDelPeriferico(void)
{
	switch(m_estado)
	{
	case OFF:
		buffer=OFF;
		break;
	case ON:
		buffer=ON;
		break;
	case BLINK:
		ticks--;
		if(!ticks)
		{
			buffer.SetTogglePin();
			ticks=m_SemiPeriodo;
		}
		break;
	default:
		break;
	}
}









