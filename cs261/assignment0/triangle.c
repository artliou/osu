/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 1/8/18
 ** Description: Assignment 0

 Find the area of a triangle in C given 3 sides.
 Heron's Formula

gcc triangle.c -o triangle -lm

 *********************************************************************/

#include <stdio.h>
#include <math.h>

double triangleArea(double a, double b, double c)
{

    double perimeter = 0.5 * (a + b + c);
    // printf("Triangle's perimeter = %f \n", perimeter); //Should be 36
    double next = perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c);
    // printf("Triangle's next = %f \n", next);
    return sqrt(next);
}

int main(void)
{
    double result = triangleArea(24, 30, 18);
    printf("Triangle's Area = %f \n", result);
    return 0;
}