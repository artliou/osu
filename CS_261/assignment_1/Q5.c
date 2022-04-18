/* CS261- Assignment 1 - Q.5*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Convert a word into StIcKy CaPs
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
     int index = 0;
     while (word[index] != 0)
     {
         // Check if even or odd letter
         if ((index & 1) == 1)
         {
             // Letter is odd, convert to lower
             // Check if the case is upper
             if ((word[index] >= 'A') && (word[index] <= 'Z'))
             {
                 // Letter is between A and Z. Convert!
                 word[index] = toLowerCase(word[index]);
             }
         }
         else
         {
             // Letter is even, convert to upper
             // Check if the case is lower
             if ((word[index] >= 'a') && (word[index] <= 'z'))
             {
                 // Letter is between a and z. Convert!
                 word[index] = toUpperCase(word[index]);
             }
         }

         // Increment index
         index++;
     }
}

int main(){
    char stringBuffer[64];

    /*Read word from the keyboard using scanf*/
    printf ("\nEnter a word: ");
    scanf ("%64s", stringBuffer);

    /*Call sticky*/
    sticky (stringBuffer);

    /*Print the new word*/
    printf ("%s\n\n", stringBuffer);

    return 0;
}
