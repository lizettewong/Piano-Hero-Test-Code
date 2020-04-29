// Music.h
// Runs on LM4F120 or TM4C123
// Program written by: Reva Vaidya and Lizette Wong
// Date Created: 4/4/2020
// Last Modified: 4/4/2020 
// Lab number: 6
// Hardware connections Lizette was here 
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#ifndef MUSIC_H
#define MUSIC_H
#include <stdint.h>
#include "Sound.h"
#include "../inc/tm4c123gh6pm.h"
#define bus 150000000
#define q (bus/4)
#define h (q*2)
#define w (q*4)
#define e (q/2)
#define g (q/10)
#define s (q/4)
#define Q 0xFFFFFF				//4.7 Hz

struct state {
	uint32_t pitch;
	uint32_t tempo;
};
typedef struct state note_t;

void Music_Init(void);
void Music_Play (void);

#endif
