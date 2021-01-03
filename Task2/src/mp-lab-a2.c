/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
آ© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : task2
Version : 1.0
Date    : 12/24/2020
Author  : Amir Ebrahimian
Company : 
Comments: 
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/
#include <mega16.h>
#include <delay.h>

int of0Counter;
int of1Counter;
int SevenSegCounter[4];
int i = 3;
int lastSevenSeg = 3;
int temp;
int SevenSegNumber[10] = {0b00111111 , 
0b00000110 , 0b01011011 , 0b01001111 ,
 0b01100110 , 0b01101101 , 0b01111101 ,
  0b00000111 ,0b01111111 ,0b01101111};


interrupt [TIM1_OVF] void sevenSegTimer(void)
{
    if (of1Counter < 350)
    of1Counter = of1Counter + 1;
    
   else { //after 350ms add 1 number to sevenSeg display

         SevenSegCounter[3]++;  //add 1 number to fourth seven seg (the right side)

         while (i>=0){
               
         
            /*
            The one that reaches 10 resets to zero and 
            activates the next seven seg
            */
            if( SevenSegCounter[i] == 10){
             SevenSegCounter[i] = 0;  
            SevenSegCounter[i-1]++;
            }
            
             i = i - 1; //Reactivates the previous seven seg for counting
         }
                   i = 3;
             of1Counter = 0;
    }
        TCNT1H = 0xFF;
        TCNT1L = 0xF0;
}

interrupt [TIM0_OVF] void SevenSegCount(void)
{
   if(of0Counter < 1)
   of0Counter = of0Counter + 1;
   
    else{  // go to next seven seg after 1 ms
           temp = PORTC ^ 0b11111111;
           PORTC= temp ^ 0b11111111;
           PORTD = SevenSegNumber[SevenSegCounter[lastSevenSeg]];
           temp = temp >>1;
           if(temp == 0){
           temp = 8;
           }
           temp = temp ^ 0b11111111;
           PORTC = temp;

              of0Counter = 0;
             lastSevenSeg = lastSevenSeg - 1;
             if(lastSevenSeg == -1 ){
             lastSevenSeg = 3;
             }
    }
       TCNT0 = 0x00;
}


void main(void)
{

DDRD = 0b11111111;
PORTD = 0b00000000;
DDRC = 0b11111111;
PORTC = 0b11101111;

TIMSK =(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) |
 (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

TCCR0 =(0<<WGM00) | (0<<COM01) | (0<<COM00) |
 (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);

TCNT0 = 0x00;

TCCR1A =(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) |
 (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);

TCCR1B =(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) |
 (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);

TCNT1H = 0xFF;

TCNT1L = 0xF0;

MCUCR =(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);

MCUCSR =(0<<ISC2);

#asm("sei")

}
