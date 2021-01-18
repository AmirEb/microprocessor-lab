/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
A© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Task4
Version : 1
Date    : 2021-01-18
Author  : Amir Ebrahimian
Company : 
Comments: 


Chip type               : ATxmega128A1
Program type            : Application
AVR Core Clock frequency: 2.000000 MHz
Memory model            : Small
Data Stack size         : 2048
*******************************************************/

#include <mega16.h>

int delay = 0;
int btn = 0;
int nextmove = 0;

//Information given in the question table
int moves[4][4] = {{1, 0, 0, 1},{1,0, 1, 0},{0, 1, 1, 0},{0, 1, 0, 1}};


interrupt [TIM0_OVF] void timer(void)
{
    TCNT0=0x0C;

    if(btn==1) {  //Move by pressing the key
        if(delay==0) {
            PORTA.0 = moves[nextmove][0];  
            PORTA.1 = moves[nextmove][1];
            PORTA.2 = moves[nextmove][2];
            PORTA.3 = moves[nextmove][3];
        }
        
     
        
        if(delay == 5){ //After 5 ms, it moves again
            delay = 0;  
            if(nextmove<3) { //Do the next move to reach 4 moves
                nextmove++;
            } else {
                nextmove=0;
                btn=0;
            }
        } 
        
        else {
            delay++; //Each time we add a delay to 5 ms
        }   
    }
}


void main(void)
{ 
    DDRA = 0xff;  
    PORTA = 0x00;
    DDRC = 0x00;   
    PINC = 0x00;      

    
      
     TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
     
     TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
   

    #asm("sei")

    while (1) {
        if(PINC.2 == 0 && btn == 0) { 
             delay = 0;  
             btn=1;
        }
    }
}
