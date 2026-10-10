/*
 * I2C.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include "I2C.h"
#include "LPC845.h"
#include "Gpio.h"

I2C_type*I2CS[]={
		I2C0,I2C1,I2C2,I2C3
};

I2C::I2C(uint8_t numero,uint8_t modo,uint8_t pines[], uint8_t puertos[]):
m_numero(numero),m_modo(modo)
{
		for(uint8_t i=0;i<2;i++)
	{
		m_pin_assign[i]=pines[i];
		m_port[i]=puertos[i];
	}
	m_I2C=I2CS[numero];
	uint32_t indice_SDA=IOCON_PIO[m_port[0]][m_pin_assign[0]];
	uint32_t indice_SCL=IOCON_PIO[m_port[1]][m_pin_assign[1]];
	switch(numero)
	{
	case I2C0_:
		//habilito los clocks del I2C y de la SWM
		SYSCON->SYSAHBCLKCTRL0|=(1<<5)|(1<<7);
		//Hago un reset del I2C
		SYSCON->PRESETCTRL0&=~(1<<5);
		SYSCON->PRESETCTRL0|=(1<<5);
		//Pongo el clock del I2C en el main clock
		SYSCON->FCLKSEL[5]=0x01;
		//habilito los pines especiales del I2C
		PINENABLE_Config(PE_I2C0_SDA, ENABLE);
		PINENABLE_Config(PE_I2C0_SCL, ENABLE);
		//habilito el clock del registro
		m_I2C->CLKDIV=29;
		m_I2C->MSTTIME=0;
	break;
	case I2C1_:
		SYSCON->SYSAHBCLKCTRL0|=(1<<21)|(1<<7);
		SYSCON->PRESETCTRL0&=~(1<<21);
		SYSCON->PRESETCTRL0|=(1<<21);
		SYSCON->FCLKSEL[6]=0x01;
		//Habilito la configuracion de la swm de los pines
		PINASSIGN_Config(PA_I2C1_SDA, m_port[0], m_pin_assign[0]);
		PINASSIGN_Config(PA_I2C1_SCL, m_port[1], m_pin_assign[1]);
		m_I2C->CLKDIV=29;
		m_I2C->MSTTIME=0;
	break;
	case I2C2_:
		SYSCON->SYSAHBCLKCTRL0|=(1<<22)|(1<<7);
		SYSCON->PRESETCTRL0&=~(1<<22);
		SYSCON->PRESETCTRL0|=(1<<22);
		SYSCON->FCLKSEL[7]=0x01;
		PINASSIGN_Config(PA_I2C2_SDA, m_port[0], m_pin_assign[0]);
		PINASSIGN_Config(PA_I2C2_SCL, m_port[1], m_pin_assign[1]);
		m_I2C->CLKDIV=29;
		m_I2C->MSTTIME=0;
	break;
	case I2C3_:
		SYSCON->SYSAHBCLKCTRL0|=(1<<23)|(1<<7);
		SYSCON->PRESETCTRL0&=~(1<<23);
		SYSCON->PRESETCTRL0|=(1<<23);
		SYSCON->FCLKSEL[8]=0x01;
		PINASSIGN_Config(PA_I2C3_SDA, m_port[0], m_pin_assign[0]);
		PINASSIGN_Config(PA_I2C3_SCL, m_port[1], m_pin_assign[1]);
		m_I2C->CLKDIV=29;
		m_I2C->MSTTIME=0;
	break;
	}

	IOCON->PIO[indice_SDA]&= ~0x418;
	IOCON->PIO[indice_SCL]&=~0x418;
	//Pongo los pines elegidos en PULL-UP y en OPEN-DRAIN
	IOCON->PIO[indice_SDA]|=0x410;
	IOCON->PIO[indice_SCL]|=0x410;
	// division del clock, SCL high time (in I2C function clocks) = (CLKDIV + 1) * (MSTSCLHIGH + 2)
	//SCL low time (in I2C function clocks) = (CLKDIV + 1) * (MSTSCLLOW + 2)
	// tomo MSTSCLLOW Y MSTSCLHIGH como el minimo posible que es 2, poniendo un 0 en ambos
	if(m_modo)
	{
		SetMaster();
	}else
	{
		SetSlave();
	}
	SYSCON->SYSAHBCLKCTRL0&=~(1<<7);
}

void I2C::SetMaster(void)
{
	if(!m_modo)
	{
		return;
	}
	m_I2C->CFG=1;
	m_I2C->INTENCLR=0x51;
}


void I2C::SetSlave(void)
{
	if(m_modo)
	{
		return;
	}
	m_I2C->CFG=2;
}

uint8_t I2C::startRead(uint32_t direccion,uint8_t registro)
{
	uint8_t valor_leido;
	//espero a que este en condiciones de empezar la comunicacion
	while(!(m_I2C->STAT & 1));
	//envio la direccion del esclavo como escritura
	m_I2C->MSTDAT=(direccion<<1);
	m_I2C->MSTCTL=3;
	//espero a que vuelva a estar bien
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return 0;
	}
	m_I2C->MSTDAT=registro;
	m_I2C->MSTCTL=1;
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return 0;
	}
	m_I2C->MSTDAT=(direccion<<1)|1;
	m_I2C->MSTCTL=3;
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return 0;
	}
	m_I2C->MSTCTL=5;
	while(!(m_I2C->STAT & 1));
	/*if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return 0;
	}*/
	valor_leido=m_I2C->MSTDAT;
	/*while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return 0;
	}*/
	//m_I2C->MSTCTL=4;
	//while(!(m_I2C->STAT & 1));
	return valor_leido;
}

void I2C::startWrite(uint32_t direccion,uint8_t registro,uint32_t valor_escritura)
{
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0)
	{
		m_I2C->MSTDAT&=~0xFF;
		m_I2C->MSTDAT=(direccion<<1);
		m_I2C->MSTCTL=3;
	}
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return ;
	}
	if((m_I2C->STAT&14)==0x4)
	{
		m_I2C->MSTDAT=registro;
		m_I2C->MSTCTL=1;
	}
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return ;
	}
	if((m_I2C->STAT&14)==0x4)
	{
		m_I2C->MSTDAT=valor_escritura;
		m_I2C->MSTCTL=1;
	}
	while(!(m_I2C->STAT & 1));
	if((m_I2C->STAT&14)==0x6)
	{
		m_I2C->MSTCTL=4;
		return ;
	}
	m_I2C->MSTCTL=4;
	while(!(m_I2C->STAT & 1));
}



I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

