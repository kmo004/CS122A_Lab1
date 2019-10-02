/*	Author: kmo004
 *  Partner(s) Name: Jason Mendoza
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

volatile unsigned char light;
enum states{on1,on2,on3} state;
void Tick(){
	switch(state){
		case on1:
			if(state == on1){
				state = on2;
			}
			else{
				state = on1;
			}
			break;
		case on2:
			if(state == on2){
				state = on3;
			}
			else{
				state = on1;
			}
			break;
		case on3:
			if(state == on3){
				state = on1;
			}
			else{
				state = on1;
			}
		default:
			state = on1;
			break;
	}
	switch(state){
		case on1:
			light = 0x01;
			break;
		case on2:
			light = 0x02;
			break;
		case on3:
			light = 0x04;
			break;
			
		default:
			light = 0x00;
			break;
	}
}
volatile unsigned char light2 = 0x00;

unsigned char time1 = 0;
unsigned char pause = 0;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    
    TimerSet(500);
	TimerOn();
	state = on1;

    /* Insert your solution below */
    while (1) {
		if(PINA != 0xFF){
			if(pause == 0){
				pause = 1;
			}
			else{
				pause = 0;
			}
		}
		if(pause == 0){
			Tick();
			if(time1 == 0 || time1 == 1){
				light2 = 0x08;
				time1 = time1 + 1;
			}
			else if(time1 == 2 || time1 == 3) {
				light2 = 0x00;
				if(time1 == 3){
					time1 = 0;
				}
				else{
					time1 = 3;
				}
			}
		}
	
		PORTB = light + light2;
		while (!TimerFlag){}
		TimerFlag = 0;
		


    }
    return 1;
}
