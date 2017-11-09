/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10) 
#if TMR2PERIOD > 0xffff
#error "TMR2PERIOD is too big"
#endif

int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // initialize Port E so that bits 7 through 0 of Port E are set as outputs(0)
  // Register TRISE has address 0xbf886100
  volatile int * trise = (volatile int *) 0xbf886100;
  // least 8 bits are 0
  * trise = * trise & 0xff00;
  // initialize port D so that bits 11 through 5 of Port D are set as inputs(1)
  TRISD = TRISD & 0x0fe0;
  
  T2CON = 0x70; // 0111 000 is for 1:256
  PR2 = TMR2PERIOD; // for a timeout value of 100 ms
  TMR2 = 0; // reset the counter
  T2CONSET = 0x8000; // start the timer
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int * porte = (volatile int *) 0xbf886110;
  // initial the value to 0
  * porte = 0x0; 
  int btns;
  int sw;

  while(1) { 
    btns = getbtns();
    sw = getsw();
    // delay( 1000 ); 
	// test the time-out event flag
	// from exercise 2
	if(IFS(0) & 0x100){
      IFS(0) = 0;	//Reset all event flags (crude!)
	  // without this, the speed will become extremely fast
	  timeoutcount++;
	}
    // Pressing buttons simultaneously should update all relevant digits of mytime
	// hence we use if instead of if-else condition
    // BTN 2
    if(btns & 0x1 ){
      mytime = (sw << 4) | (mytime & 0xff0f);
    }
    // BTN 3
    if(btns & 0x2 ){
      mytime = (sw << 8) | (mytime & 0xf0ff);
    }
    // BTN 4
    if(btns & 0x4){
      mytime = (sw << 12) | (mytime & 0x0fff);
    }
    
	if(timeoutcount == 10){
	  time2string( textstring, mytime );
      display_string( 3, textstring );
      tick( &mytime );
      // increase the binary value of LED lights when function tick is called
      * porte =  * porte + 0x1;
	  timeoutcount = 0; // reset timeout value to 0
	}
	display_image(96, icon);
	display_update();
  }
}

