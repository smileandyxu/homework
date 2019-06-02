#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"

static double ccx = 1.0, ccy = 1.0;
static double radius = 1.0; 
void DrawCenteredCircle(double x, double y, double r);
void KeyboardEventProcess(int key,int event);

void Main()
{
    InitGraphics();        	
	registerKeyboardEvent(KeyboardEventProcess);
    ccx = GetWindowWidth()/2; ccy = GetWindowHeight()/2;
    DrawCenteredCircle(ccx, ccy, radius);
}

void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360.0);
}

void KeyboardEventProcess(int key,int event)
{
     if (event==KEY_DOWN && key==VK_ESCAPE) {
     	SetEraseMode(TRUE);
        DrawCenteredCircle(ccx, ccy, radius);
		ccx += 0.5; ccy += 0.5;
		SetEraseMode(FALSE);
        DrawCenteredCircle(ccx, ccy, radius);
     }
     return; 
}
