/* CS261- Assignment 1 - Q.4*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Generate an array of student id and scores and sort them. Print results.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_SCORE    100

#define false        0
#define true         1

struct student{
	int id;
	int score;
};

///////////////////////////////////////////////////
//
// Function declarations
//

int merge_sort(struct student * arr,int n);
void merge(struct student arr[], int l, int m, int r);

struct student* allocate(unsigned int num_students){
     /*Allocate memory for ten students*/
     void * memory = malloc (sizeof(struct student) * num_students);

     /*return the pointer*/
     return (struct student*) memory;
}

void generate(struct student* students, unsigned int num_students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     for (int studentIndex = 0; studentIndex < num_students; studentIndex++)
     {
         char idCheck = false;
         char scoreCheck = false;

         int newID;
         int newScore;

         // Generate a new ID
         while (!idCheck)
         {
             idCheck = true;
             newID = rand() % num_students;

             // Linear unsorted search for same ID for students that exist
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

             // Linear unsorted search for same score for students that exist
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

void output(struct student* students, unsigned int num_students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
     printf ("\n -- Dumping student data --\n\n");
     for (int studentIndex = 0; studentIndex < num_students; studentIndex++)
     {
         printf("%u\t%u\n", students[studentIndex].id, students[studentIndex].score);
     }
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free (stud);
}

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
     merge_sort(students, n);
}

int main(){
    /*Declare an integer n and assign it a value.*/
    const int n = 20;

    /*Allocate memory for n students using malloc.*/
    struct student * students = allocate (n);

    /*Generate random and unique IDs and random scores for the n students, using rand().*/
    generate (students, n);

    /*Print the contents of the array of n students.*/
    output (students, n);

    /*Pass this array along with n to the sort() function*/
    sort (students,n);

    /*Print the contents of the array of n students.*/
    output (students, n);

    // Free student memory
    deallocate (students);

    return 0;
}

//////////////////////////////////////////////////////////////////////
//
// Taken from CS_162
//
// modified to remove class dependencies
// modified to sort student structues

/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  mergeSort_Iterate.cpp
**
** Source code downloaded from :
** http://www.geeksforgeeks.org/iterative-merge-sort/
**
** Code adapted and added to a class
**
*********************************************************************/

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

///////////////////////////////////////////////////////////////////////////////
//
// Source code from : http://www.geeksforgeeks.org/iterative-merge-sort/
//

/* Iterative mergesort function to sort arr[0...n-1] */
int merge_sort(struct student * arr,int n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
   return 0;
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(struct student arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    struct student L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].score <= R[j].score)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
