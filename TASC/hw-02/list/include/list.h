/*
 * File: list.h
 * -------------
 * This file provides an interface to a simple list
 * abstraction.
 */


#ifndef _list_h
#define _list_h


typedef struct listCDT *listADT;                 //Abstraction of type list.

listADT NewList();                               //Create a new list and return a pointer points to it.
listADT GetList();                               //Get a sequence of numbers from keyboard.
listADT MergeList(listADT, listADT);             //Merge two non-decreasing list into one.
void PutList(listADT);                           //Print the elements of a list onto the screen.
void FreeList(listADT);                          //Free the memory space used by the list to which the pointer points to.


#endif