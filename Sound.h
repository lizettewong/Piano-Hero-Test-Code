// Sound.h
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: Reva Vaidya and Lizette Wong
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// Header files contain the prototypes for public functions
// this file explains what the module does

#ifndef SOUND_H
#define SOUND_H
#include <stdint.h>

#define C0  2389   // 523.3 Hz	
#define B0  2531   // 493.9 Hz	
#define BF0 2681   // 466.2 Hz	
#define A0  2841   // 440 Hz	
#define AF0 3010   // 415.3 Hz	
#define G0  3189  // 392 Hz	
#define GF0 3378   // 370 Hz	
#define F0  3579   // 349.2 Hz	
#define E0  3729   // 329.6 Hz	
#define EF0 4018   // 311.1 Hz	
#define D0  4257  // 293.7 Hz	
#define DF0 4510   // 277.2 Hz	
#define C7  4778   // 261.6 Hz	

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void);


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
void Sound_Play(uint32_t period);

#endif

