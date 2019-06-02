#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define CURSOR_ID 1
#define CURSOR_FREQUENCY 500
#define CURSOR_CHAR '|'
#define EMPTY_COLOR "White"
#define TEXT_COLOR "Black"
#define MAXLEN 80


static double initx;
static double inity;
static char inputstr[MAXLEN + 2];
static int iscursor = 0;
static int inputlen = 0;
static int strpos = 0;

void delstr();
void insertstr(int);

void InitConfig();
void DrawCursor();
void DrawChar(char);
void DrawCleanText();
void DrawCleanChar(char);

void typein(int, int);
void print(char);
void cursor(int);
void pause_cursor();
void resume_cursor();

/*Response to keyboard*/
void res_del();
void res_back();
void res_left();
void res_right();


Main()
{
	InitConfig();
	registerKeyboardEvent(typein);
	registerCharEvent(print);
	registerTimerEvent(cursor);
	startTimer(CURSOR_ID, CURSOR_FREQUENCY);
}

void InitConfig()
{
	InitGraphics();
	SetPenColor(TEXT_COLOR); 
    SetPenSize(1);
	initx = GetWindowWidth() * 0.1;
	inity = GetWindowHeight() * 0.8;
	MovePen(initx, inity - 0.2);
	SetPenColor("Red");
	DrawTextString("Notice: String size is limited within 80 characters!");
	MovePen(initx, inity);
	DrawTextString("Here's the place to typewrite: ");
	SetPenColor(TEXT_COLOR);
}
void delstr()/**/
{
	if (strpos != inputlen && strpos >= 0) {
		int i;
		for (i = strpos + 1; i != inputlen; ++i) {
			inputstr[i - 1] = inputstr[i];
		}
		inputstr[--inputlen] = 0;/*strpos*/
	}
}
void res_del()/**/
{
	DrawCleanText();
	delstr();
	double nx = GetCurrentX();
	double ny = GetCurrentY();
	DrawTextString(inputstr + strpos);
	MovePen(nx, ny);
}
void res_back()/**/
{
	res_left();
	res_del();
}
void res_left()
{
	if (strpos) {
		char tmp[2] = {0, 0};
		tmp[0] = inputstr[--strpos];
		MovePen(GetCurrentX() - TextStringWidth(tmp), GetCurrentY());
	}
}
void res_right()
{
	if (strpos < inputlen) {
		char tmp[2] = {0, 0};
		tmp[0] = inputstr[strpos++];
		MovePen(GetCurrentX() + TextStringWidth(tmp), GetCurrentY());
	}
}
void typein(int key, int event)
{
	
	switch (event) { 
		case KEY_DOWN:
			pause_cursor();
			switch (key) {
				case VK_RETURN:
					OpenConsole();
					printf("%s", inputstr);
					getchar();
					CloseConsole();
					
				break;
				case VK_BACK:
					res_back();
				break;
				case VK_DELETE: 
					res_del();
				break;
				case VK_LEFT:/**/
					res_left();
				break;
				case VK_RIGHT:/**/
					res_right();
				break;
			}
			DrawCursor();
		break;
		default:
			resume_cursor();
		break;
	}
}
void insertstr(int key)
{
	if (inputlen < MAXLEN) {
		inputstr[++inputlen] = 0;
	}
	int i;
	for (i = inputlen - 1; i > strpos; --i) {
		inputstr[i] = inputstr[i - 1];
	}
	inputstr[strpos] = key;
	if (strpos < inputlen)
		++strpos; 
}
void print(char key)
{
	double nx, ny;
	if (!iscntrl(key) && strpos != MAXLEN) {
		pause_cursor();
		DrawCleanText();
		insertstr(key);
		DrawTextString(inputstr + strpos - 1);
		MovePen(GetCurrentX() - TextStringWidth(inputstr + strpos), GetCurrentY());
		resume_cursor();
	}
}
void cursor(int timerID)
{
	switch(timerID) {
		case CURSOR_ID:
			DrawCursor();
		break;
	}
}
void pause_cursor()
{
	
	cancelTimer(CURSOR_ID);
	if (iscursor) {
		DrawCleanChar(CURSOR_CHAR);
	}
	DrawChar(inputstr[strpos]);
	
}
void resume_cursor()
{
	DrawCursor();
	startTimer(CURSOR_ID, CURSOR_FREQUENCY);
} 
void DrawCursor()
{
	if (iscursor) {
		DrawCleanChar(CURSOR_CHAR);
		DrawChar(inputstr[strpos]);
	}
	else {
		//DrawCleanChar(inputstr[strpos]);
		DrawChar(CURSOR_CHAR);
	}
	iscursor = 1 - iscursor;
}
void DrawCleanChar(char key)
{
	SetPenColor(EMPTY_COLOR);
	DrawChar(key);
	SetPenColor(TEXT_COLOR);
}
void DrawCleanText()
{
	double nx = GetCurrentX();
	double ny = GetCurrentY();
	SetPenColor(EMPTY_COLOR);
	DrawTextString(inputstr + strpos);
	SetPenColor(TEXT_COLOR);
	MovePen(nx, ny);
}
void DrawChar(char key)
{
	double nx = GetCurrentX();
	double ny = GetCurrentY();
	char tmp[2] = {0, 0};
	tmp[0] = key;
	DrawTextString(tmp);
	MovePen(nx, ny);
}
