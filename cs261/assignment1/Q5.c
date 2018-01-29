/* CS261- Assignment 1 - Q.5*/
/* Name: Arthur Liou
 * Date: 1/22/18
 * Solution description: Uppercases all even char, lowercase all odd char
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch)
{
    return ch - 'a' + 'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch)
{
    return ch - 'A' + 'a';
}

void sticky(char *word)
{
    /*Convert to sticky caps*/
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        if ((i % 2) == 0)
        { //Check to see if i is even... if so, then it should be UpperCase
            if (!isupper(*(word + i)))
            { //If it isn't already uppercase, than make it so
                *(word + i) = toUpperCase(*(word + i));
            }
        }
        else if ((i % 2) == 1)
        { //Check to see if i is odd... if so, then it should be LowerCase
            if (!islower(*(word + i)))
            { //If it isn't already lowercase, than make it so
                *(word + i) = toLowerCase(*(word + i));
            }
        }
    }
}

int main()
{
    /*Read word from the keyboard using scanf*/
    char str[20];
    printf("Give Word Less than 20 characters: \n");
    scanf("%s", str);

    /*Call sticky*/
    sticky(str);

    /*Print the new word*/
    printf("%s \n", str);

    return 0;
}
