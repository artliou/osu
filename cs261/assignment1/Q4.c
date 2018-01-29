/* CS261- Assignment 1 - Q.4*/
/* Name: Arthur Liou
 * Date: 1/22/18
 * Solution description: Taking Q2 and Q3 and combining them together.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student
{
    int id;
    int score;
};

void sort(struct student *students, int n)
{
    /*Sort the n students based on their score*/
    int currID, currScore;
    int i;
    for (i = 0; i < n; i++)
    {
        currID = (students + i)->score;
        currScore = (students + i)->score;
        int k;
        for (k = (i + 1); k < n; k++)
        {
            if ((students + k)->score < currScore)
            { //swap both scores and ids
                (students + i)->id = (students + k)->id;
                (students + i)->score = (students + k)->score;
                (students + k)->id = currID;
                (students + k)->score = currScore;
                currID = (students + i)->id;
                currScore = (students + i)->score;
            }
        }
    }
}

int main()
{
    /*Declare an integer n and assign it a value.*/
    int n = 20;

    /*Allocate memory for n students using malloc.*/
    struct student *Students = (struct student *)malloc(sizeof(struct student) * n);

    /*Generate random IDs and scores for the n students, using rand().*/
    srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    {
        (Students + i)->id = rand() % 20 + 1; //Randomly generate an ID number betwen 1 and 20
        (Students + i)->score = rand() % 101; // Randomly generate a score between 0 and 100
    }

    /*Print the contents of the array of n students.*/
    int j;
    for (j = 0; j < n; j++)
    {
        printf("ID:%d  Score: %d\n", (Students + j)->id, (Students + j)->score);
    }
    printf("Now Sorting Students \n");

    /*Pass this array along with n to the sort() function*/
    sort(Students, n);

    /*Print the contents of the array of n students.*/
    int m;
    for (m = 0; m < n; m++)
    {
        printf("ID:%d  Score:%d\n", (Students + m)->id, (Students + m)->score);
    }

    return 0;
}
