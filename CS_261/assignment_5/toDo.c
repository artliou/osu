/*
 * CS 261 Assignment 5
 * Name: 
 * Date: 
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(heap) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // Commands
    switch (command)
    {
        case 'l':
        {
            // Load from file.
            char filename[64];
            printf ("Enter file name to load data from :");
            scanf ("%s", filename);
            FILE * file = fopen (filename, "r");
            if (file == 0)
            {
                printf ("Unable to open file : %s\n", filename);
                return;
            }
            char line [TASK_NAME_SIZE*2];
            while (fgets (line, TASK_NAME_SIZE * 2, file))
            {
                int priority;
                char name[TASK_NAME_SIZE];
                sscanf (line, "%d, %s", &priority, name);
                dyHeapAdd (list, taskNew (priority, name), &taskCompare);
            }
            fclose (file);
            dyHeapSort (list, &taskCompare);
            for (int index = 0; index < dySize(list) / 2; index++)
            {
                dySwap (list, index, dySize(list) - index - 1);
            }
        }
        break;
        case 's':
        {
            // Save tofile.
            char filename[64];
            printf ("Enter file name to save data to :");
            scanf ("%s", filename);
            int fd = open (filename, O_WRONLY | O_CREAT);
            if (fd < 0)
            {
                printf ("Unable to save file : %s\n", filename);
                return;
            }
            for (int index=0; index < dySize (list); index++)
            {
                char line [TASK_NAME_SIZE*2];
                struct Task * curTask = (struct Task *)dyGet (list, index);
                snprintf (line, TASK_NAME_SIZE * 2, "%d, %s\n", curTask->priority, curTask->name);
                write (fd, line, strlen (line));
            }
            close (fd);
        }
        break;
        case 'a':
        {
            int priority;
            char name[TASK_NAME_SIZE];
            memset (name, 0, TASK_NAME_SIZE);
            printf ("Add a new item!!\n");
            printf ("Enter Priority: ");
            scanf ("%d", &priority);
            printf ("Enter name : ");
            scanf ("%s", name);
            dyHeapAdd (list, taskNew (priority, name), &taskCompare);
        }
        break;
        case 'g':
        {
            if (dySize (list) > 0)
            {
                printf ("First Item : \n");
                taskPrint(dyHeapGetMin (list));
                printf ("\n");
            }
            else
            {
                printf ("No items to display!!\n");
            }
        }
        break;
        case 'r':
        {
            if (dySize (list) > 0)
            {
                dyHeapRemoveMin (list, &taskCompare);
            }
            else
            {
                printf ("No items to remove!!\n");
            }
        }
        break;
        case 'p':
        {
            dyPrint(list, &taskPrint);
        }
        break;
        case 'e':
        {
            dyDelete (list);
            exit (0);
        }
        break;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}