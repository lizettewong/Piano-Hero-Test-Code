// Piano.c
// This software configures the off-board piano keys
// Lab 6 requires a minimum of 4 keys, but you could have more
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
#include "../inc/tm4c123gh6pm.h"
uint8_t key;
// **************Piano_Init*********************
// Initialize four piano key inputs, called once to initialize the digital ports
// Input: none 
// Output: none
void Piano_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x10;				//turn on clock for portE
	int volatile nop;
	nop++;
	GPIO_PORTE_DIR_R &= ~(0x03);		//make PE0 and PE1 inputs
	GPIO_PORTE_DEN_R |= 0x03;				//digital enable 
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
//   bit n is set if key n is pressed
uint32_t Piano_In(void){
	key = GPIO_PORTE_DATA_R;			//read port E
	key &= 0x03;
  return key; 
}
