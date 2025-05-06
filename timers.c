#include "stm32f10x.h"
#include "timers.h"
/* CNT-> counter register
	ARR -> Auto Reload Register, his value is continuously compared to CNT
	CR1 -> Control Register
	SR -> Status Register when ARR=CNT UIF(update interrupt flag) is set
	and CNT=0
*/

void timer2_pwm(){
RCC  -> APB1ENR |= 1<<0;
TIM2 -> PSC = 27;
TIM2 -> ARR = 64284;
TIM2 -> CCMR1 |= (1 << 6) | (1<<5);
TIM2 -> CCER |= 1 << 0; // salida por el canal 1  del timer 2
TIM2 ->  CR1 |= 1 << 0;






}


void timer3_pwm(){

RCC -> APB1ENR |= 1<<1;
TIM3 -> PSC= 27;
TIM3 -> ARR =  64284;
TIM3 -> CCMR1 |= (1<< 6) | (1<<5);
TIM3 -> CCER |= (1 <<0);  // salida por el canal 1 del timer 3
TIM3 -> CR1 |= (1<<0);


}