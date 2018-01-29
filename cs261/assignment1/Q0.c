/* CS261- Assignment 1 - Q. 0*/
/* Name: Arthur Liou
 * Date: 1/22/18
 * Solution description: Wrote printf for each comment.
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int *iptr)
{
    /*Print the value pointed to by iptr*/
    printf("Value: %d\n", *iptr);
    /*Print the address pointed to by iptr*/
    printf("Address: %p\n", iptr);
    /*Print the address of iptr itself*/
    printf("iptr: %p\n", &iptr);
}

int main()
{
    /*declare an integer x*/
    int x = 2;
    /*print the address of x*/
    printf("Main Address: %d\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("X Value: %d\n", x);
    return 0;
}
