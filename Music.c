//Music.c
// Program written by: Reva Vaidya & Lizette Wong
// Date Created: 4/4/2020
// Last Modified: 4/4/2020 
// Lab number: 6

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Music.h"
#include "Sound.h"
uint8_t songpt;
uint32_t flag;

// we need to add rests in between sixteenth notes because DAC cannot distinguish them
note_t OneLastTime_Data[27] = { 						//declare prototype for variable 
	{G0, h,},
	{A0, (e+q)},
	{B0, (e+q+e)},
	{G0, e},
	{C0, q},
	{B0, q},
	{E0, (q+e)},
	{D0, e},
	{E0, (q+e)},
	{D0, e},
	{E0, q},
	{G0, e},
	{GF0, (e+h)},
	{G0, h},
	{A0, (e+q)},
	{B0, (e+q+e)},
	{G0, e},
	{C0, q},
	{B0, q},
	{E0, (q+e)},
	{D0, e},
	{E0, (q+e)},
	{D0, e},
	{E0, q},
	{G0, e},
	{GF0, (e+h)},
	{0,0}
};
/*note_t DangerousWoman_Data[45] = { 						//declare prototype for variable 
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, (h+q)},
	{A0, h},
	{G0, q},
	{A0, q},
	{A0, q},
	{G0, q},
	{BF0, q},
	{A0, q},
	{G0, q},
	{A0, q},
	{G0, (e+h)},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, (h+q)},
	{A0, h},
	{G0, q},
	{A0, q},
	{A0, q},
	{G0, q},
	{BF0, q},
	{A0, q},
	{G0, q},
	{A0, q},
	{G0, (e+h)},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{E0, q},
	{D0, q},
	{E0, q},
	{G0, q},
	{E0, w},
	{0,0}
};
*/
/*note_t IntoYou_Data[59] = { 						//declare prototype for variable 
	{D0, s},
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, s},
	{E0, h},
	{D0, s},
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, e},
	{D0, q},
	{D0, s},
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, s},
	{E0, h},
	{D0, s},
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, e},
	{D0, q},
	{D0, s}, 
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, s},
	{E0, e},
	{C7, e},
	{C7, e},
	{D0, (e+s)},
	{D0, s},
	{D0, s},
	{D0, e},
	{E0, e},
	{F0, e},
	{E0, e},
	{D0, q},
	{D0, s},
	{C0, q},
	{A0, q},
	{G0, (e+s)},
	{A0, s},
	{G0, q},
	{F0, (e+s)},
	{G0, s},
	{F0, q},
	{E0, (e+s)},
	{F0, s},
	{E0, q},
	{D0, w},
	{0,0}
};
*/
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(uint32_t period){//long sr;
//  sr = StartCritical();
	volatile int delay;
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
	delay++;
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = period-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector numbe r 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
  TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
//  EndCritical(sr);
}

void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT; 										//ack interrupt
	if ((OneLastTime_Data[songpt].pitch + OneLastTime_Data[songpt].tempo)== 0){  	//if song is at the end 
		TIMER0_IMR_R = 0x0000000;
		flag = 0;
	}
	Sound_Play (OneLastTime_Data[songpt].pitch);
	TIMER0_TAILR_R = OneLastTime_Data[songpt].tempo;
	songpt++;
}

void Music_Init(void){
	Timer0A_Init(100000);							//initialize timer (calls timer0a init) - WORKS WHEN STEP BUT NOT YEET 
	TIMER0_IMR_R = 0x0000000; 		//disarm 
	songpt = 27;                  // set pointer to null 
}
void Music_Play (void){
	songpt = 0;								//initial  pointer
	TIMER0_IMR_R = 0x0000001; //arm 
	flag = 1;
}
	
	
	
