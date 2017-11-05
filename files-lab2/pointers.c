


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int list1 [80]; // cannot add * or it will be a mistake
int list2 [80];
int count = 0;	// global variable
void copycodes(char*, int*, int*);

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  // address of c is 0x23 and other is 0x00
  // this using little-endian, as 0x23 is the LSB, not the 0x00
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

void work(void){
	//char* text1 so text1 is already an address pointing to "This...."
	//using list1 because its name represents the address of the first element 
	//count using & to pass its address
	copycodes(text1,list1,&count);
    copycodes(text2,list2,&count);
}

void copycodes(char* t,int* l,int* c){
    while(*t!=0){ 	//beq	$t0,$0,done
		int temp = *t;
        *l=temp;  	//sw	$t0,0($a1)
        *t++;      	//addi	$a0,$a0,1, for text we only need to go one by one(increment a pointer
        *l++;       //addi	$a1,$a1,4, because this is an array which need 4 bits to go to the next element (increment a pointer
        *c=*c+1;    //lw	$t1,0($a2)    
					//addi	$t1,$t1,1 (increment a pointer
					//sw	$t1,0($a2)
    }
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
