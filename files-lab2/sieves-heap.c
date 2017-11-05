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
int count = 0;

void print_number(int n){
  printf("%10d\t", n);
  if (count == COLUMNS){
    count = 0;
    printf("\n");
  }
}
void print_sieves(int n){
  if(n>1){
	int *a = malloc(sizeof(int)*(n+1));
	for(int p=0;p<n+1;p++){
		a[p] = 0;   // 0 represend this is a prime
	}
	for(int i=2; i<=sqrt(n+1); i++){
	  if(a[i]==0){ // i is a prime
		  for(int j=2;i*j<=n; j++){
			a[i*j]= 1; // 1 means this i*j is not a prime 
		  }
	  }
	}
  
    for(int p=2;p<n+1;p++){
	  if(a[p]!=1){
		count++;
		print_number(p);
	  }
	  
    }
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

 
