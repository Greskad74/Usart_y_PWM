#include "stm32f10x.h"
#include "i2c.h"


void i2c_init(uint8_t i2c_num)
{
		// enable GPIOB clock
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		
		// Enable the alternate functions for pins
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		
		if(i2c_num == 1)
		{
			// enable i2c 1
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		
		// Reset PB6 and PB7
		GPIOB->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_CNF6);
		GPIOB->CRL &= ~(GPIO_CRL_MODE7| GPIO_CRL_MODE6);
		
		// set both PB6 and PB7 as AF Output 50MHz Open-Drain
		GPIOB->CRL |= (GPIO_CRL_MODE6 | GPIO_CRL_MODE7);	// output 50MHz
		GPIOB->CRL |= (GPIO_CRL_CNF6 | GPIO_CRL_CNF7);		// Alternate function open-drain
		
		I2C1->CR1 |= I2C_CR1_SWRST;			// reset I2C peripherals
		I2C1->CR1 &= ~(I2C_CR1_SWRST);	// release the reset
		
		// set the frequency
		I2C1->CR2 = 0x08;	// default
		
		// set the speed of I2C
		I2C1->CCR = I2C_STDMODE;	// standard speed mode
		I2C1->TRISE = 0x09;
		
		// enable the peripheral
		I2C1->CR1 |= I2C_CR1_PE;
	}
	else
	{
			// enable i2c 2
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
		
		// reset PB10 and PB11
		GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_CNF11);
		GPIOB->CRH &= ~(GPIO_CRH_MODE10| GPIO_CRH_MODE11);
		
		// set both PB6 and PB7 as AF Output 50MHz Open-Drain
		GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);	// output 50MHz
		GPIOB->CRH |= (GPIO_CRH_CNF10 | GPIO_CRH_CNF11);		// Alternate function open-drain
		
		I2C2->CR1 |= I2C_CR1_SWRST;			// reset I2C peripherals
		I2C2->CR1 &= ~(I2C_CR1_SWRST);	// release the reset
		
		// set the frequency
		I2C2->CR2 = 0x08;	// default
		
		// set the speed of I2C
		I2C2->CCR = I2C_STDMODE;	// standard speed mode
		I2C2->TRISE = 0x09;
		
		// enable the peripheral
		I2C2->CR1 |= I2C_CR1_PE;
	}

}




void i2c_start(uint8_t i2c_num)
{
	if(i2c_num == 1)
	{
		I2C1->CR1 |= I2C_CR1_START;		// start transmission
		// wait
		while(!(I2C1->SR1 & I2C_SR1_SB)); // wait until ready
	}
	else
	{
		I2C2->CR1 |= I2C_CR1_START;		// start transmission
		// wait
		while(!(I2C2->SR1 & I2C_SR1_SB)); // wait until ready
	}
}



	
void I2C_Data(uint8_t i2c_num, uint8_t data)
{
	if(i2c_num == 1)
	{
		// confirm that TXE = 0 before sending
		while((I2C1->SR1 & I2C_SR1_TXE) == 0);
		I2C1->DR = data; // load the data
		// wait until data is sent
		while((I2C1->SR1 & I2C_SR1_TXE) == 0);
		// clear by reading SR1
	}
	else
	{
		// confirm that TXE = 0 before sending
		while((I2C2->SR1 & I2C_SR1_TXE) == 0);
		I2C2->DR = data; // load the data
		// wait until data is sent
		while((I2C2->SR1 & I2C_SR1_TXE) == 0);
	}
}
	

void i2c_stop(uint8_t i2c_num)
{
	
	if(i2c_num == 1)
	{
		I2C1->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		I2C2->CR1 |= I2C_CR1_STOP;
	}
}


void i2c_adress(uint8_t i2c_num, uint8_t address, uint8_t r_w) // 0: write, 1: read
{
	
	if(i2c_num == 1)
	{
			I2C1->DR = (address|r_w);
		// wait for the acknowledge
		while((I2C1->SR1 & I2C_SR1_ADDR)==0);
		
		while(I2C1->SR1 & I2C_SR1_ADDR)
		{
			if((I2C1->SR1 & I2C_SR1_ADDR)==0)
				break;
		}
	}
	else
	{
			I2C2->DR = (address|r_w);
		// wait for the acknowledge
		while((I2C2->SR1 & I2C_SR1_ADDR)==0);
		
		while(I2C2->SR1 & I2C_SR1_ADDR)
		{
			if((I2C2->SR1 & I2C_SR1_ADDR)==0)
				break;
		}
	}
}

// write data via I2C
void i2c_write(uint8_t i2c_num, uint8_t address, uint8_t data[], uint64_t length)
{
	uint64_t i = 0;
	i2c_start(i2c_num);
	i2c_adress(i2c_num, address, 0);
	
	for(i=0; i<length; i++) // send all bytes in data
	{
		I2C_Data(i2c_num, data[i]);
	}
	
	i2c_stop(i2c_num);
}

