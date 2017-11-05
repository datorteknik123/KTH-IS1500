/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define COLUMNS 6
void print_number(int);
int count = 0;

void print_sieves(int n){
  
  if(n>=2){
	char a[(n-1)/sizeof(char)];
	for(int p=0;p<n-1;p++){
		a[p] = 0;   // 0 represend this is a prime
	}				// a[x]=0 for any x
	for(int i=2; i-2<=sqrt(n-1.0); i++){  // main steps
	  if(a[i-2]==0){ //if i is a prime
		  for(int j=2;i*j<=n; j++){
			a[i*j-2]= 1; // 1 means for all j>=2, i*j is not a prime 
		  }
	  }
	}
  
    for(int p=0;p<n-1;p++){
	  if(a[p]!=1){
		count++;
		print_number(p+2);
		
	  }
    }
  }
  printf("\n");
}

void print_number(int n){
  printf("%10d\t", n);
  if (count == COLUMNS){
    count = 0;
    printf("\n");
  }
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  //clock_t time1 = clock(), diff;
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  //diff = clock() - time1;
  //printf("Time: %d ms\n", (diff * 1000 / CLOCKS_PER_SEC));
  return 0;
  
}
