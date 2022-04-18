/* CS261- Assignment 1 - Q.1*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Generate and print unique student id and score
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_STUDENTS 10
#define MAX_SCORE    100

#define false        0
#define true         1

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     void * memory = malloc (sizeof(struct student) * NUM_STUDENTS);

     /*return the pointer*/
     return (struct student*) memory;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     for (int studentIndex = 0; studentIndex < NUM_STUDENTS; studentIndex++)
     {
         char idCheck = false;
         char scoreCheck = false;

         int newID;
         int newScore;

         // Generate a new ID
         while (!idCheck)
         {
             idCheck = true;
             newID = rand() % NUM_STUDENTS;

             // Linear unsorted search for same ID
             for (int studentSearch = 0; studentSearch < studentIndex; studentSearch++)
             {
                 if (students[studentSearch].id == newID)
                 {
                     // A student with this Id already exists
                     idCheck = false;
                 }
             }
         }
         students[studentIndex].id = newID;

         // Generate a new Score
         while (!scoreCheck)
         {
             scoreCheck = true;
             newScore = rand() % MAX_SCORE;

             // Linear unsorted search for same score
             for (int studentSearch = 0; studentSearch < studentIndex; studentSearch++)
             {
                 if (students[studentSearch].score == newScore)
                 {
                     // A student with this score already exists
                     scoreCheck = false;
                 }
             }
         }
         students[studentIndex].score = newScore;

         // It would be nice to optimize this function to not use two seperate loops for id and score.
         // However, finding an id and score are not mutually exclusive.
     }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
     for (int studentIndex = 0; studentIndex < NUM_STUDENTS; studentIndex++)
     {
         printf("%u\t%u\n", students[studentIndex].id, students[studentIndex].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int min = 100;
     int max = 0;
     int avg = 0;
     for (int studentIndex = 0; studentIndex < NUM_STUDENTS; studentIndex++)
     {
         if (min > students[studentIndex].score)
         {
             min = students[studentIndex].score;
         }
         if (max < students[studentIndex].score)
         {
             max = students[studentIndex].score;
         }
         avg += students[studentIndex].score;
     }
     avg /= NUM_STUDENTS;

     printf ("Max score = %u\n", max);
     printf ("Min score = %u\n", min);
     printf ("Avg score = %u\n", avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free (stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);

    /*call output*/
    output (stud);

    /*call summary*/
    summary (stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
