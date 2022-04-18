#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_STRING_LENGTH 1024
#define STRING_SEPS " .!,?;\n"

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */

static char readBuffer[MAX_STRING_LENGTH];


int main(int argc, const char** argv)
{
    const char* fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    printf ("Opened [%s]\n", fileName);
    FILE * file = fopen (fileName, "r");
    if (file == NULL)
    {
        printf ("File not found! [%s]\n", fileName);
    }
    while (!feof(file))
    {
        fgets (readBuffer, MAX_STRING_LENGTH, file);
        if (readBuffer[strlen(readBuffer) - 1] == '\n')
        {
            readBuffer[strlen(readBuffer) - 1] = 0;
        }
        printf ("Read Line [%s]\n", readBuffer);
        char * curString = strtok (readBuffer, STRING_SEPS);
        while (curString)
        {
            printf (" -- Token: [%s]\n", curString);
            int * value = hashMapGet(map, curString);
            if (value == NULL)
            {
                hashMapPut(map, curString, 1);
            }
            else
            {
                hashMapPut(map, curString, (*value)+1);                
            }
            curString = strtok (NULL, STRING_SEPS);
        }   
    }
    fclose (file);
    // --- Concordance code ends here ---
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}