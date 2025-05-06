
#ifndef _usart
#define _usart
void usart_polling();
void usart_w_interrupt();
void USART3_txrx();
void USART1_txrx();
unsigned long USART_BRR(unsigned short usart, unsigned long BR);
char UART_RX(unsigned short uart);
void UART_TX(unsigned short uart,char c);
void UART_ISR(unsigned short uart,unsigned short bridge, unsigned short * signal, unsigned short * counter, char str[]);
void UART_SEND(unsigned short uart, char str[]);
void str_empty(char str[]);


#endif

