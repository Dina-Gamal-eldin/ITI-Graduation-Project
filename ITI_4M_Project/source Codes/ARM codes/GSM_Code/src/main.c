
#include "LSTD_TYPES.h"
#include "MRCC_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_Interface.h"
#include "MUSART_Interface.h"
#include"DCMotor_interface.h"
#include"Delay_interface.h"
#include"MTIMER4_interface.h"
#include <stdio.h>
#include <string.h>

static u8 L_u8msg=0;
static u8 L_u8msg1=0;
u8 flag=0;
u8 i=1;
u8 x=0;
u8 y=0;
u8 lat[30];
u8 longt[30];
u8 mobileNumber[] = "+201015244400";  // Enter the Mobile Number you want to send to
u8 ATcommand[80];
u8 buffer[30] = {0};
u8 ATisOK = 0;

int main(void)
{
	/*************************************************************************************************************************/
	/********************************Step 1: initialize System Clock is 16MHz from HSI****************************************/
	/*************************************************************************************************************************/

	MRCC_voidInitSystemClk();

	/*************************************************************************************************************************/
	/********************************************Step 2: Enable peripherls clock**********************************************/
	/*************************************************************************************************************************/

	/*Enable GPIO Peripheral clock*/
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOA ) ;
	MRCC_voidEnablePeripheralClock(AHB1,_PERIPHERAL_EN_GPIOB ) ;

	/*Enable RCC For USART1 At APB2*/
	MRCC_voidEnablePeripheralClock(APB2, PERIPHERAL_EN_USART1);
	/*Enable RCC For TIMER2 At APB1*/
	MRCC_voidEnablePeripheralClock(APB1,PERIPHERAL_EN_TIM2) ;


	/*************************************************************************************************************************/
	/******************************************** Configure UART1 ,UART6  Pins******************************************/
	/*************************************************************************************************************************/

	MGPIO_voidSetPinMode (_GPIOA_PORT, _PIN_9, _MODE_ALTF);    //TX-->UART1
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_10, _MODE_ALTF);    //RX-->UART1
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_11, _MODE_ALTF);    //TX-->UART6
	MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_12, _MODE_ALTF);    //RX-->UART6
	MGPIO_voidSetPinAltFn  (_GPIOA_PORT, _PIN_9, _ALTFN_7);    //TX-->UART1
	MGPIO_voidSetPinAltFn (_GPIOA_PORT, _PIN_10, _ALTFN_7);    //RX-->UART1
	/*************************************************************************************************************************/
		/******************************************** Configure TIMER2 PIN  Pins******************************************/
		/*************************************************************************************************************************/

			MGPIO_voidSetPinMode(_GPIOA_PORT, _PIN_5,  _MODE_ALTF) ;
			MGPIO_voidSetPinAltFn      (_GPIOA_PORT,_PIN_5,_ALTFN_1);

	/*************************************************************************************************************************/
	/********************************************Step 4: initialize Output Pins  in System ***********************************/
	/*************************************************************************************************************************/

	for(int PIN =0; PIN<4; PIN++)
	{
		/*Set Pin Mode --> Output*/
		MGPIO_voidSetPinMode		    	(_GPIOA_PORT, PIN, _MODE_OUTPUT) ;
		/*Out put Push Pull*/
		MGPIO_voidSetPinOutPutType   (_GPIOA_PORT,PIN,_OUTPUT_TYPE_PUSH_PULL);
		/*Pin Speed*/
		MGPIO_voidSetPinOutSpeed	    (_GPIOA_PORT, PIN, _OUTPUT_SPEED_LOW);
	}

	/*************************************************************************************************************************/
	/********************************************Step 5: Enable Peripherials interrupt from NVIC *****************************/
	/*************************************************************************************************************************/

	MNVIC_voidEnableInterrupt(37) ;              //Enable uart1 from NVIC

	/*************************************************************************************************************************/
	/********************************************Step 6: Initialize USART1 ***************************************************/
	/*************************************************************************************************************************/
    MTIMER2_voidInit( );
    MTIMER2_void_PWM(24000);
	MSUART_voidInit();

	/*************************************************************************************************************************/
	/********************************************Step 6:  initialize system Peripherials *************************************/
	/*************************************************************************************************************************/
	MUSART_voidEnable(1) ; //Enable UART 1
	MUSART_voidEnable(6) ; //Enable UART 6


	 while(!ATisOK){
	   	sprintf(ATcommand,"AT\r\n");
 MUSART_u8SendData(10,(u8 *)ATcommand,strlen(ATcommand));
 L_u8msg1= MUSART_u8ReadData (30);
	HAL_Delay(1000);
	if(strstr((char *)buffer,"OK")){
		ATisOK = 1;
	}
    HAL_Delay(1000);
    memset(buffer,0,sizeof(buffer));
     }
     sprintf(ATcommand,"AT+CMGF=1\r\n");// Configuring TEXT mode
     MUSART_u8SendData(10,(u8 *)ATcommand,strlen(ATcommand) );
     L_u8msg1= MUSART_u8ReadData (30);
     HAL_Delay(1000);
     memset(buffer,0,sizeof(buffer));

	/* Loop forever */
	while(1)
	{

if(L_u8msg=='G')
{
	MTIMER2_void_PWM(8000);

}

		if(L_u8msg=='L')
		{
			H_DCMotor1_void_ClockWise();
			H_DCMotor2_void_Stop();

		}
		else if(L_u8msg=='R')
		{
			H_DCMotor2_void_ClockWise();
			H_DCMotor1_void_Stop();
		}
		else if(L_u8msg=='F')
				{
			H_DCMotor1_void_ClockWise();
			H_DCMotor2_void_ClockWise();
				}
		else if(L_u8msg=='B')
				{
			H_DCMotor1_void_untyClockWise();
			H_DCMotor2_void_untyClockWise();
				}

	}
	 while(flag==0){
	 L_u8msg1= MUSART_u8ReadData (50);
  if (L_u8msg1 == 1){
	 while(L_u8msg1!=3)
 {
		lat[x]=L_u8msg1;
		 x++;
	i=i+1;
  }
	 i=i+1 ;
	  while(L_u8msg1!='#')
	   {
	  	 longt[y]=L_u8msg1;
	  	 y++;

		i=i+1  ;

	    }
         sprintf(ATcommand,"AT+CMGS=\"%s\"\r\n",mobileNumber);
         MUSART_u8SendData(10,(u8 *)ATcommand,strlen(ATcommand));
         HAL_Delay(100);
         sprintf(ATcommand,"There is a car has accident here its  location is %c latitude: %c longitude: %c",0x1a,lat,longt);
         MUSART_u8SendData(1,(u8 *)ATcommand,strlen(ATcommand));
         L_u8msg1= MUSART_u8ReadData (30);
         memset(buffer,0,sizeof(buffer));
         HAL_Delay(4000);
		  }
		  flag=1;
	  }

}

void USART1_IRQHandler(void){
	L_u8msg=MUSART_u8ReadData(1);


}

void USART6_IRQHandler(void){
	L_u8msg1=MUSART_u8ReadData(50);


}




