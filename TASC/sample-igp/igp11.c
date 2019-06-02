#include "graphics.h"
#include "extgraph.h"
#include <windows.h>
#include <winuser.h>

bool flag = FALSE;
double x, y; 
void KeyboardEventProcess(int key,int event);
void TimerEventProcess(int timerID);

void Main()
{
    InitGraphics();        	
	registerKeyboardEvent(KeyboardEventProcess);
	registerTimerEvent(TimerEventProcess);
    x = GetWindowWidth()/2;
	y = GetWindowHeight()/2;
}

void KeyboardEventProcess(int key,int event)
{
	if (event==KEY_DOWN && key==VK_ESCAPE) startTimer(1, 500);
}

void TimerEventProcess(int timerID)
{
	static char buf[2] = "9";
    static int count = 0;
    static flag = TRUE;
    if (timerID == 1) {
		SetEraseMode(!flag);
	    MovePen(x, y);
	    DrawTextString(buf);
    	if (flag = !flag) buf[0]--;
 	    if (++count == 20) cancelTimer(1);
    }
}
