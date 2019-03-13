/*
 * File: list.c
 * -------------
 * This file implements the list.h abstraction using an array.
 */


#include <stdio.h>
#include <math.h>

#include "genlib.h"
#include "list.h"

/*
 * Constants:
 * ----------
 * MaxListSize -- Maximum number of elements in the list
 */

#define MaxListSize 1000

/*
 * Type: listCDT
 * --------------
 * This type provides the concrete counterpart to the listADT.
 * The representation used here consists of an array coupled
 * with a integer representing the length of the list.
 */

struct listCDT
{
    int array[MaxListSize];
    int len;
};

/*
 * Function: SizeOfList
 * ------------------
 * This function return the length of a list.
 */

int SizeOfList(listADT list)
{
    return list->len;
}

/*
 * Function: Check
 * ------------------
 * This function decides whether the list is non-decreasing.
 */

int Check(listADT list)
{
    int flag = 1, i;
    for (i = 1; flag && i < SizeOfList(list); ++i) {
        if (list->array[i - 1] > list->array[i]) {
            flag = 0;
        }
    }
    return flag;
}

/*
 * Function: NewList
 * ------------------
 * This function allocates and initializes the storage for a
 * new list.
 */

listADT NewList()
{
    listADT list = New(listADT);
    list->len = 0;
    return list;
}

/*
 * Function: GetList
 * ------------------
 * This function gets a list with the sequence from keyboard.
 */

listADT GetList()
{
    listADT list = NewList();
    int input;
    while (scanf("%d", &input) && input != -1) {
        if (SizeOfList(list) == MaxListSize) {
            printf("Too many input numbers!\n");
            break;
        }
        list->array[(list->len)++] = input;
    }
    if (!Check(list)) {
        printf("Input sequence is illegal.\n");
        list->len = 0;
    }
    return list;
}

/*
 * Function: MergeList
 * ------------------
 * This function merges two non-decreasing list into one 
 * non-decreasing list, and then return its value.
 */

listADT MergeList(listADT lhs, listADT rhs)
{
    listADT list = NewList();
    int lp = 0, rp = 0;
    while (lp != lhs->len || rp != rhs->len) {
        if (lp != lhs->len && rp != rhs->len) {
            if (lhs->array[lp] < rhs->array[rp]) {
                list->array[(list->len)++] = lhs->array[lp++];
            }
            else {
                list->array[(list->len)++] = rhs->array[rp++];
            }
        }
        else if (lp != lhs->len) {
            list->array[(list->len)++] = lhs->array[lp++];
        }
        else {
            list->array[(list->len)++] = rhs->array[rp++];
        }
    }
    return list;
}

/*
 * Function: PutList
 * ------------------
 * This function puts the elements from a list onto the screen.
 */

void PutList(listADT list)
{
    int i;

    for (i = 0; i != SizeOfList(list); ++i) {
        printf("%d", list->array[i]);
        if (i + 1 != SizeOfList(list))
            printf(" ");
    }
    if (SizeOfList(list) == 0)
        printf("NULL");
    printf("\n");
}

/*
 * Function: FreeList
 * ------------------
 * This function frees the memory used by list.
 */

void FreeList(listADT list)
{
    FreeBlock(list);
}
