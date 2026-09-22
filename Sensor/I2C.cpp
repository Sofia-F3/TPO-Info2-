/*
 * I2C.cpp
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#include "I2C.h"
#include "LPC845.h"
#include "Gpio.h"
// 5-6-7-8
I2C::I2C(uint8_t numero,uint8_t modo,uint8_t pines[], uint8_t puertos[]):
m_numero(numero),m_modo(modo)
{
		for(uint8_t i=0;i<2;i++)
	{
		m_pin_assign[i]=pines[i];
		m_port[i]=puertos[i];
	}
	//PINENABLE_Config(PE_ADC_1, I2C::DISABLE);
	uint32_t indice_SDA=IOCON_PIO[m_port[0]][m_pin_assign[0]];
	uint32_t indice_SCL=IOCON_PIO[m_port[1]][m_pin_assign[1]];
	//abilito los clocks de los I2C y la SWM
	SYSCON->SYSAHBCLKCTRL0|=(1<<21)|(1<<22)|(1<<23)|(1<<5)|(1<<7);
	//Hago un reset de todos los bloques del I2C
	SYSCON->PRESETCTRL0&=~(1<<5)&~(1<<21)&~(1<<22)&~(1<<23);
	SYSCON->PRESETCTRL0|=(1<<5)|(1<<21)|(1<<22)|(1<<23);
	IOCON->PIO[indice_SDA]&= ~0x418;
	IOCON->PIO[indice_SCL]&=~0x418;
	//Pongo los pines elegidos en PULL-UP y en OPEN-DRAIN
	IOCON->PIO[indice_SDA]|=0x410;
	IOCON->PIO[indice_SCL]|=0x410;
	//Elijo el clock del sistema que es 12MHz
	for(uint32_t i=0;i<4;i++)
	{
		SYSCON->FCLKSEL[i+5]=0x01;
	}
	//Configuro en la swm los pines elegidos
	if(m_numero==I2C0_)
	{
		PINENABLE_Config(m_numero, ENABLE);
		PINENABLE_Config(m_numero+1, ENABLE);
	}
	if(m_numero==I2C1_ || m_numero==I2C2_ || m_numero==I2C3_)
	{
		PINASSIGN_Config(m_numero, m_port[0], m_pin_assign[0]);
		PINASSIGN_Config(m_numero+1, m_port[1], m_pin_assign[1]);
	}
	// division del clock, SCL high time (in I2C function clocks) = (CLKDIV + 1) * (MSTSCLHIGH + 2)
	//SCL low time (in I2C function clocks) = (CLKDIV + 1) * (MSTSCLLOW + 2)
	I2C0->CLKDIV=29;
	I2C1->CLKDIV=29;
	I2C2->CLKDIV=29;
	I2C3->CLKDIV=29;
	// tomo MSTSCLLOW Y MSTSCLHIGH como el minimo posible que es 2, poniendo un 0 en ambos
	I2C0->MSTTIME=0;
	I2C1->MSTTIME=0;
	I2C2->MSTTIME=0;
	I2C3->MSTTIME=0;
	if(m_modo)
	{
		SetMaster();
	}else
	{
		SetSlave();
	}
	//SYSCON->SYSAHBCLKCTRL0&=~(1<<7);
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
		I2C0->INTENCLR=0x51;
	break;
	case I2C1_:
		I2C1->CFG=1;
		I2C1->INTENCLR=0x51;
	break;
	case I2C2_:
		I2C2->CFG=1;
		I2C2->INTENCLR=0x51;
	break;
	case I2C3_:
		I2C3->CFG=1;
		I2C3->INTENCLR=0x51;
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
		while(!(I2C0->STAT & 1));
		I2C0->MSTDAT=(direccion<<1);
		I2C0->MSTCTL=3;
		//espero a que se termine la comunicacion
		while(!(I2C0->STAT & 1));
		if((I2C0->STAT&14)==0x6)
		{
			I2C0->MSTCTL=4;
			break;
		}
		// envio la direccion del registro a leer y continuo
		I2C0->MSTDAT=registro;
		I2C0->MSTCTL=1;
		while(!(I2C0->STAT & 1)){}
		if((I2C0->STAT&14)==0x6)
		{
			I2C0->MSTCTL=4;
			break;
		}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C0->MSTDAT=(direccion<<1)|1;
		I2C0->MSTCTL=3;
		while(!(I2C0->STAT & 1)){}
		if((I2C0->STAT&14)==0x6)
		{
			I2C0->MSTCTL=4;
			break;
		}
		// mando continuar para que mande el byte del registro
		I2C0->MSTCTL=1;
		while(!(I2C0->STAT & 1));
		if((I2C0->STAT&14)==0x6)
		{
			I2C0->MSTCTL=4;
			break;
		}
		//Guardo el valor que llega del sensor
		valor_leido=I2C0->MSTDAT;
		I2C0->MSTCTL=1;
		while(!(I2C0->STAT & 1)){}
		if((I2C0->STAT&14)==0x6)
		{
			I2C0->MSTCTL=4;
			break;
		}
		//Stop de la comunicacion
		I2C0->MSTCTL=4;
		while(!(I2C0->STAT & 1)){}
	break;
	case I2C1_:
		//envio direccion del esclavo en tipo escritura y escribo start
		while(!(I2C1->STAT & 1));
		I2C1->MSTDAT=(direccion<<1);
		I2C1->MSTCTL=3;
		//espero a que se termine la comunicacion
		while(!(I2C1->STAT & 1));
		if((I2C1->STAT&14)==0x6)
		{
			I2C1->MSTCTL=4;
			break;
		}
		// envio la direccion del registro a leer y continuo
		I2C1->MSTDAT=registro;
		I2C1->MSTCTL=1;
		while(!(I2C1->STAT & 1)){}
		if((I2C1->STAT&14)==0x6)
		{
			I2C1->MSTCTL=4;
			break;
		}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C1->MSTDAT=(direccion<<1)|1;
		I2C1->MSTCTL=3;
		while(!(I2C1->STAT & 1)){}
		if((I2C1->STAT&14)==0x6)
		{
			I2C1->MSTCTL=4;
			break;
		}
		// mando continuar para que mande el byte del registro
		I2C1->MSTCTL=1;
		while(!(I2C1->STAT & 1));
		if((I2C1->STAT&14)==0x6)
		{
			I2C1->MSTCTL=4;
			break;
		}
		valor_leido=I2C1->MSTDAT;
		I2C1->MSTCTL=1;
		while(!(I2C1->STAT & 1)){}
		if((I2C1->STAT&14)==0x6)
		{
			I2C1->MSTCTL=4;
			break;
		}
		I2C1->MSTCTL=4;
		while(!(I2C1->STAT & 1)){}
	break;
	case I2C2_:
		//envio direccion del esclavo en tipo escritura y escribo start
		//envio direccion del esclavo en tipo escritura y escribo start
		while(!(I2C2->STAT & 1));
		I2C2->MSTDAT=(direccion<<1);
		I2C2->MSTCTL=3;
		//espero a que se termine la comunicacion
		while(!(I2C2->STAT & 1));
		if((I2C2->STAT&14)==0x6)
		{
			I2C2->MSTCTL=4;
			break;
		}
		// envio la direccion del registro a leer y continuo
		I2C2->MSTDAT=registro;
		I2C2->MSTCTL=1;
		while(!(I2C2->STAT & 1)){}
		if((I2C2->STAT&14)==0x6)
		{
			I2C2->MSTCTL=4;
			break;
		}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C2->MSTDAT=(direccion<<1)|1;
		I2C2->MSTCTL=3;
		while(!(I2C2->STAT & 1)){}
		if((I2C2->STAT&14)==0x6)
		{
			I2C2->MSTCTL=4;
			break;
		}
		// mando continuar para que mande el byte del registro
		I2C2->MSTCTL=1;
		while(!(I2C2->STAT & 1));
		if((I2C2->STAT&14)==0x6)
		{
			I2C2->MSTCTL=4;
			break;
		}
		valor_leido=I2C2->MSTDAT;
		I2C2->MSTCTL=1;
		while(!(I2C2->STAT & 1)){}
		if((I2C2->STAT&14)==0x6)
		{
			I2C2->MSTCTL=4;
			break;
		}
		I2C2->MSTCTL=4;
		while(!(I2C2->STAT & 1)){}
	break;
	case I2C3_:
		//envio direccion del esclavo en tipo escritura y escribo start
		//envio direccion del esclavo en tipo escritura y escribo start
		while(!(I2C3->STAT & 1));
		I2C3->MSTDAT=(direccion<<1);
		I2C3->MSTCTL=3;
		//espero a que se termine la comunicacion
		while(!(I2C3->STAT & 1));
		if((I2C3->STAT&14)==0x6)
		{
			I2C3->MSTCTL=4;
			break;
		}
		// envio la direccion del registro a leer y continuo
		I2C3->MSTDAT=registro;
		I2C3->MSTCTL=1;
		while(!(I2C3->STAT & 1)){}
		if((I2C3->STAT&14)==0x6)
		{
			I2C3->MSTCTL=4;
			break;
		}
		//vuelvo a enviar direccion del esclavo pero en tipo lectura y start y continuo
		I2C3->MSTDAT=(direccion<<1)|1;
		I2C3->MSTCTL=3;
		while(!(I2C3->STAT & 1)){}
		if((I2C3->STAT&14)==0x6)
		{
			I2C3->MSTCTL=4;
			break;
		}
		// mando continuar para que mande el byte del registro
		I2C3->MSTCTL=1;
		while(!(I2C3->STAT & 1));
		if((I2C3->STAT&14)==0x6)
		{
			I2C3->MSTCTL=4;
			break;
		}
		valor_leido=I2C3->MSTDAT;
		I2C3->MSTCTL=1;
		while(!(I2C3->STAT & 1)){}
		if((I2C3->STAT&14)==0x6)
		{
			I2C3->MSTCTL=4;
			break;
		}
		I2C3->MSTCTL=4;
		while(!(I2C3->STAT & 1)){}
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

			while(!(I2C0->STAT & 1));
			if((I2C0->STAT&14)==0)
			{//envio direccion del esclavo en tipo escritura y escribo start
			I2C0->MSTDAT&=~0xFF;
			I2C0->MSTDAT=(direccion)<<1;
			I2C0->MSTCTL=3;
			}
			//espero a que se termine la comunicacion
			while(!(I2C0->STAT & 1));
			if((I2C0->STAT&14)==0x6)
			{
				I2C0->MSTCTL=4;
				break;
			}
			if((I2C0->STAT&14)==0x4){
			// envio la direccion del registro a escribir y continuo
			I2C0->MSTDAT=registro;
			I2C0->MSTCTL=1;
			while(!(I2C0->STAT & 1));	//escribo en la zona de dato lo que hay que escribir en el registro y termino la comunicacion
			if((I2C0->STAT&14)==0x6)
			{
				I2C0->MSTCTL=4;
				break;
			}
			if((I2C0->STAT&14)==0x4)
			{
			I2C0->MSTDAT=valor_escritura;
			I2C0->MSTCTL=1;
			while(!(I2C0->STAT & 1));
			if((I2C0->STAT&14)==0x6)
			{
				I2C0->MSTCTL=4;
				break;
			}
			I2C0->MSTCTL=4;
			while(!(I2C0->STAT & 1));
			}
			}
		break;
		case I2C1_:
			while(!(I2C1->STAT & 1));
			if((I2C1->STAT&14)==0)
			{//envio direccion del esclavo en tipo escritura y escribo start
			I2C1->MSTDAT&=~0xFF;
			I2C1->MSTDAT=(direccion)<<1;
			I2C1->MSTCTL=3;
			}
			//espero a que se termine la comunicacion
			while(!(I2C1->STAT & 1));
			if((I2C1->STAT&14)==0x6)
			{
				I2C1->MSTCTL=4;
				break;
			}
			if((I2C1->STAT&14)==0x4){
			// envio la direccion del registro a escribir y continuo
			I2C1->MSTDAT=registro;
			I2C1->MSTCTL=1;
			while(!(I2C1->STAT & 1));
			//Confirmo que me da OK o No
			if((I2C1->STAT&14)==0x6)
			{
				I2C1->MSTCTL=4;
				break;
			}
			if((I2C1->STAT&14)==0x4)
			{
			//Mando el valor a escribir en el registro elegido y continuo
			I2C1->MSTDAT=valor_escritura;
			I2C1->MSTCTL=1;
			while(!(I2C1->STAT & 1));
			if((I2C1->STAT&14)==0x6)
			{
				I2C1->MSTCTL=4;
				break;
			}
			//termino la comunicacion
			I2C1->MSTCTL=4;
			while(!(I2C1->STAT & 1));
			}
			}
			break;
		case I2C2_:
			//envio direccion del esclavo en tipo escritura y escribo start
			while(!(I2C2->STAT & 1));
			if((I2C2->STAT&14)==0)
			{//envio direccion del esclavo en tipo escritura y escribo start
			I2C2->MSTDAT&=~0xFF;
			I2C2->MSTDAT=(direccion)<<1;
			I2C2->MSTCTL=3;
			}
			//espero a que se termine la comunicacion
			while(!(I2C2->STAT & 1));
			if((I2C2->STAT&14)==0x6)
			{
				I2C2->MSTCTL=4;
				break;
			}
			if((I2C2->STAT&14)==0x4){
			// envio la direccion del registro a escribir y continuo
			I2C2->MSTDAT=registro;
			I2C2->MSTCTL=1;
			while(!(I2C2->STAT & 1));	//escribo en la zona de dato lo que hay que escribir en el registro y termino la comunicacion
			if((I2C2->STAT&14)==0x6)
			{
				I2C2->MSTCTL=4;
				break;
			}
			if((I2C2->STAT&14)==0x4)
			{
			//Mando el valor a escribir en el registro elegido y continuo
			I2C2->MSTDAT=valor_escritura;
			I2C2->MSTCTL=1;
			while(!(I2C2->STAT & 1));
			if((I2C2->STAT&14)==0x6)
			{
				I2C2->MSTCTL=4;
				break;
			}
			I2C2->MSTCTL=4;
			while(!(I2C2->STAT & 1));
			}
			}
		break;
		case I2C3_:
			//envio direccion del esclavo en tipo escritura y escribo start
			while(!(I2C3->STAT & 1));
			if((I2C3->STAT&14)==0)
			{//envio direccion del esclavo en tipo escritura y escribo start
			I2C3->MSTDAT&=~0xFF;
			I2C3->MSTDAT=(direccion)<<1;
			I2C3->MSTCTL=3;
			}
			//espero a que se termine la comunicacion
			while(!(I2C3->STAT & 1));
			if((I2C3->STAT&14)==0x6)
			{
				I2C3->MSTCTL=4;
				break;
			}
			if((I2C3->STAT&14)==0x4){
			// envio la direccion del registro a escribir y continuo
			I2C3->MSTDAT=registro;
			I2C3->MSTCTL=1;
			while(!(I2C3->STAT & 1));	//escribo en la zona de dato lo que hay que escribir en el registro y termino la comunicacion
			if((I2C3->STAT&14)==0x6)
			{
				I2C3->MSTCTL=4;
				break;
			}
			if((I2C3->STAT&14)==0x4)
			{
			//Mando el valor a escribir en el registro elegido y continuo
			I2C3->MSTDAT=valor_escritura;
			I2C3->MSTCTL=1;
			while(!(I2C3->STAT & 1));
			if((I2C3->STAT&14)==0x6)
			{
				I2C3->MSTCTL=4;
				break;
			}
			I2C3->MSTCTL=4;
			while(!(I2C3->STAT & 1));
			}
			}
		break;
		default:break;
		}
}

I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

