/* CS261- Assignment 1 - Q.2*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Pass pointers into a function
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    
    /*Print the values of x, y and z*/
    printf ("x = %d\n", x);
    printf ("y = %d\n", y);
    printf ("z = %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    z = foo (&x, &y, z);

    /*Print the value returned by foo*/
    printf ("foo(..) returned %d\n", z);

    /*Print the values of x, y and z again*/
    printf ("x = %d\n", x);
    printf ("y = %d\n", y);
    printf ("z = %d\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
    printf ("z equals 13, the return of foo(..) because \n\t*a=(5*2)=10\n\t*b=(6/2)=3\n\tc= *a + *b\n\tc=10+3=13\n");

    return 0;
}
