/*******************************************************************************************************/
/* Author            : vena emad                                                                       */
/* Version           : V0.0.0                                                                          */
/* Data              : 23 May 2022                                                                     */
/* Description       : MSPI_Program.c --> implementations                                              */
/* Module  Features  :                                                                                 */
/*      01- MSPI1_voidInit                                                                             */
/*      02- MSPI1_voidSendDataU8                                                                       */
/*      03- MSPI1_voidSetCallBack                                                                      */
/*******************************************************************************************************/



/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "LSTD_TYPES.h"
#include "LERROR_STATES.h"
#include "LBIT_MATH.h"


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/


#include "MSPI_Interface.h"
#include "MSPI_Config.h"
#include "MSPI_Privaite.h"
#include "MGPIO_interface.h"


void (*MSPI1_CallBack) (void);

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      01- MSPI1_voidInit                                             */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/



void MSPI1_voidInit ( void ){
#if(0)
#if   MSP1_STATUS == MSPI_ENABLE

#if		MSPI1_CLOCK_MODE == MSPI_MODE0

	CLR_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE1

	SET_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE2

	CLR_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE3

	SET_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

#endif

#if    MSPI1_MASTER_SLAVE == MSPI_MASTER

	SET_BIT( MSPI1 -> CR1 , 2 );

#elif  MSPI1_MASTER_SLAVE == MSPI_SLAVE

	CLR_BIT( MSPI1 -> CR1 , 2 );

#endif

#if   MSPI1_DATA_ORDER == MSPI_MSB_FIRST

	CLR_BIT( MSPI1 -> CR1 , 7 );

#elif MSPI1_DATA_ORDER == MSPI_LSB_FIRST

	SET_BIT( MSPI1 -> CR1 , 7 );

#endif

#if   MSPI1_SS_MANAGE  == HW_SLAVE_MANAGEMENT

	CLR_BIT( MSPI1 -> CR1 , 9 );

#elif MSPI1_SS_MANAGEb == SW_SLAVE_MANAGEMENT

	SET_BIT( MSPI1 -> CR1 , 9 );

#endif

#if   MSPI1_DATA_SIZE == MSPI_8BIT_DATA

	CLR_BIT( MSPI1 -> CR1 , 11 );

#elif MSPI1_DATA_SIZE == MSPI_16BIT_DATA

	SET_BIT( MSPI1 -> CR1 , 11 );

#endif

#if   MSPI1_INT_STATUS == MSPI_INT_DISABLE

	/* Active Intterput OF  TXEIE & RXNEIE CR2*/
	//MSPI1 -> CR2 = 0 ;

	MSPI1 -> CR2 = 0x00000030;

#elif MSPI1_INT_STATUS == MSPI_TXE_INT_ENABLE

	SET_BIT( MSPI1 -> CR2 , 7 );

#elif MSPI1_INT_STATUS == MSPI_RXNE_INT_ENABLE

	SET_BIT( MSPI1 -> CR2 , 6 );

#endif

	MSPI1 -> CR1 &= 0xFFC7 ;
	MSPI1 -> CR1 |= ( MSPI1_PRESCALLER << 3 ) ;

	SET_BIT( MSPI1 -> CR1 , 6 );

#elif MSP1_STATUS == MSPI_DISABLE
	CLR_BIT( MSPI1 -> CR1 , 6 );
#endif
#endif

	//	SET_BIT( MSPI1 -> CR1 , 9 );
	//	SET_BIT( MSPI1 -> CR1 , 0 );
	//	SET_BIT( MSPI1 -> CR1 , 1 );
	//	CLR_BIT( MSPI1 -> CR1 , 8 );
	//	CLR_BIT( MSPI1 -> CR1 , 2 );
	//	//SET_BIT( MSPI1 -> CR2 , 7 ); //TX int
	//	SET_BIT( MSPI1 -> CR2 , 6 ); //Rx int
	//	SET_BIT( MSPI1 -> CR1 , 6 );
	//
	/* CPOL =1 / CPHA = 1 / Prescaller = Clk/2 / SPI Enable / MSB First */
	MSPI1 ->CR1 = 0x0347 ;


}

u8 MSPI1_voidSendDataU8 ( u8 Copy_u8Data ){

	/* Clear For Slave Select Pin */
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_0, _LOW) ;

	/* Send Data */
	MSPI1 -> DR = Copy_u8Data;

	/* Wait Busy Flag to finish */
	while (GET_BIT(MSPI1 -> SR, 7) == 1);



	/* Set Salve Select Pin */
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_0, HIGH) ;

	/* Return to the received data */
	return (u8) MSPI1 -> DR ;

}

void MSPI1_voidSetCallBack( void (*ptr) (void) ){

	MSPI1_CallBack = ptr;

}

void SPI1_IRQHandler(void){

	MSPI1_CallBack();

}
