#include <stdio.h>


int main(void){
  int v = 2;
  int l* = v;
  v++;
  l++;
  printf("%d\n",v );  
  printf("%d\n",l ); 
}
