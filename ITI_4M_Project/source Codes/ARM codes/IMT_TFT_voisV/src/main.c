#include "LSTD_TYPES.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_Interface.h"
#include"MEXTI_interface.h"
#include "MDMA_Interface.h"
#include "MSPI_Interface.h"
#include "HTFT_Interface.h"
#include"Delay_interface.h"
#include "MSYSTICK_Interface.h"
#include"MUSART_Interface.h"
#include "MGPIO_private.h"



#include "speedwarning.h"
#include "welcome.h"
#include"pic2.h"
#define NVIC_EXTI0     6


static u8 L_u8msg=0;

#define LED_NUM   8
volatile u16 i = 0 ;
void App_voidSetDAC(void);



u8 flag=0;



volatile u8 Global_u8Flag = 0 ;

volatile u32 Global_u32FrameData[50] = {0} ; // 32 + 1 start = 33

volatile u8 Global_u8EdgeCounter   = 0 ;


volatile u8 Global_u8Data =  0 ;

void App_voidPlay(void)
{

	switch(Global_u8Data)
	{
	case 69: flag=1;
	break ;
	case 70 : flag=1;
	break ;
	}
}

/*Called in the End of Frame */
void App_voidTakeAction(void)
{
	//asm("NOP") ;
	u8 i ;

	Global_u8Data = 0 ;
	if((Global_u32FrameData[0]>= 10000) && (Global_u32FrameData[0] <= 14000))
	{
		MGPIO_voidWriteData(_GPIOA_PORT, _PIN_2, _HIGH);
		for(i = 0 ; i<8 ;i++)
		{
			if ((Global_u32FrameData[17+i]>= 2000) && (Global_u32FrameData[17+i] <= 2300))
			{
				/*Logic one*/
				SET_BIT(Global_u8Data,i);
			}
			else
			{
				/*Logic Zero*/
				CLR_BIT(Global_u8Data,i);
			}
		}
		App_voidPlay();
	}
	else
	{
		/*invalid Frame*/
	}
	Global_u8Flag = 0 ;
	Global_u32FrameData[0] = 0 ;
	Global_u8EdgeCounter   = 0 ;
}

void App_voidGetFrame(){

	// asm("NOP") ;

	if(Global_u8Flag == 0)
	{
		/*Start Timer*/
		MSTK_voidSetIntervalSingle(100000,App_voidTakeAction);
		Global_u8Flag = 1 ;
	}
	else
	{
		Global_u32FrameData[Global_u8EdgeCounter] = MSTK_u32GetElapsedTime() ;
		MSTK_voidSetIntervalSingle(100000,App_voidTakeAction);
		Global_u8EdgeCounter++;
	}

}



int main(void)
{

	/*System Clock is 16MHz from HSI*/
	MRCC_voidInitSystemClk();

	/*Enable GPIO Peripheral clock*/
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOB ) ;
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOA ) ;
	MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_SYSCFG) ;


    /* Config RCC GPIO SPI */
    MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_SPI1); //Enable CLK Of SPI1   At APB2
    /*Enable RCC For USART1*/
    MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_USART1); //Enable CLK Of UART1   At APB2


	/*************************************************************************************************************************/
	/********************************************S Configur SPI1  Pins**************************************************/
	/*************************************************************************************************************************/


			/* GPIO At HW MODE MOSI(AF,OUTPUT)Like SPI1--->AF(5)*/
			/* GPIO At HW MODE NSS(AF,OUTPUT)Like SPI1--->AF(5) */
			/* GPIO At HW MODE MISO(AF,INPUT)Like SPI1--->AF(5) */

			MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_5, _MODE_ALTF);
			MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_7, _MODE_ALTF);

			MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_5, _ALTFN_5);    //SPI1_SCK-->SPI1
			MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_7, _ALTFN_5);     //SPI1_MOSI-->SPI1

			/*************************************************************************************************************************/
			/******************************************** Configur UART1  Pins******************************************/
			/*************************************************************************************************************************/

				MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_9, _MODE_ALTF);     //TX-->UART1
				MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_10, _MODE_ALTF);    //RX-->UART1
				MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_9, _ALTFN_7);      //TX-->UART1
				MGPIO_voidSetPinAltFn(_GPIOA_PORT, _PIN_10, _ALTFN_7);     //RX-->UART1

			/*************************************************************************************************************************/
			/******************************************** initialize Output Pins  in System ***********************************/
			/*************************************************************************************************************************/
			for(int PIN =1; PIN<4; PIN++)
			{                                                                              /* A0   */
				/*Set Pin Mode --> Output*/                                                /* RST  */
				MGPIO_voidSetPinMode(_GPIOA_PORT, PIN, _MODE_OUTPUT) ;                     /* CLK  */
				/*Out put Push Pull*/                                                      /* MOSI */
				MGPIO_voidSetPinOutPutType(_GPIOA_PORT,PIN,_OUTPUT_TYPE_PUSH_PULL);
				/*Pin Speed*/
				MGPIO_voidSetPinOutSpeed(_GPIOA_PORT, PIN, _OUTPUT_SPEED_LOW);
			}

			/*Set Pin Mode --> Input*/
				MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_11, _MODE_INPUT) ;     //EXTI0
				/*Input Pull Type*/
				MGPIO_voidSetPullType(_GPIOA_PORT, _PIN_11, _PULL_OFF);
			/*************************************************************************************************************************/
			/********************************************Step 6: Initialize SPI1 ***************************************************/
			/*************************************************************************************************************************/


				MSPI1_voidInit() ;

				/*************************************************************************************************************************/
				/********************************************Step 6:  initialize system Peripherials *************************************/
				/*************************************************************************************************************************/

				/* TFT Init */
				HTFT_voidInitialize();




	for(u8 PIN_NUM = 0 ; PIN_NUM < LED_NUM ; PIN_NUM++)
	{
		/*Set Pin Mode --> Output*/
		MGPIO_voidSetPinMode(_GPIOB_PORT, PIN_NUM, _MODE_OUTPUT) ;

		/*Out put Push Pull*/
		MGPIO_voidSetPinOutPutType(_GPIOB_PORT,PIN_NUM,_OUTPUT_TYPE_PUSH_PULL);

		/*Pin Speed*/
		MGPIO_voidSetPinOutSpeed(_GPIOB_PORT, PIN_NUM, _OUTPUT_SPEED_LOW);

	}



	MEXTI0_voidSetCallBack(App_voidGetFrame);
    MEXTI_voidSetEXTIConfiguration(EXTI0, _GPIOA_PORT);
    MEXTI_voidSetSignalLatch(EXTI0, FALLING_EDGE);

		/*Enable Peripheral Interrupt*/
		MNVIC_voidEnableInterrupt(NVIC_EXTI0);
		/*Enable uart1 from NVIC*/
		MNVIC_voidEnableInterrupt(37) ;
		/*************************************************************************************************************************/
			/******************************************** Initialize USART1 ***************************************************/
			/*************************************************************************************************************************/

			MSUART_voidInit();



			/*************************************************************************************************************************/
			/********************************************  initialize system Peripherials *************************************/
			/*************************************************************************************************************************/
			MUSART_voidEnable(1) ; //Enable UART 1

		/*SysTick Init*/
		MSTK_voidInit();

while(flag==0){};
HTFT_voidDisplayImage(welcome1);
MSTK_voidInit();
	while(1)
	{

		if(L_u8msg=='G')
						{


					/*Enable Interrupt*/
					MSTK_voidINTStatus(MSTK_INT_EN) ;

								/*For 125 Micro Second*/
								MSTK_voidStart(250) ;
							    /*Set  CallBack*/
								MSTK_voidSetCallBack(App_voidSetDAC) ;
								/* Display Image */
								HTFT_voidDisplayImage(pic2);


	}  

}
}

void App_voidSetDAC(void)
{

   GPIOB_ODR = speedwarning_raw[i] ;
   i++ ;
   if(i == 18040)
   {
	   i = 0 ;
   }
}

void USART1_IRQHandler(void){
	L_u8msg=MUSART_u8ReadData(1);
}
