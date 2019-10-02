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
#include "lcd.h"
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
unsigned char score = 0;
unsigned char update = 0;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    
    TimerSet(500);
	TimerOn();
	LCD_init();
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
			update = 0;
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
		else if(pause != 0 && update == 0){
			update = 1;
			if(light == 0x02){
				score = score + 1;
			}
			else{
				if(score == 0){
				}
				else{
					score = score - 1;
				}
			}
		}
	
		PORTB = light + light2;
		LCD_Cursor(1);
		LCD_WriteData(score + '0');
		while (!TimerFlag){}
		TimerFlag = 0;
		


    }
    return 1;
}
