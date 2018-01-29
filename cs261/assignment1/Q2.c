/* CS261- Assignment 1 - Q.2*/
/* Name: Arthur Liou
 * Date: 1/22/18
 * Solution description: Foo doubled the first parameter, halves the second, and the third parameter returns the sum of the first two. Returns the sum. All three numbers are printed before and after foo is invoked.
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int *a, int *b, int c)
{
    /*Set a to double its original value*/
    *a = *a * 2;
    /*Set b to half its original value*/
    *b = *b / 2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
    return c;
}

int main()
{
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    /*Print the values of x, y and z*/
    printf("X: %d\n", x);
    printf("Y: %d\n", y);
    printf("Z: %d\n", z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int result = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("Foo Returned Result: %d\n", result);
    /*Print the values of x, y and z again*/
    printf("New X: %d\n", x);
    printf("New Y: %d\n", y);
    printf("New Z: %d\n", z);
    /*Is the return value different than the value of z?  Why?*/
    //Z was passed by value into foo. X & y were passed by reference, so while x & y were changed, z was unchanged as foo didn't access it.
    return 0;
}
