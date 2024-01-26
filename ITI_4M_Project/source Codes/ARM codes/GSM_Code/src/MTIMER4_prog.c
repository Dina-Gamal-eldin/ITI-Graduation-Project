
#include"LSTD_TYPES.h"
#include"LBIT_MATH.h"
#include"MTIMER4_privet.h"
#include"MTIMER4_interface.h"


void MTIMER2_voidInit( void )
{
	TIM2->TIM_PSC = 10 - 1;    /*PRESCALER *divided by 10 */
	TIM2->TIM_ARR = 26667 - 1; /* divided by 26667 */
	TIM2->TIM_CNT = 0;
	TIM2->TIM_CCMR1 = 0x0060;  /* PWM mode */
	TIM2->TIM_CCER = 1;        /* enable PWM Ch1 */
	TIM2->TIM_CR1= 1;          /* enable timer */
}
void MTIMER2_void_PWM(u32 copy_u8DutyCycle)
{
	TIM2->TIM_CCR1 = copy_u8DutyCycle - 1; /* pulse width 1/3 of the period */
}
