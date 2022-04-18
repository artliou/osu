#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

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
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */

void loadDictionary(FILE* file, HashMap* map)
{
    int counter = 0;
    int totalCount = 0;
    int maxCount = 109584;
    char * curWord;
    printf ("Loading dictionary...\r");
    fflush (stdout);
    while ((curWord = nextWord(file)) != 0)
    {
        hashMapPut (map, curWord, 1);
        free (curWord);
        counter++;
        totalCount++;
        if (counter == 1000)
        {
            printf ("Loading dictionary... [%.2f%%]\r", (((float) totalCount) * 100.0f) / (float) maxCount);
            fflush (stdout);
            counter = 0;
        }
    }
    printf ("Loading dictionary... [%.2f%%]\n", (((float) totalCount) * 100.0f) / (float) maxCount);
    printf ("Dictionary load complete.\n\n");
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    char wordMatch;
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // Implement the spell checker code here..
        wordMatch = 0;
        if (hashMapContainsKey (map, inputBuffer))
        {
            printf ("The word [%s] is in the dictionary!\n", inputBuffer);
        }
        else
        {
            while (wordMatch == 0)
            {
                inputBuffer [strlen (inputBuffer) - 1] = 0;
                if (hashMapContainsKey (map, inputBuffer))
                {
                    printf ("[%s] is the closest match!\n", inputBuffer);
                    wordMatch = 1;
                }
            }
        }        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    hashMapDelete(map);
    return 0;
}