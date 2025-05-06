

#include "stm32f10x.h" 
#include "systick_time.h"
#include "garra.h"
#include <string.h>
#include "usart.h"
#include "delay.h"

char USART_1_msg[250];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;

char USART_2_msg[250];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;

char USART_3_msg[250];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;
char pw1[] = "PWM1";
char pw2[]= "PWM2";


char chat = 'C';

char msg[30] = "Hellow \n";

int main()
{
delay_init();
USART1_txrx();
USART3_txrx();

delay_ms(100);

UART_SEND(1,"terminal serial");
UART_SEND(3,"terminal bluetho");
	

while(1)
	{
		
	}
}



void USART1_IRQHandler()
{
 //UART_ISR(1,3,&USART_1_sig, &USART_1_cnt, USART_1_msg);
 if (strcmp(USART_1_msg,pw1)){
  motor1_sec1();
  }
 }

void USART3_IRQHandler()
{
 //UART_ISR(3,1,&USART_3_sig, &USART_3_cnt, USART_3_msg);
  if (strcasecmp(USART_3_msg,pw2)){
  motor2_sec1();
  
}


}



