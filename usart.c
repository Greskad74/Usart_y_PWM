/*
steps to program USART:
- Enable clocks for GPIOs and USART.
- Configure Control Register: 1 stop bit, no
parity, 
- Set baudrate (BRR register).
- Select alternate function output for UARTn_Tx
UARTn_Rx as input.
- Write a byte to UARTn Data Register.
- Monitor TC bit of Status Register (UARTn_SR)
and wait for trnasmission to complete.
*/


#include <stm32f10x.h>
#include "delay.h"
#include "usart.h"

void usart1_sendbyte(uint16_t data){
	USART1->DR = data;
	while((USART1->SR&(1<<6))==0);
	USART1->SR &= ~(1<<6);
}


void usart1_sendstring(char s[]){
	int i = 0;
	while(i < 64){
		if (s[i] == '\0') break;
		usart1_sendbyte(s[i++]);
	}
}


void usart_polling(){
	RCC->APB2ENR |= 0xFC | (1 << 14);
	//usart1_tx PA9
	//usart1_rx PA10
	GPIOA->ODR |= (1 << 10);
	GPIOA->CRH = 0x444448B4;
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;
	while(1){
		usart1_sendbyte('h');
		usart1_sendbyte('e');
		usart1_sendbyte('y');
		usart1_sendbyte(' ');
		usart1_sendbyte('n');
		usart1_sendbyte('a');
		usart1_sendbyte('n');
		usart1_sendbyte('a');
		usart1_sendbyte('\n');
		usart1_sendstring("isaac");
		usart1_sendbyte('\n');
		usart1_sendbyte('\r');
	}
}


void usart_w_interrupt(){
	USART1->CR1 |= (1 << 2 | 1 << 3 | 1 << 13); //enable rx,tx and USART
	/* Example Baud rate 9600
	BRR = fpclk/bayd rate = 72,000,000/9600 = 7,500 */
	USART1->BRR = 7500; //set baudrate
	//USART1->CR1 |= (1 << 7);	//TXE enable interrupt
	NVIC_EnableIRQ(USART1_IRQn);//enable global interrupts
}

void USART1_txrx(){
	__disable_irq();

	RCC->APB2ENR |= (1 << 14);
	RCC->APB2ENR |= (1 << 2);  // Habilita el reloj para GPIOA
	//usart1_tx PA9
	//usart1_rx PA10

	GPIOA->CRH &= ~((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));  // LIMPIA PA 9
	GPIOA->CRH |= (1 << 7) | (1 << 5) | (1 << 4);   // PA9 SALIDA A 50 MHZ PUSHPULL
	GPIOA->CRH &= ~((1 << 11) | (1 << 10) | (1 << 9) | (1 << 8));  // Reseteo a Pa10, Entrada 
	GPIOA -> CRH |= (1 << 10); // opendrai
	// Setup the baude rate for 9600 bps
	USART1->BRR = 7500; // 0x341 = 9600 bps
	USART1->CR1 |= 8;
	USART1->CR1 |= 4;
	USART1->CR1 |= 0x2000;
	USART1->CR1 |= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);
		__enable_irq();


}

void USART3_txrx(){
	__disable_irq();

	RCC->APB2ENR |= (1 << 3); //gpio8
	RCC->APB1ENR |=(1 << 18); // Habilita el reloj para USART3
	GPIOB->CRH  &= ~ ((1<<15) | (1 <<12)| (1<<14)| (1<<13)); // limpiza Rx
	GPIOB->CRH |= (1 << 14); // RX FLOTANTE
	GPIOB->CRH  &= ~ ((1<<11) | (1 <<10)| (1<<9)| (1<<8)); // limpiza TX 
	GPIOB->CRH |= ( (1 <<11)|(1 << 9) | (1<<8)); // TX A 50 Mhz
	
	// Setup the baude rate for 9600 bps
	USART3->BRR = 0xEA6; // 0x341 = 9600 bps
	USART3->CR1 |= 8;
	USART3->CR1 |= 4;
	USART3->CR1 |= 0x2000;
	USART3->CR1 |= 0x20;
	NVIC_EnableIRQ(USART3_IRQn);
	__enable_irq();
}








unsigned long USART_BRR(unsigned short usart, unsigned long BR)
{
	unsigned long div = 36000000UL;
	unsigned long dec;
	unsigned long final;
	double frac = 36000000.00;
	double frac2 = 1.00;
	
	if(usart == 1)
	{
	div = 72000000UL;
	frac = 72000000.00;
	}
	div = div / (BR*16);
	frac = 16*((frac / (BR*16))-div);
	dec = frac;
	frac2 = 100*(frac-dec);
	if(frac2>50)
	{
		dec ++;
		if(dec == 16)
		{
			dec = 0;
			div ++;
		}
	}
	
	final = (div<<4);
	final += dec;
	
	return final;
	
}


char UART_RX(unsigned short uart)
{
	char c;
	if(uart == 1)
		{
		while((USART1->SR & 0x20) == 0x00)
		{};
		c = USART1->DR;
		}
	else if(uart == 2)
		{
		while((USART2->SR & 0x20) == 0x00)
		{};
		c = USART2->DR;
		}
		if(uart == 3)
		{
		while((USART3->SR & 0x20) == 0x00)
		{};
		c = USART3->DR;
		}
		return c;
}

void UART_TX(unsigned short uart,char c)
{
	if(uart == 1)
		{
			while((USART1->SR & (1<<6)) == 0x80)
			{};
			USART1->DR = c;
		}
	else if(uart == 2)
		{
			while((USART2->SR & (1<<6)) == 0x80)
			{};
			USART2->DR = c;
		}
		if(uart == 3)
		{
			while((USART3->SR & (1<<6)) == 0x80)
			{};
			USART3->DR = c;
		}
}

/*
1- Define my uart
2- is it bridge or process or both 
if process : Sting to fullfill, cnt , signal 
*/

void UART_ISR(unsigned short uart,unsigned short bridge, unsigned short * signal, unsigned short * counter, char str[])
{
	if(bridge == 0)
		{
			str[*counter] = UART_RX(uart);
			if(str[*counter] == '\n')
			{
				*counter = 0;
				*signal = 1;
			}
			else
			{
				*counter = *counter +1;
			}
		}
	else
	{
		UART_TX(bridge,UART_RX(uart));
	}
}

void UART_SEND(unsigned short uart, char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		UART_TX(uart,str[i]);
		i++;
		delay_ms(1);
	}
}

void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	
}
