/* CS261- Assignment 1 - Q. 0*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Point pointer addresses and values
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     
     /*Print the value pointed to by iptr*/
     printf ("%s: iptr value = 0x%08x\n", __FUNCTION__, *iptr);

     /*Print the address pointed to by iptr*/
     printf ("%s: iptr pointer address = 0x%p\n", __FUNCTION__, iptr);
     
     /*Print the address of iptr itself*/
     printf ("%s: address of iptr (it's on the stack) = 0x%p\n", __FUNCTION__, &iptr);
}

int main(){
    
    /*declare an integer x*/
    int x = 0x00C0FFEE;
    
    /*print the address of x*/
    printf ("Adress of x is 0x%p\n", &x);
    
    /*Call fooA() with the address of x*/
    fooA (&x);

    /*print the value of x*/
    printf ("The value of x is 0x%08x\n", x);

    return 0;
}
