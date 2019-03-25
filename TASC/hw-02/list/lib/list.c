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

struct listCDT
{
    int num;
    int len;
    listADT prev;
};

/*
 * Function: SizeOfList
 * ------------------
 * This function return the length of a list.
 */

int SizeOfList(listADT list)
{
    if (list == NULL)
        return 0;
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
    for (listADT p = list; p && p->prev; p = p->prev) {
        if (p->num < (p->prev)->num) {
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

listADT NewList(int x, int l, listADT pre)
{
    listADT list = New(listADT);
    list->num = x;
    list->len = l;
    list->prev = pre;
    return list;
}

listADT FindHead(listADT list)
{
    if (list == NULL)
        return NULL;
    else if (list->prev == NULL)
        return list;
    return FindHead(list->prev);
}

/*
 * Function: GetList
 * ------------------
 * This function gets a list with the sequence from keyboard.
 */

listADT GetList()
{
    listADT list = NULL;
    int input;
    while (scanf("%d", &input) && input != -1) {
        if (SizeOfList(list) == MaxListSize) {
            printf("Too many input numbers!\n");
            break;
        }
        list = AddList(list, input);
    }
    if (!Check(list)) {
        printf("Input sequence is illegal.\n");
        FreeList(list);
        list = NULL;
    }
    return list;
}
/*
 * Function: AddList
 * ------------------
 * This function adds an element at the tail of the list.
 */
listADT AddList(listADT list, int x)
{
    listADT tmp;
    if (list)
        tmp = NewList(x, list->len + 1, list);
    else
        tmp = NewList(x, 1, NULL);
    return tmp;
}
/*
 * Function: AddList
 * ------------------
 * This function adds an element at the head of the list.
 */
listADT InsertList(listADT list, int x)
{
    listADT tmp = NewList(x, 1, NULL);
    tmp->num = x;
    listADT p = list;
    while (p) {
        (p->len)++;
        p = p->prev;
    }
    p = FindHead(list);
    if (p) {
        p->prev = tmp;
        return list;
    }
    else {
        return tmp;
    }
    
}
/*
 * Function: MergeList
 * ------------------
 * This function merges two non-decreasing list into one 
 * non-decreasing list, and then return its value.
 */

listADT MergeList(listADT lhs, listADT rhs)
{
    listADT list = NULL;
    while (lhs || rhs) {
        if ((lhs && rhs && lhs->num > rhs->num) || (lhs && !rhs)) {
            list = InsertList(list, lhs->num);
            lhs = lhs->prev;

        }
        else {
            list = InsertList(list, rhs->num);
            rhs = rhs->prev;
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
    int stack[MaxListSize];
    int i = 0;
    while (list) {
        stack[i++] = list->num;
        list = list->prev;
    }
    if (i == 0)
        printf("NULL");
    else {
        for (i = i - 1; i >= 0; --i) {
            printf("%d", stack[i]);
            if (i > 0)
                printf(" ");
        }
    }
    printf("\n");
}

/*
 * Function: FreeList
 * ------------------
 * This function frees the memory used by list.
 */

void FreeList(listADT list)
{
    if (list->prev) {
        FreeList(list->prev);
    }
    FreeBlock(list);
}
