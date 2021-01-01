/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Task3-Q2
Version : 1
Date    : 12/30/2020
Author  : Amir Ebrahimian
Company : 
Comments: 



*******************************************************/
#include <mega16.h>
#include <alcd.h>

int counter = 0;
int charCode = 0x41;
int x = 0 , y = 0; // x and y are coordinates of LCD 

interrupt [TIM0_OVF] void LCDshow(void)
{
      if (counter < 2500)
      counter = counter + 1;
      
      else {      //after 2500 ms this run
          lcd_gotoxy(x,y); 
          lcd_putchar(charCode);
          charCode = charCode + 1; //go to next character 
          x = x + 1; 
          
            if(charCode == 0x5b){ // stop print if last character is "z"
              TIMSK = 0x00;
            }
            
            if(x == 15){ //go to next line after print 15 character
            x = 0;
            y = 1;
             }
                         
           counter = 0;    
       }
}

void main(void)
{  
    TCCR0 = 0x01;
    TIMSK = 0x01;
    lcd_init(27);
    #asm("sei")
}