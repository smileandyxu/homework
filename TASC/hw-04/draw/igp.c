#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

static int down = 0;

void InitConfig();
void draw_with_mouse(int, int, int, int);

Main()
{
	InitConfig();

	registerMouseEvent(draw_with_mouse);
}

void InitConfig()
{
	InitGraphics();
	SetPenColor("Red"); 
    SetPenSize(1);
}
void draw_with_mouse(int x, int y, int button, int event)
{
	double nx, ny;
	nx = ScaleXInches(x);
	ny = ScaleYInches(y);
	switch(event) {
		case BUTTON_DOWN:
			if (button == LEFT_BUTTON || button == RIGHT_BUTTON) {
				down = 1;
				MovePen(nx, ny);
				if (button == RIGHT_BUTTON) {
					SetPenColor("White");
					SetPenSize(3);
				}
			}
		break;

		case BUTTON_UP:
			down = 0;
			if (button == RIGHT_BUTTON) {
				SetPenColor("Red");
				SetPenSize(1);
			}
		break;

		case MOUSEMOVE:
			if (down) {
				DrawLine(nx - GetCurrentX(), ny - GetCurrentY());
			}
		break;
	}
}

