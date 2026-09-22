/*
 * I2C.h
 *
 *  Created on: 21 ago 2026
 *      Author: martina
 */

#ifndef SENSOR_I2C_I2C_H_
#define SENSOR_I2C_I2C_H_
#include "LPC845.h"
#include "swm.h"


class I2C {
private:
	uint32_t m_numero;
	uint8_t m_modo;
	uint8_t m_pin_assign[2];
	uint8_t m_port[2];
public:
	enum{LECTURA,ESCRITURA};
	enum{SLAVE,MASTER};
	enum{
		I2C0_=PE_I2C0_SDA,I2C1_=PA_I2C1_SDA,I2C2_=PA_I2C2_SDA,I2C3_=PA_I2C3_SDA
	};
	enum{
		DISABLE,ENABLE
	};
	I2C(uint8_t numero,uint8_t modo,uint8_t pines[],uint8_t puertos[]);
	void SetMaster(void);
	void SetSlave(void);
	uint8_t startRead(uint32_t direccion,uint8_t registro);
	void startWrite(uint32_t direccion,uint8_t registro,uint32_t valor_escritura);
	virtual ~I2C();
};


#endif /* 1_MODULOS_SENSOR_I2C_I2C_H_ */
