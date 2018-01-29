/* CS261- Assignment 1 - Q.3*/
/* Name: Arthur Liou
 * Date: 1/22/18
 * Solution description: Creates an array of integers that have randomly assigned values, sorts them from smallest to largest, then prints them.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int *number, int n)
{
    /*Sort the given array number , of length n*/
    int curr, i, k;
    for (i = 0; i < n; i++)
    {
        curr = *(number + i);
        for (k = (i + 1); k < n; k++)
        {                             // Check to see if a number is lower than curr
            if (*(number + k) < curr) //if lower than current, then swap
            {
                *(number + i) = *(number + k);
                *(number + k) = curr;
                curr = *(number + i);
            }
        }
    }
}

int main()
{
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int *pArray = (int *)malloc(sizeof(int) * n);
    /*Fill this array with random numbers, using rand().*/
    // srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    {
        *(pArray + i) = rand() % 100;
    }

    /*Print the contents of the array.*/
    int j;
    for (j = 0; j < n; j++)
    {
        printf("%d, ", *(pArray + j));
    }
    printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
    sort(pArray, n);
    /*Print the contents of the array.*/
    int k;
    for (k = 0; k < n; k++)
    {
        printf("%d, ", *(pArray + k));
    }
    printf("\n");

    return 0;
}
