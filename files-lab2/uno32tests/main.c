/* main.c

   This file written 2015 by F Lundevall and David Broman

   Latest update 2015-09-15 by David Broman

   For copyright and licensing, see file COPYING */

#include <stddef.h>   /* Declarations of integer sizes and the like, part 1 */
#include <stdint.h>   /* Declarations of integer sizes and the like, part 2 */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

void saveinfo(char s[], void * a, size_t ns );
void showinfo(void);
void u32init(void);

int gv; /* Global variable. */
int in = 3; /* Global variable, initialized to 4711. */

void fun(int param)
{
  param++;
  saveword( "AF1: param", &param );	//A0003FD0,9
  gv = param; /* Change the value of a global variable. */
  // gv = 9
}

/* This is the main function */
int main()
{
  /* Local variables. */
  int m;
  int * p; /* Declare p as pointer, so that p can hold an address. */
  char cs[ 9 ] = "Bonjour!";
  //A0003FEC to A0003FF3
  char * cp = cs; /* Declare cp as pointer, initialise cp to point to cs */

  /* Do some calculation. */
  gv = 4;
  m = gv + in;

  /* Check the addresses and values of some variables and stuff */
  saveword( "AM1: gv", &gv );	//A000000C,4	
  saveword( "AM2: in", &in );	//A0000008,3
  saveword( "AM3: fun", &fun );	//9D001180,27BDFFE8
  saveword( "AM4: main", &main );	//9D0011D8,27BDFFD0

  p = &m;

  /* Check p and m */
  saveword( "AM5: p", &p );	//A0003FE8,A0003FE4	
  saveword( "AM6: m", &m );	//A0003FE4,7

  /* Change *p */

  *p = *p + 1;

  /* Check p and m */
  saveword( "AM7: p", &p );	//A0003FE8,A0003FE4		
  saveword( "AM8: m", &m );	//A0003FE4,8

  p = (int*)cp;   /* Casting a char pointer to an integer pointer */

  saveword( "AM9: p", &p );	//A0003FE8,A0003FEC

  savebyte( "AM10: cs[0]", &cs[0] );	//A0003FEC,42	 0x42.......B
  savebyte( "AM11: cs[1]", &cs[1] );	//A0003FED,6F	 0x6f........o
  savebyte( "AM12: cs[2]", &cs[2] );	//A0003FEE,6E	 0x6e........n
  savebyte( "AM13: cs[3]", &cs[3] );	//A0003FEF,6A	 0x6a.........j

  *p = 0x1234abcd; /* It starts to get interesting... */ 
					// 12 is the MSB and cd is the LSB
  savebyte( "AM14: cs[0]", &cs[0] );	//A0003FEC,CD
  savebyte( "AM15: cs[1]", &cs[1] ); 	//A0003FED,AB	
  savebyte( "AM16: cs[2]", &cs[2] );	//A0003FEE,34	
  savebyte( "AM17: cs[3]", &cs[3] );	//A0003FEF,12

  fun(m);  // only pass the value of m, not the address

  /* Re-check the addresses and values of m and gv */
  saveword( "AM18: m", &m );	//A0003FE4,8
  saveword( "AM19: gv", &gv );	//A000000C,9

  showinfo();
}
