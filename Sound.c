// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: Reva Vaidya and Lizette Wong
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"

uint32_t Index = 0; 
const int SineWave[64] = {32,35,38,41,44,47,49,52,54,56,58,59,61,62,62,63,63,63,62,62,61,59,58,56,54,52,49,47,44,41,38,35,32,29,26,23,20,17,15,12,10,8,6,5,3,2,2,1,1,1,2,2,3,5,6,8,10,12,15,17,20,23,26,29};

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
	DAC_Init();
  NVIC_ST_RELOAD_R = 0;									//defualt when nothing is pressed u want nothing to play
	NVIC_ST_CTRL_R = 0x07; 							//allow interrupts
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF)|0x20000000; // priority 1
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){		
	NVIC_ST_RELOAD_R = period; 
}

	void SysTick_Handler(void){
  Index = (Index+1)&0x3F;      // 6 bit sine wave 
  DAC_Out(SineWave[Index]);    // output one value each interrupt
}
	
