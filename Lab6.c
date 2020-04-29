// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Reva Vaidya & Lizette Wong
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "Music.h"
uint32_t count = 0;
extern uint32_t flag;

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

//#include "DAC.h"
//int main(void){ uint32_t data; // 0 to 15 DAC output
  //TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // like Program 4.6 in the book, 80 MHz
  //DAC_Init();
  //for(;;) {
    //DAC_Out(data);
    //data = 0x0F&(data+1); // 0,1,2...,14,15,0,1,2,...
  //}
//}
int main(void){ 
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
	Music_Init(); 
  // other initialization
	SYSCTL_RCGCGPIO_R |= 0x20;					//turn on clock for portE
	GPIO_PORTF_DIR_R 	|= 0x02;					//make PE0-3 inputs
	GPIO_PORTF_DEN_R  |= 0x02;					//dig enable 
  EnableInterrupts();
  while(1){ 
		count++;
		if (count > 100000){
		GPIO_PORTF_DATA_R ^= 0x02;				//heartbeat
		count = 0;
		}
		if (Piano_In() == 0x01){					// if PE0 pressed, play song 
			Music_Play();
	}
		while(flag == 1){									// do absolutely nothing if music playing and flag is 1
		}
		
 }
}



