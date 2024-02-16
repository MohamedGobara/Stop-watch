/*
* learning.c
*
* Created: 30/10/2022 7:12:38 AM
* Author : Mohamed Hussein
*/

//CTRL + K + D  => FORMAT CODE


#define F_CPU 8000000
#include <util/delay.h>

#include "MemMaph.h"
#include "StdTypes.h"
#include "Utils.h"
#include "SEGMENT_interface.h"
#include "DIO_interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "STEPPER_Interface.h"
#include "ADC_interface.h"
#include "KeyPad_interface.h"
#include "CALC_interface.h"
#include "StopWatch.h"

#define DELAY 250


#define RESET_OFF 0
#define RESET_ON 1

#define RESUME_OFF 0
#define RESUME_ON 1

#define MODE_OFF 0
#define MODE_ON 1


int main(void)
{
	
	DIO_Init() ;
	u8 reset_f = RESET_OFF  , resume_f= RESUME_OFF , mode_f= MODE_OFF ;
	
	u8 num = 11  , i_loop =0 , defult_number= 11 ;
	u8 f_moveFromResToPaus =0 ;
	
	while(1) {
		
		/*************** Start While ********************/
		

		/************************** counter mode *******************************/
		if(mode_f==MODE_OFF) {

			//resume
			
			DIO_WritePin(LED_GREEN_KIT,HIGH) ;
			DIO_WritePin(LED_BLUE_KIT,LOW) ;
			
			if(resume_f==RESUME_ON) {
				
				num-- ;
				for(i_loop =0 ; i_loop < 40 ; i_loop++) {
					
					SEGMENT_Mlx(num) ;
					
					
					if (DIO_ReadPin(RESUME_BUTTON)==LOW)
					{
						
						//pause watch
						resume_f = RESUME_OFF ;
						f_moveFromResToPaus = 1 ;
						while(DIO_ReadPin(RESUME_BUTTON)==LOW) ;

					}
					
					//check reset
					if(DIO_ReadPin(RESET_BUTTON)==LOW) {
						
						num=defult_number-1 ;
						
						while(DIO_ReadPin(RESET_BUTTON)==LOW) ;
						
					}
					
					//check mode

					
					if(DIO_ReadPin(MODE_BUTTON)==LOW) {
						
						if(mode_f==MODE_OFF) {
							mode_f=MODE_ON ;
							//setting mode
						}
						else
						{
							mode_f=MODE_OFF ;
							//counter mode  ;
						}
						while(DIO_ReadPin(MODE_BUTTON)==LOW) ;
						
					}
					
				}
				
				
				if(num==0) {
					
					for(u8 i =0 ; i <4 ;i++) {
						
						DIO_WritePin(BUZZER_KIT,HIGH) ;
						DIO_WritePin(LED_RED_KIT,HIGH) ;
						_delay_ms(250) ;
						DIO_WritePin(BUZZER_KIT,LOW) ;
						DIO_WritePin(LED_RED_KIT,LOW) ;
						_delay_ms(250) ;
						
						
						
					}
					resume_f=RESUME_OFF ;
					num=defult_number ;
				}
				
				
				
			}
			
			//pause
			else if(resume_f==RESUME_OFF) {
				
				
				while ((resume_f==RESUME_OFF))
				{
					if(f_moveFromResToPaus==1) {
						
						num=num+1 ;
						f_moveFromResToPaus= 0 ;
					}
					else {
						
						SEGMENT_Mlx(num-1) ;

					}
					
					if(DIO_ReadPin(RESUME_BUTTON)==LOW){
						resume_f = RESUME_ON ;
						//RESUME COUNTER
						
						while(DIO_ReadPin(RESUME_BUTTON)==LOW) ;
						
					}
					//check reset

					if(DIO_ReadPin(RESET_BUTTON)==LOW) {
						
						//reset watch
						num=defult_number;
						while(DIO_ReadPin(RESET_BUTTON)==LOW) ;
					}
					
					//check mode
					if(DIO_ReadPin(MODE_BUTTON)==LOW) {
						
						if(mode_f==MODE_OFF) {
							mode_f=MODE_ON ;
							//setting mode
						}
						else
						{
							mode_f=MODE_OFF ;
							//counter mode  ;
						}
						while(DIO_ReadPin(MODE_BUTTON)==LOW) ;
						
					}
					
				}
				
				
			}
		}
		

		/************************** Setting mode *******************************/
		if(mode_f==MODE_ON) {
				
				DIO_WritePin(LED_GREEN_KIT,LOW) ;
				DIO_WritePin(LED_BLUE_KIT,HIGH) ;
			SEGMENT_Mlx(num) ;
			
			if(DIO_ReadPin(RESUME_BUTTON)==LOW&&mode_f==MODE_ON){
				
				
				//increment COUNTER

				
				while (DIO_ReadPin(RESUME_BUTTON)==LOW&&mode_f==MODE_ON)
				{
					for(i_loop=0 ; i_loop <8;i_loop++) {
						
						
						SEGMENT_Mlx(num) ;
					}

					num++ ;
					
					
					
					if(num==99) {
						num=0 ;
					}
					defult_number= num ;

				}
					
			}
			
			
			
			if(DIO_ReadPin(RESET_BUTTON)==LOW&&mode_f==MODE_ON) {
				
				//decrement watch
				
				
				while (DIO_ReadPin(RESET_BUTTON)==LOW&&mode_f==MODE_ON)
				{
					
					
					
					for(i_loop=0 ; i_loop <8;i_loop++) {
						
						SEGMENT_Mlx(num) ;
		
					}
					
					
					
									num-- ;

					
					
					if(num==255) {
						num=99 ;
					}
					defult_number= num ;
					
					
					
					
				}
				
				
				
				
				
				
				
			}
			
			
			
			if(DIO_ReadPin(MODE_BUTTON)==LOW) {
				
				if(mode_f==MODE_OFF) {
					mode_f=MODE_ON ;
					num=num+1 ;
					defult_number=num ;
					//setting mode
				}
				else if(mode_f==MODE_ON)
				{
					mode_f=MODE_OFF ;
					resume_f=RESET_OFF ;
					num=num+1 ;

					defult_number=num ;
					//counter mode  ;
				}
				while(DIO_ReadPin(MODE_BUTTON)==LOW) ;
				
			}
			
			
		}
		
		

		
		/*************** End While ********************/
	}
	
	/*************** End Main ********************/

}





