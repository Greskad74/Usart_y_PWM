#include "stm32f10x.h"
#include "timers.h"
#include "garra.h"

void motor1_sec1(){
        timer2_pwm();
        for (volatile int i = 0;i < 100;i++)
        {
        TIM2 -> CCR2 = 1800;
        for (int j = 0;j < 75453;j++);
        }
        
        for (volatile int i = 100;i > 0;i--)
                                 {
        TIM2->CCR2 = 3857;
        for (int j = 0;j < 75453;j++);
        }
                                
        for (volatile int i = 0;i < 100;i++)
        {
        TIM2->CCR2 = 5914;
        for (int j = 0;j < 75453;j++);
                }
        }

 void motor1_sec2(){
                timer2_pwm();
                for (volatile int i = 0;i < 100;i++)
                {
                TIM2->CCR2 = 5914;
                for (int j = 0;j < 75453;j++);
                }

                for (volatile int i = 100;i > 0;i--)
                {
                TIM2->CCR2 = 3857;
                for (int j = 0;j < 75453;j++);
                }

                for (volatile int i = 0;i < 100;i++)
                {
                TIM2->CCR2 = 1800;
                for (int j = 0;j < 75453;j++);
                        }
                }
        

void motor2_sec1(){
                        
        timer3_pwm();        //SEGUNDO MOTOR TIMER 3
        
        for (volatile int i = 0;i < 100;i++)
                {
                TIM3->CCR2 = 1800;
                for (int j = 0;j < 65453;j++);
                }

                for (volatile int i = 100;i > 0;i--)
                {
                TIM3->CCR2 = 3857;
                for (int j = 0;j < 65453;j++);
                }
                        
                for (volatile int i = 0;i < 100;i++)
                {
                TIM3->CCR2 = 5914;
                for (int j = 0;j < 65453;j++);
                                }
                }
        

 void motor2_sec2(){
                timer3_pwm();
                for (volatile int i = 0;i < 100;i++)
                {
                TIM3->CCR2 = 5914;
                for (int j = 0;j < 65453;j++);
                }
        
                for (volatile int i = 100;i > 0;i--)
                {
                TIM3->CCR2 = 3857;
                for (int j = 0;j < 65453;j++);
                }
                
                for (volatile int i = 0;i < 100;i++)
                {
                TIM3->CCR2 = 1800;
                for (int j = 0;j < 65453;j++);
                }
                        
                }
                
