/*******************************************************************************************************/
/* Author            : Menna Abdellatif                                                           */
/* Version           : V0.0.0                                                                          */
/* Data              : 23 May 2022                                                                     */
/* Description       : TIMER2_Interface.c --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- MTIMER2_voidInit                                                                           */
/*                                                                                                     */
/*      05- MSTK_VidSetCallBack                                                                        */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*	    * What i sell To Customer                                                                          */
/*		*  The Archictect Give The API	                                                               */
/*						- The Name Of Function                                                         */
/*						- What is The Input                                                            */
/*						- What Is The Output                                                           */
/*						- Macro                                                                        */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

/*******************************************************************************************************/
/*                                        Macros for Systick State                                     */
/*******************************************************************************************************/



/*#####################################################################################################*/
/*                                      Function Prototypes                                            */
/*#####################################################################################################*/


void MTIMER2_voidInit( void );

void MTIMER2_void_PWM(u32 );




#endif /* TIMER2_INTERFACE_H_ */
 
