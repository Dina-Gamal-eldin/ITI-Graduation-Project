/*
 * DCMotor_prog.c
 *
 *  Created on: feb   5 , 2022
 *      Author: Menna Abdellatif
 */
#include"MGPIO_interface.h"
#include"DCMotor_interface.h"


void H_DCMotor1_void_ClockWise(void)
{

	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_0, 1) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_1, 0) ;
}
void H_DCMotor1_void_untyClockWise(void)
{
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_0, 0) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_1, 1) ;
}
void H_DCMotor1_void_Stop()
{
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_0, 0) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_1, 0) ;
}
void H_DCMotor2_void_ClockWise(void)
{

	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_2, 1) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_3, 0) ;
}
void H_DCMotor2_void_untyClockWise(void)
{
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_2, 0) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_3, 1) ;
}
void H_DCMotor2_void_Stop()
{
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_2, 0) ;
	MGPIO_voidWriteData(_GPIOA_PORT, _PIN_3, 0) ;
}
