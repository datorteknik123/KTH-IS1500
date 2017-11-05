/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
void print_number(int);


void print_sieves(int n){
	
  if(n>=1){
	int count = 0;
	int *a = malloc(sizeof(int)*(1000000));
	for(int p=0;p<1000000;p++){
		a[p] = 0;   // 0 represend this is a prime
	}
	for(int i=2; i<1000000; i++){
	  if(a[i]==0){ // i is a prime  
		  count++;
		  if(count==n){
			  printf("%10d\t", i);
			  return ;
		  }
		  
		  for(int j=2;i*j<=1000000; j++){
			a[i*j]= 1; // 1 means this i*j is not a prime 
		  }
	  }
	}
  
    printf("%10d\t", n);
	free(a);
  }
  printf("\n");
  
	
}



// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
