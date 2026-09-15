/*
 * I2C.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include <sensor/I2C/I2C.h>
#include "LPC845.h"
// 5-6-7-8
I2C::I2C(uint8_t numero,uint8_t modo,uint8_t pines[], uint8_t puertos[]):
m_numero(numero),m_modo(modo)
{
	for(uint8_t i=0;i<2;i++)
	{
		m_pin_assign[i]=pines[i];
		m_port[i]=puertos[i];
	}
	SYSCON->SYSAHBCLKCTRL0|=(1<<21)|(1<<22)|(1<<23)|(1<<5)|(1<<7);
	for(uint32_t i=0;i<4;i++)
	{
		SYSCON->FCLKSEL[i+5]=0x01;
	}
	if(m_numero==I2C0_)
	{
		PINENABLE_Config(m_numero, ENABLE);
		PINENABLE_Config(m_numero+1, ENABLE);
	}
	if(m_numero==I2C1_||m_numero==I2C2_||m_numero==I2C2_)
	{
		PINASSIGN_Config(m_numero, m_port[0], m_pin_assign[0]);
		PINASSIGN_Config(m_numero+1, m_port[1], m_pin_assign[1]);
	}
	I2C0->CLKDIV=20;
	I2C1->CLKDIV=20;
	I2C2->CLKDIV=20;
	I2C3->CLKDIV=20;
	if(m_modo)
	{
		SetMaster();
	}else
	{
		SetSlave();
	}
}

void I2C:: SetMaster(void)
{
	if(!m_modo)
	{
		return;
	}
	switch(m_numero)
	{
	case I2C0_:
		I2C0->CFG=1;
	break;
	case I2C1_:
		I2C1->CFG=1;
	break;
	case I2C2_:
		I2C2->CFG=1;
	break;
	case I2C3_:
		I2C3->CFG=1;
	break;
	default:break;
	}
}
void I2C::SetSlave(void){
	if(m_modo)
	{
		return;
	}
	switch(m_numero)
		{
		case I2C0_:
			I2C0->CFG=2;
		break;
		case I2C1_:
			I2C1->CFG=2;
		break;
		case I2C2_:
			I2C2->CFG=2;
		break;
		case I2C3_:
			I2C3->CFG=2;
		break;
		default:break;
		}
}
uint8_t I2C:: startRead(uint32_t direccion,uint8_t registro)
{
	uint8_t valor_leido=0;
	switch (m_numero)
	{
	case I2C0_:
		//envio direccion del esclavo en tipo escritura y escribo start
		I2C0->MSTDAT=(direccion<<1);
		I2C0->MSTCTL=2;
		//espero a que se termine la comunicacion
		while(!(I2C3->INSTAT & 1)){}
		// envio la direccion del registro a leer y continuo
		I2C0->MSTDAT=registro;
		I2C0->MSTCTL=1;
		while(!(I2C3->INSTAT & 1)){}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C0->MSTDAT=(direccion<<1);
		I2C0->MSTCTL=3;
		while(!(I2C3->INSTAT & 1)){}
		valor_leido=I2C0->MSTDAT;
		I2C0->MSTCTL=(1<<2);
	break;
	case I2C1_:
		//envio direccion del esclavo en tipo escritura y escribo start
		I2C1->MSTDAT=(direccion<<1);
		I2C1->MSTCTL=2;
		//espero a que se termine la comunicacion
		while(!(I2C3->INSTAT & 1)){}
		// envio la direccion del registro a leer y continuo
		I2C1->MSTDAT=registro;
		I2C1->MSTCTL=1;
		while(!(I2C3->INSTAT & 1)){}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C1->MSTDAT=(direccion<<1);
		I2C1->MSTCTL=3;
		while(!(I2C3->INSTAT & 1)){}
		valor_leido=I2C1->MSTDAT;
		I2C1->MSTCTL=(1<<2);
	break;
	case I2C2_:
		//envio direccion del esclavo en tipo escritura y escribo start
		I2C2->MSTDAT=(direccion<<1);
		I2C2->MSTCTL=2;
		//espero a que se termine la comunicacion
		while(!(I2C3->INSTAT & 1)){}
		// envio la direccion del registro a leer y continuo
		I2C2->MSTDAT=registro;
		I2C2->MSTCTL=1;
		while(!(I2C3->INSTAT & 1)){}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C2->MSTDAT=(direccion<<1);
		I2C2->MSTCTL=3;
		while(!(I2C3->INSTAT & 1)){}
		valor_leido=I2C2->MSTDAT;
		I2C2->MSTCTL=(1<<2);
	break;
	case I2C3_:
		//envio direccion del esclavo en tipo escritura y escribo start
		I2C3->MSTDAT=(direccion<<1);
		I2C3->MSTCTL=2;
		//espero a que se termine la comunicacion
		while(!(I2C3->INSTAT & 1)){}
		// envio la direccion del registro a leer y continuo
		I2C3->MSTDAT=registro;
		I2C3->MSTCTL=1;
		while(!(I2C3->INSTAT & 1)){}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C3->MSTDAT=(direccion<<1);
		I2C3->MSTCTL=3;
		while(!(I2C3->INSTAT & 1)){}
		valor_leido=I2C3->MSTDAT;
		I2C3->MSTCTL=(1<<2);
	break;
	default:break;
	}
	return valor_leido;
}

void I2C::startWrite(uint32_t direccion,uint8_t registro,uint32_t valor_escritura)
{
	switch (m_numero)
		{
		case I2C0_:
			//envio direccion del esclavo en tipo escritura y escribo start
			I2C0->MSTDAT=(direccion<<1);
			I2C0->MSTCTL=2;
			//espero a que se termine la comunicacion
			while(!(I2C3->INSTAT & 1)){}
			// envio la direccion del registro a leer y continuo
			I2C0->MSTDAT=registro;
			I2C0->MSTCTL=1;
			while(!(I2C3->INSTAT & 1)){}
			//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
			I2C0->MSTDAT=valor_escritura;
			I2C0->MSTCTL=4;
		break;
		case I2C1_:
			//envio direccion del esclavo en tipo escritura y escribo start
			I2C1->MSTDAT=(direccion<<1);
			I2C1->MSTCTL=2;
			//espero a que se termine la comunicacion
			while(!(I2C3->INSTAT & 1)){}
			// envio la direccion del registro a leer y continuo
			I2C1->MSTDAT=registro;
			I2C1->MSTCTL=1;
			while(!(I2C3->INSTAT & 1)){}
			//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
			I2C1->MSTDAT=valor_escritura;
			I2C1->MSTCTL=4;		break;
		case I2C2_:
			//envio direccion del esclavo en tipo escritura y escribo start
			I2C2->MSTDAT=(direccion<<1);
			I2C2->MSTCTL=2;
			//espero a que se termine la comunicacion
			while(!(I2C3->INSTAT & 1)){}
			// envio la direccion del registro a leer y continuo
		    I2C2->MSTDAT=registro;
		    I2C2->MSTCTL=1;
		    while(!(I2C3->INSTAT & 1)){}
		    //vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		    I2C2->MSTDAT=valor_escritura;
		    I2C2->MSTCTL=4;
		break;
		case I2C3_:
			//envio direccion del esclavo en tipo escritura y escribo start
			I2C3->MSTDAT=(direccion<<1);
			I2C3->MSTCTL=2;
			//espero a que se termine la comunicacion
			while(!(I2C3->INSTAT & 1)){}
			// envio la direccion del registro a leer y continuo
			I2C3->MSTDAT=registro;
			I2C3->MSTCTL=1;
			while(!(I2C3->INSTAT & 1)){}
			//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
			I2C3->MSTDAT=(direccion<<1);
			I2C3->MSTCTL=1;
			while(!(I2C3->INSTAT & 1)){}
		    //vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		    I2C2->MSTDAT=valor_escritura;
		    I2C2->MSTCTL=4;
		break;
		default:break;
		}

}

I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

