#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wincon.h>
#include <Windows.h>

#include "genlib.h"
#include "gcalloc.h"
#include "strlib.h"
#include "extgraph.h"

#define TEXTBOX_WIDTH_RATIO 1.0
#define TEXTBOX_HEIGHT_RATIO 1.2

#define EMPTY_COLOR "White"

double dist(double, double, double, double);

void DrawBox(double, double, double, double); //From leftdown to rightup
void DrawOval(double, double, double, double); /**/
void DrawTextBox(double, double, string);
void DrawFixTextBox(double, double, double, double, string);

bool box_intersect(double, double, double, double, double, double, double, double);
bool interval_intersect(double, double, double, double);

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void DrawBox(double x1, double y1, double x2, double y2)
{
    MovePen(x1, y1);
    DrawLine(x2 - x1, 0);
    DrawLine(0, y2 - y1);
    DrawLine(x1 - x2, 0);
    DrawLine(0, y1 - y2);
}

void DrawTextBox(double x, double y, string text)
{
    double width = TextStringWidth(text) * TEXTBOX_WIDTH_RATIO;
    double height = GetFontHeight() * TEXTBOX_HEIGHT_RATIO;
    DrawFixTextBox(x, y, width, height, text);
}

void DrawCleanTextBox(double x, double y, string text)
{
	string color = GetPenColor();
	SetPenColor(EMPTY_COLOR);
	DrawTextBox(x, y, text);
	SetPenColor(color);
}

void DrawFixTextBox(double x, double y, double width, double height, string text)
{
    DrawBox(x, y, x + width, y + height);
    MovePen(x + (width - TextStringWidth(text)) / 2,  y + (height - GetFontHeight()) / 2);
    DrawTextString(text);
    MovePen(x + width, y);
}

void DrawOval(double x1, double y1, double x2, double y2)
{
	/**/
}

bool box_intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	return interval_intersect(x1, x2, x3, x4) && interval_intersect(y1, y2, y3, y4);
}

bool interval_intersect(double x1, double y1, double x2, double y2)
{
	if (y2 >= y1)
		return x2 <= y1;
	else
		return x1 <= y2;
}
