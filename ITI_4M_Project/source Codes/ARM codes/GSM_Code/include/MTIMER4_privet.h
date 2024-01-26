/********************************************************************************************************/
/* Author            :Menna Abdellatif                                                                  */
/* Version           : V0.0.0                                                                           */
/* Data              : 23 May 2022                                                                      */
/* Description       : TIMER2_Privite.h --> implementations                                             */
/* Features          : Register Definitions                                                             */
/********************************************************************************************************/



/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/



#ifndef TIMER_REG_H_
#define TIMER_REG_H_


/*******************************************************************************************************/
/*                                    Macros Base Address Of TIMER2 Registers                         */
/*******************************************************************************************************/

 #define    TIMER2_BASE_ADRESS        0x40000000

/*******************************************************************************************************/
/*                                       Register Definitions                                          */
/*-----------------------------------------------------------------------------------------------------*/
/*     - Developer can't Edit in it                                                                    */
/*     - Register _ Defination		                                                                   */
/*     - Design :                                                                                      */
/*    				- #define	:	NO                                                                 */
/*    				- Union		:	NO                                                                 */
/*    				- Struct	:	YES                                                                */
/*                                                                                                     */
/*******************************************************************************************************/



typedef struct
{
	volatile u32 TIM_CR1;         /*!< TIM control register 1,              Address offset: 0x00 */
	volatile u32 TIM_CR2;         /*!< TIM control register 2,              Address offset: 0x04 */
	volatile u32 TIM_SMCR;        /*!< TIM slave mode control register,     Address offset: 0x08 */
	volatile u32 TIM_DIER;        /*!< TIM DMA/interrupt enable register,   Address offset: 0x0C */
	volatile u32 TIM_SR;          /*!< TIM status register,                 Address offset: 0x10 */
	volatile u32 TIM_EGR;         /*!< TIM event generation register,       Address offset: 0x14 */
	volatile u32 TIM_CCMR1;       /*!< TIM capture/compare mode register 1, Address offset: 0x18 */
	volatile u32 TIM_CCMR2;       /*!< TIM capture/compare mode register 2, Address offset: 0x1C */
	volatile u32 TIM_CCER;        /*!< TIM capture/compare enable register, Address offset: 0x20 */
	volatile u32 TIM_CNT;         /*!< TIM counter register,                Address offset: 0x24 */
	volatile u32 TIM_PSC;         /*!< TIM prescaler,                       Address offset: 0x28 */
	volatile u32 TIM_ARR;         /*!< TIM auto-reload register,            Address offset: 0x2C */
	volatile u32 TIM_RCR;         /*!< TIM repetition counter register,     Address offset: 0x30 */
	volatile u32 TIM_CCR1;        /*!< TIM capture/compare register 1,      Address offset: 0x34 */
	volatile u32 TIM_CCR2;        /*!< TIM capture/compare register 2,      Address offset: 0x38 */
	volatile u32 TIM_CCR3;        /*!< TIM capture/compare register 3,      Address offset: 0x3C */
	volatile u32 TIM_CCR4;        /*!< TIM capture/compare register 4,      Address offset: 0x40 */
	volatile u32 TIM_BDTR;        /*!< TIM break and dead-time register,    Address offset: 0x44 */
	volatile u32 TIM_DCR;         /*!< TIM DMA control register,            Address offset: 0x48 */
	volatile u32 TIM_DMAR;        /*!< TIM DMA address for full transfer,   Address offset: 0x4C */
	volatile u32 TIM_OR;          /*!< TIM option register,                 Address offset: 0x50 */
} TIM_TypeDef;

/*******************************************************************************************************/
/*                                   Struct Macros Base Address Of TIMER2                            */
/*******************************************************************************************************/


#define TIM2  ((volatile TIM_TypeDef*) TIMER2_BASE_ADRESS)

#endif /* SYSTICK_REG_H_ */
 
