#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define minimumThree(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char *nextWord(FILE *file)
{
    int maxLength = 16;
    int length = 0;
    char *word = malloc(sizeof(char) * maxLength);
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
void loadDictionary(FILE *file, HashMap *map)
{
    // FIXME: implement
    char str[100];

    while (fscanf(file, "%s\n", &str[0]) != EOF)
    {
        hashMapPut(map, str, 0);
    }
}

/**
** The Levenshtein Distance formula calculates the distance between 2 different strings.
*/
int levenshtein(char *str1, char *str2)
{
    unsigned int str1len, str2len, lastdiag, olddiag;
    str1len = strlen(str1);
    str2len = strlen(str2);
    int *column = malloc((str1len + 1) * sizeof(int));
    for (int z = 1; z <= str1len; z++)
    {
        column[z] = z;
    }
    for (int x = 1; x <= str2len; x++)
    {
        column[0] = x;
        for (int y = 1, lastdiag = x - 1; y <= str1len; y++)
        {
            olddiag = column[y];
            column[y] = minimumThree(column[y] + 1, column[y - 1] + 1, lastdiag + (str1[y - 1] == str2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }

    int result = column[str1len];
    free(column);
    return result;
}

/**
* Helper Function to find similar words & store them into an array
*/
void suggestions(HashMap *map, char *array[])
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink *link = map->table[i];

        while (link != NULL)
        {
            if (strcmp(array[0], "") == 0)
                array[0] = link->key;

            else if (*(hashMapGet(map, array[0])) >= *(hashMapGet(map, link->key)))
            {
                for (int j = 5; j > 0; j--)
                    array[j] = array[j - 1];

                array[0] = link->key;
            }

            link = link->next;
        }
    }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char **argv)
{
    // FIXME: implement
    HashMap *map = hashMapNew(1000);

    FILE *file = fopen("dictionary.txt", "r");
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
        HashLink *link;
        // int dist;

        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }

        else if (hashMapContainsKey(map, inputBuffer))
            printf("Spelling is correct.\n");

        else
        {
            char *words[6] = {""};

            for (int i = 0; i < map->capacity; i++)
            {
                link = map->table[i];

                while (link != NULL)
                {
                    int dist = levenshtein(inputBuffer, link->key);
                    hashMapPut(map, link->key, dist);
                    link = link->next;
                }
            }

            suggestions(map, words);

            for (int j = 0; j < 6; j++)
                printf("Did you mean %s?\n", words[j]);
        }
        //End Implementation
    }
    if (strcmp(inputBuffer, "quit") == 0)
    {
        quit = 1;
    }

    hashMapDelete(map);
    return 0;
}